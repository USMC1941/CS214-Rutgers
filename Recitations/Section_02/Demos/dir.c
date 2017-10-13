
#include <unistd.h>  
#include <stdio.h>  
#include <dirent.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <stdlib.h>  
  
  
void printdir(char *dir, int depth)  
{  
    DIR *dp;  
    struct dirent *entry;  
    struct stat statbuf;  
  
    if ((dp = opendir(dir)) == NULL) {  
        fprintf(stderr, "Can`t open directory %s\n", dir);  
        return ;  
    }  
    //change current work dir to the dir 
    //same to the cd comand 
    chdir(dir);  
    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);  
        if (S_ISDIR(statbuf.st_mode)) {  
            if (strcmp(entry->d_name, ".") == 0 ||   
                strcmp(entry->d_name, "..") == 0 )    
                continue;     
            printf("%*s%s/\n", depth, "", entry->d_name);  
            printdir(entry->d_name, depth+4);  
        } else  
            printf("%*s%s\n", depth, "", entry->d_name);  
    } 
    //change to the upper dir
    chdir("..");  
    closedir(dp);     
}  
  
  
int main(int argc, char *argv[])  
{  
    char *topdir = ".";  
    if (argc >= 2)  
        topdir = argv[1];  
  
    printf("Directory scan of %s\n", topdir);  
    int printdepth=0;
    printdir(topdir,printdepth);  
    printf("done.\n");  
    exit(0);  
}  