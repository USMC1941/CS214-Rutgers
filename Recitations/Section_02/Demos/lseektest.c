//lseek is a system call that is used to change the location of the read/write pointer of a file descriptor. The location can be set either in absolute or relative terms.
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
 
int main()
{
        int file=0;
        if((file=open("dir.c",O_RDONLY)) < -1)
                return 1;
 
        char buffer[19];
        if(read(file,buffer,19) != 19)  return 1;
        printf("%s\n",buffer);
 
        if(lseek(file,10,SEEK_SET) < 0) return 1;
 
        if(read(file,buffer,19) != 19)  return 1;
        printf("%s\n",buffer);
 
        return 0;
}

/*

Value	    Meaning
SEEK_SET	Offset is to be measured in absolute terms.
SEEK_CUR	Offset is to be measured relative to the current location of the pointer.
SEEK_END	Offset is to be measured relative to the end of the file.

*/