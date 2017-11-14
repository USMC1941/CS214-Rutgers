#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#define MAX_BUF 2048  
#define INT_SIZE_BUF 8
#define COMM_SIZE_BUF 256
 
int check_if_number (char *str)
{
  int i;
  for (i=0; str[i] != '\0'; i++)
  {
    if (!isdigit (str[i]))
    {
      return 0;
    }
  }
  return 1;
}

const char *getUserName (int uid)
{
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}


void pidaux (char *cuser)
{
  DIR *thingy;
  FILE *fp;
  struct dirent *entry;

  char path[MAX_BUF], comm_buf[COMM_SIZE_BUF];
  char uid_int_str[INT_SIZE_BUF]={0};
  char *line;
  char *user, *command;
  size_t len=0; // auto allocation
  thingy = opendir ("/proc/");


  if (thingy == NULL)
  {
         perror ("Fail");
         exit(0);
  } 

  while ((entry = readdir (thingy)) != NULL)
  {
    if (check_if_number (entry->d_name))
    {
      strcpy(path, "/proc/");
    	strcat(path, entry->d_name);
    	strcat(path, "/status");
    	fp = fopen(path, "r");

    	if(fp!=NULL)
    	{
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		getline(&line, &len, fp);
    		sscanf(line, "Uid:    %s ", uid_int_str);
    	}
    	else
    	{
    		fprintf(stdout, "FP is NULL\n");
    	}

    	strcpy(path, "/proc/");
    	strcat(path, entry->d_name);
    	strcat(path, "/stat");

    	fp = fopen(path, "r");
    	getline(&line, &len, fp);

    	char comm[COMM_SIZE_BUF],state;
    	unsigned int flags;
    	int pid,ppid,pgrp,session,tty_nr,tpgid;
    	unsigned long minflt,cminflt,majflt,cmajflt,utime,stime;
    	unsigned long long starttime;
    	long cutime,cstime,priority,nice,num_threads,itreavalue;

    	sscanf(line,"%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld 
        %ld %ld %ld %ld %llu",&pid,comm,&state,&ppid,&pgrp,&session,&tty_nr,
        &tpgid,&flags,&minflt,&cminflt,&majflt,&cmajflt,&utime,&stime,&cutime,
        &cstime,&priority,&nice,&num_threads,&itreavalue,&starttime);

    	strcpy (path, "/proc/");
    	strcat (path, entry->d_name);
    	strcat (path, "/comm");
	 
    	fp = fopen (path, "r");
    	if (fp != NULL)
    	{
      	fscanf(fp, "%s", comm_buf);
		    fclose(fp);
      }

      strcpy(path,"/proc/");
      strcat (path, entry->d_name);
      strcat(path,"/schedstat");
     
      fp=fopen(path,"r");
      char exec_runtime_str[256];
      char waiting_on_queue_str[256];
      char times_switched_str[256];
      if(fp!=NULL)
      {
        getline(&line,&len,fp);
        sscanf(line,"%s %s %s", exec_runtime_str, waiting_on_queue_str, 
            times_switched_str);
      }
      unsigned long long exec_runtime = atol(exec_runtime_str);
      unsigned long waiting_on_queue = atol(waiting_on_queue_str);
      unsigned long times_switched = atol(times_switched_str);

      // only print for the current user
      if (strcmp(getUserName(atoi(uid_int_str)), cuser) == 0)
      {
        if (strlen(getUserName(atoi(uid_int_str))) < 9)
        {
            user = getUserName(atoi(uid_int_str));
        }
        else
        {
            user = uid_int_str;
        }
        printf("%s\t %c\t %d\t %d\t %ld\t %s\t\t %lu\t\t %lu\t\t %llu\n", user, state, 
          pid, ppid, num_threads, comm_buf, waiting_on_queue, times_switched, exec_runtime);
      }	 
    }
  } 
  closedir (thingy);
}
 
int main (int argc, char *argv[])
{
  char current_user[256];
  strcpy (current_user, getUserName(getuid()));
  printf("UID\t STATE\t PID\t PPID\t NUM_TR\t COMM\t\t WAIT_T\t\t 
      T_SWCH\t\t EXEC_T\n");
  pidaux(current_user);	
  long Hertz=sysconf(_SC_CLK_TCK); 
  printf("Hertz: %ld\n", Hertz);
  return 0;
}