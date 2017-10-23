// Created by Hanxiong Chen
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void printDirInfo(char *dir) {
	DIR *dp = NULL;
	struct dirent *curObj = NULL;
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "Can't open directory: %s\n", dir);
		return;
	}
	while (curObj = readdir(dp)) {
		if (!strcmp(".", curObj->d_name) || 
				!strcmp("..", curObj->d_name)) {
			continue;
		}
		if (curObj->d_type == DT_REG) {
			char * newPath = (char *) malloc(strlen(curObj->d_name) 
					+ strlen(dir) + 2);

			/* gurantee that strcpy works */
			newPath[0] = '\0';
			strcpy(newPath, dir);
			strcat(newPath, "/");
			strcat(newPath, curObj->d_name);

			/* for the assignment you can do:
			 * int pid = fork();
			 * if child process:
			 *	  sorter("path_of_file");
			 * 
			 * if parent process:
			 *	  (keep searching the files)
			 * Think about how to record all the
			 * PIDs.
			 *
			 * //////////////////////////////
			 * 1. you can put the wait() call in
			 * a signal_handler to get a 
			 * non-block parent program. sorter()
			 * function is your project 0. 
			 *
			 * 2. You need to modify your code to 
			 * make your first project be a sorting 
			 * module instead of a lonely executable.
			 * 
			 * 3. I recommend you to change your 
			 * project 0 code to be a library and
			 * include the sorter library header 
			 * file in this project. This will make 
			 * your code clean. Or you can just 
			 * write all the functions in one source 
			 * file.
			 * //////////////////////////////
			 * */
			/* check the file size */
			int fd = open(newPath, O_RDONLY);
			if (fd < 0) {
				fprintf(stderr, "Can't open file: %s\n", newPath);
				return;
			}
			int len = lseek(fd, 0, SEEK_END);
			close(fd);

			printf("%-30s%s%d\n", newPath, " ", len);
			free(newPath);
		}
		else if (curObj->d_type == DT_DIR) {
			char * newPath = (char *)malloc(strlen(curObj->d_name)
					+ strlen(dir) + 2);

			newPath[0] = '\0';
			
			/* choice 1: do not add ./ to directory 
			if (strcmp(dir, ".")) {
				strcpy(newPath, dir);
				strcat(newPath, "/");
			}*/
		    ///////////////////////
			// choice 2: add ./ to directory
			strcpy(newPath, dir);
			strcat(newPath, "/");
		    //////////////////////
			
			strcat(newPath, curObj->d_name);
			printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n", newPath);
			printDirInfo(newPath);
			free(newPath);
		}
	}
	closedir(dp);
	return;
}

int main(int argc, char * argv[]) {
	char * base = ".";
	if (argc >= 2) {
		base = argv[1];
	}
	printf("Directory index from %s\n", base);
	printDirInfo(base);
	return 0;
}
