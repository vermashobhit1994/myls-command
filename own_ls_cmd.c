//program to write ls command that gives names of files in current directory
#include<stdio.h>
#include<dirent.h>//for DIR,struct dirent
#include<stdlib.h>//for exit(0)
#include<errno.h>//for errno
#include<string.h>//for strerror
#define PATH_MAX_NO 256
void print_dir_recursively(const char *pathname)
{
    DIR *dp;
    struct dirent *dirp;
    char PATH[PATH_MAX_NO] ;
    int width = 60; 
    //opendir function returns NULL on error
    if( (dp = opendir(pathname) ) == NULL)
    {
        //here strerror is used to print corresponding error message to error number
        printf("Error in opening directory %s\n",strerror(errno));
        return ;
    }

    //readdir is used to read the directory by DIR pointer using dirp structure 
    while( (dirp = readdir(dp)) != NULL)
    {
        
        
        if(dirp -> d_type == DT_DIR)
        {
            
            if( (strcmp(dirp -> d_name,".") == 0) || (strcmp(dirp->d_name,"..") == 0) )
            {
                //return back to while loop
                continue;
            }
            char *str = "directory";
            
            printf("%s/%s  ->  %s\n",pathname,dirp -> d_name,str);
            
            snprintf(PATH,sizeof(PATH)-1,"%-s/%-s",pathname,dirp -> d_name);
            //printf("after %s\n",PATH);
                    
            print_dir_recursively(PATH);
        }
        else if (dirp -> d_type == DT_REG)
        {
            char *str = "normal file";
            printf("%s/%s  ->  %s\n",pathname,dirp -> d_name,str);
        }
        else if (dirp -> d_type == DT_LNK)
        {
            char *str = "symbolic link file";
            printf("%s/%s  ->  %s\n",pathname,dirp -> d_name,str);
        }
        
        else if (dirp -> d_type == DT_BLK)
        {
            char *str = "block device file";
            printf("%s/%s  ->  %s\n",pathname,dirp -> d_name,str);
        }
        else
        {
            char *str = "Unknown file";
            printf("%s/%s  ->  %s\n",pathname,dirp -> d_name,str);
                   
        }
        
    }
    closedir(dp);
    printf("\n");

}
int main(int argcount,char *argv[])
{ 
    
    char pathname[PATH_MAX_NO];
    //DIR is directory stream and is used when any directory is to opened
    DIR *dp;

    //It's a structure which has fd,data,allocation,offset, size,pos for all files
    struct dirent *dirp;

    //if directory isn't specified
    if(argcount != 2)
    {
        print_dir_recursively(".");
        
    }
    else
        print_dir_recursively(argv[1]);
    
}

