### explicit free list

there is two section for boundry flag, one is header, another is footer, the function of footer is used to coalese with the next memory block(midterm exam). If there is no footer for previous memory block, we could not coalese with the previous one. the function is like double linked list in logic way. For the free space, there should be an extra flags to label those parts.(midterm exam: （100+1） * 2 * 4)(aligning for 4 Byte in 32-bit system)

[useful link](https://www.youtube.com/watch?v=d_JhP130XO8&t=85s)


### posix standard

The Portable Operating System Interface (POSIX) is a family of standards specified by the IEEE Computer Society for maintaining compatibility between operating systems. POSIX defines the application programming interface (API), along with command line shells and utility interfaces, for software compatibility with variants of Unix and other operating systems (From wiki)

mannual of [poxis api](http://man7.org/linux/man-pages/man2/stat.2.html)

### file operation

**open** LPI 4.3
input: 
path
flags
mode

return: 
file descriptor , type (non negative integer) -> refer all types of open files , each process has its own set of file descriptor

special file descriptor (stdin, stdout, stderror),
interactive shell (this descriptor is always open)


flags:
reading or writing

mode:
permission to be places on the file, create the new file, the mode is controled by the parameters and the umask of the direactory

rwx rwx rwx
111 111 111
(privilage of user the file belonging to, user in same group, other users)

success:

return file descriptor refering to the open file
not exist, create, 

fail:
-1 
when syscall file, errno is set to the specific number to identify the error.

possible reasons:


compare with fopen, [the advantage over open for fopen](https://stackoverflow.com/questions/1658476/c-fopen-vs-open)

**read**

input parametes:(LPI 4.4)

how many to read, read to where,read from where.

open -> read -> start to get the data from the file

success:

the bytes of read

EOF (end of file)-> 0

fail:
-1

**write**
inverse process compared with read

**close**
input：

file discriptor

return:
0 success
-1 error

operation:
free the file descriptor and process could reuse it.

**lseek**
input

return:
new offset
-1 or error

operation: change the offset of the file

**stat**(LPI 15.1)

difference for parameters:

stat() stats the file pointed to by path and fills in buf.

lstat() is identical to stat(), except that if path is a symbolic link, then the link itself is stat-ed, not the file that it refers to.

fstat() is identical to stat(), except that the file to be stat-ed is specified by the file descriptor fd.

```
//return struct of stat
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
https://linux.die.net/man/2/fstat
```

relative concept:

[symbolic link, inode](https://stackoverflow.com/questions/16912997/what-is-there-behind-a-symbolic-link)


**opendir->scandir->closedir**(18.8)
open a directory andretrieve the names of the files it contains one by one. close at last.

return value :  the pointer to struct DIR

```
           struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };
//http://man7.org/linux/man-pages/man3/readdir.3.html
```

### process

**keep in mind!!!**

a process is an abstract entity, defined by the kernel, to which system resources are allocated in order to execute a program.

? represent

process id, positive integer
no fixed relationship between pid and process except the pid=1 (init process) init process is the ancestor of all the process.

Each process also has a parent process identifier (PPID) attribute, which identifies the process that requested the kernel to create this process.

[all kinds of id](https://stackoverflow.com/questions/41498383/what-do-the-identifiers-pid-ppid-sid-pgid-uid-euid-mean)

? system resource

**memory layout**
text segment 
initialized data segment 
uninitialized data segment
stack
heap
+
?(how to track/scheduler/controle the process for os?) 
refer to
[Although the task_struct data structure is quite large and complex, but its fields can be divided into a number of functional areas](http://www.tldp.org/LDP/tlk/kernel/processes.html
)

? check on linux os

ps top pstree

? create
sys call fork()


### fork(24.1 24.2)

input
void

operation:


return
in parent: return process id of child on success
error: -1
in child process :return 0

use return value to seprate the parent and the child process

question:

how many processes (3) are created for:

```
int main()  
{  
        fork() || fork();  
        printf("+");  
        return 0;  
} 
```

### wait(26)

In many applications where a parent creates child processes, it is useful for the parent to be able to monitor the children to find out when and how they terminate.

input:
status

operation:
parent process wait the termination of child process
[demo link](http://www.geeksforgeeks.org/wait-system-call-c/)

return:
Returns process ID of terminated child, or –1 on error


### exit()
terminate and release the resource

### orphan && zombie(26.2)

different lifecycle of parent process and child process

? the status of parent and child process when there is orphan process or zombie process？

[demo](http://www.geeksforgeeks.org/zombie-and-orphan-processes-in-c/)

how to check: [?](https://askubuntu.com/questions/111422/how-to-find-zombie-process)

meaning of [Stat column for ps](https://askubuntu.com/questions/360252/what-do-the-stat-column-values-in-ps-mean)

### signal


Signals - Sent by other processes or the kernel to a specific process to indicate various conditions.

The types of inter process communication are: ?

http://www.comptechdoc.org/os/linux/programming/linux_pgcomm.html


### Demo

fork, fork_wait, orphan&zombie, io operation

when you start to using it, you will start to understand it.


### other useful links
http://www.man7.org/tlpi/
