#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

struct stat {
  dev_t     st_dev;     /* ID of device containing file */
  ino_t     st_ino;     /* inode number */
  mode_t    st_mode;    /* protection */
  nlink_t   st_nlink;   /* number of hard links */
  uid_t     st_uid;     /* user ID of owner */
  gid_t     st_gid;     /* group ID of owner */
  dev_t     st_rdev;    /* device ID (if special file) */
  off_t     st_size;    /* total size, in bytes */
  blksize_t st_blksize; /* blocksize for file system I/O */
  blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
  time_t    st_atime;   /* time of last access */
  time_t    st_mtime;   /* time of last modification */
  time_t    st_ctime;   /* time of last status change */
};

int main() {
  FILE *file = fopen("notes.txt", "r");
  int fd = fileno(file); /* Just for fun - extract the file descriptor from a C FILE struct */
  struct stat s;
  fstat(fd, &s);
  printf("Last accessed %s", ctime(s.st_atime));
}

int exists(char* directory, char* name)  {
    struct dirent *dp;
    DIR *dirp = opendir(directory);
    //
    while ((dp = readdir(dirp)) != NULL) {
        puts(dp->d_name);
        if (!strcmp(dp->d_name, name)) {
 	        return 1; /* Found */
        }
    }
    //
    closedir(dirp);
    return 0; /* Not Found */
}
