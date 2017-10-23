#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

// the ls function
int ls(char* base)
{
    DIR *thingy = opendir(base);
    struct dirent *newfile;

    char buf[1024] = {0};
    while((newfile = readdir(thingy)) != NULL)
    {
        int flag = 0;
        if (newfile->d_type == DT_REG)
        {
            // if the base directory is "./", no need to add "/"
            if (!strcmp(base,"./"))
            {
                sprintf(buf, "%s%s", base, newfile->d_name);
            }
            else
            {
                sprintf(buf, "%s/%s", base, newfile->d_name);
            }
            
            // for a file, print its name with full path and size
            printf(" %s", buf);
            int checkFD = open(buf, O_RDONLY);
            // check if no open error 
            if (!checkFD)
            {
                return -1;
            }
            int len = lseek(checkFD, 0, SEEK_END);
            close(checkFD);
            printf("    %d\n",len);
        }
        else if (newfile->d_type == DT_DIR)
        {
            // for folder like "." or "..", no need to search for their sub-folder
            if (!strcmp(newfile->d_name,"."))
            {
                flag = 1;
            }

            if (!strcmp(newfile->d_name,".."))
            {
                flag = 1;
            }

            // if the base directory is "./", no need to add "/"
            if (!strcmp(base,"./"))
            {   
                sprintf(buf, "%s" , newfile->d_name);
            }
            else 
            {
                sprintf(buf, "%s/%s", base, newfile->d_name);
            }

            // for a folder, print its name with full path
            printf(" %s/\n", buf);

            // if it's not "." or ".." , continue to explore its sub-folder
            if (flag != 1)
            {
                ls(buf);
            }
            
        }
        else
        {
            return 0;
        }
        
    }
    closedir(thingy);
    return 1;
}


int main(int argc, char* argv[])
{
    // base directory
    char* base;

    if (argc == 1)
    {
        base = "./";
    }
    else if(argc == 2)
    {
        base = argv[1];
    }
    else
    {
        return 0;
    }

    // call the ls function
    ls(base); 
}
