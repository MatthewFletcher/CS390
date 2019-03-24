#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


int main(int argc, const char **argv)
{
    //printf("%s\n", "ls called from myls"); 
    char *curr_dir = NULL;
    DIR *dp = NULL;
    //Dirent structure is indicated in comments below code
    struct dirent *dptr = NULL;
    unsigned int count = 0;

    curr_dir = getenv("PWD");

    //Check if directory opens, if not, return error code. 
    if((dp = opendir((const char*)curr_dir))==NULL)
        return -1;
    //Select Loop through directory and print out names 
    // based on the argument 
    if(argc > 1 && !(strcmp(argv[1], "-a")))
    {
        // printf("%s", "-a argument chosen");
        for(count=0;(dptr = readdir(dp)) != NULL;count++)
        {
            printf("%s\t", dptr->d_name);
        }
    }
    else
    {

        // printf("%s", "-a argument not chosen");
        for(count=0;(dptr = readdir(dp)) != NULL;)
        {
            if(dptr->d_name[0] != '.')
            {
                count++;
                //printf("%d ",dptr->d_type);
                printf("%s", dptr->d_name);
                if(dptr->d_type == 4)
                printf("/\t");
                else
                    printf("\t");
            }
        }
    }
    //    printf("\n %u\n", count);
    //printf("%s","\n");
    return 0;
}

/*
struct dirent
{
    ino_t          d_ino;       // inode number 
    off_t          d_off;       // offset to the next dirent 
    unsigned short d_reclen;    // length of this record 
    unsigned char  d_type;      // type of file; not supported
                                //   by all file system types 
    char           d_name[256]; // filename 
};
*/
