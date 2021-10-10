#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
void file_perms(int n,char* file_name)
{
    struct stat fileperms;
    if(stat(file_name,&fileperms)==-1)
    {
        write(STDOUT_FILENO,"File Does Not Exist",20);
        _exit(1);
    }
    // user read
    char *output=(char*)calloc(1000,sizeof(char));
    if(fileperms.st_mode & S_IRUSR)
        sprintf(output,"User has read permissions on output_file_%d: Yes\n",n);
    else
        sprintf(output,"User has read permissions on output_file_%d: No\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // user write
    if(fileperms.st_mode & S_IWUSR)
        sprintf(output,"User has write permissions on output_file_%d: Yes\n",n);
    else
        sprintf(output,"User has write permissions on output_file_%d: No\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // user execute
    if(fileperms.st_mode & S_IXUSR)
        sprintf(output,"User has execute permissions on output_file_%d: Yes\n\n",n);
    else
        sprintf(output,"User has execute permissions on output_file_%d: No\n\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // group read
    if(fileperms.st_mode & S_IRGRP)
        sprintf(output,"Group has read permissions on output_file_%d: Yes\n",n);
    else
        sprintf(output,"Group has read permissions on output_file_%d: No\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // user write
    if(fileperms.st_mode & S_IWGRP)
        sprintf(output,"Group has write permissions on output_file_%d: Yes\n",n);
    else
        sprintf(output,"Group has write permissions on output_file_%d: No\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // Group execute
    if(fileperms.st_mode & S_IXGRP)
        sprintf(output,"Group has execute permissions on output_file_%d: Yes\n\n",n);
    else
        sprintf(output,"Group has execute permissions on output_file_%d: No\n\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // Others read
    if(fileperms.st_mode & S_IROTH)
        sprintf(output,"Others has read permissions on output_file_%d: Yes\n",n);
    else
        sprintf(output,"Others has read permissions on output_file_%d: No\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // Others write
    if(fileperms.st_mode & S_IWOTH)
        sprintf(output,"Others has write permissions on output_file_%d: Yes\n",n);
    else
        sprintf(output,"Others has write permissions on output_file_%d: No\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    // Others execute
    if(fileperms.st_mode & S_IXOTH)
        sprintf(output,"Others has execute permissions on output_file_%d: Yes\n\n",n);
    else
        sprintf(output,"Others has execute permissions on output_file_%d: No\n\n",n);
    write(STDOUT_FILENO,output,strlen(output));
    free(output);
}
void directory_perms(int n,char* file_name)
{
    struct stat dirperms;
    char *output=(char*)calloc(1000,sizeof(char));
    // printing if directory exist
    // user read
    stat(file_name,&dirperms);
    if(dirperms.st_mode & S_IRUSR)
        sprintf(output,"User has read permissions on directory: Yes\n");
    else
        sprintf(output,"User has read permissions on directory: No\n");
    write(STDOUT_FILENO,output,strlen(output));
    // user write
    if(dirperms.st_mode & S_IWUSR)
        sprintf(output,"User has write permissions on directory: Yes\n");
    else
        sprintf(output,"User has write permissions on directory: No\n");
    write(STDOUT_FILENO,output,strlen(output));
    // user execute
    if(dirperms.st_mode & S_IXUSR)
        sprintf(output,"User has execute permissions on directory: Yes\n\n");
    else
        sprintf(output,"User has execute permissions on directory: No\n\n");
    write(STDOUT_FILENO,output,strlen(output));
    // group read
    if(dirperms.st_mode & S_IRGRP)
        sprintf(output,"Group has read permissions on directory: Yes\n");
    else
        sprintf(output,"Group has read permissions on directory: No\n");
    write(STDOUT_FILENO,output,strlen(output));
    // user write
    if(dirperms.st_mode & S_IWGRP)
        sprintf(output,"Group has write permissions on directory: Yes\n");
    else
        sprintf(output,"Group has write permissions on directory: No\n");
    write(STDOUT_FILENO,output,strlen(output));
    // Group execute
    if(dirperms.st_mode & S_IXGRP)
        sprintf(output,"Group has execute permissions on directory: Yes\n\n");
    else
        sprintf(output,"Group has execute permissions on directory: No\n\n");
    write(STDOUT_FILENO,output,strlen(output));
    // Others read
    if(dirperms.st_mode & S_IROTH)
        sprintf(output,"Others has read permissions on directory: Yes\n");
    else
        sprintf(output,"Others has read permissions on directory: No\n");
    write(STDOUT_FILENO,output,strlen(output));
    // Others write
    if(dirperms.st_mode & S_IWOTH)
        sprintf(output,"Others has write permissions on directory: Yes\n");
    else
        sprintf(output,"Others has write permissions on directory: No\n");
    write(STDOUT_FILENO,output,strlen(output));
    // Others execute
    if(dirperms.st_mode & S_IXOTH)
        sprintf(output,"Others has execute permissions on directory: Yes\n\n");
    else
        sprintf(output,"Others has execute permissions on directory: No\n\n");
    write(STDOUT_FILENO,output,strlen(output));
    free(output);
}
int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        write(STDOUT_FILENO,"Incorrect Input\n",16);
        _exit(1);
    }
    int source, dest, n, m;
    char *buf = (char *)calloc(10000, sizeof(char));
    char *buf2 = (char *)calloc(10000, sizeof(char));
    char search='/';
    int pos_search=0;
    for(int i=0;i<strlen(argv[1]);i++)
    {
        if(argv[1][i]==search)
        {
            pos_search=i;
        }
    }
    if(pos_search!=0)
    {
        pos_search++;
    }
    char *temp_ifn=(char *) calloc(1000, sizeof(char));
    char *temppathname=(char *) calloc(1000, sizeof(char));
    char *temppathname2=(char *) calloc(1000, sizeof(char));
    char *pathname1=(char *) calloc(1000, sizeof(char));
    char *pathname2=(char *) calloc(1000, sizeof(char));
    int k=0;
    for(int i=0;i<pos_search;i++,k++)
    {
        temppathname[k]=argv[1][i];
    }
    temppathname[k]='\0';
    temp_ifn[0]='1';
    temp_ifn[1]='_';
    int j=2;
    for(int i=pos_search;i<strlen(argv[1]);i++,j++)
    {
        temp_ifn[j]=argv[1][i];
    } 
    temp_ifn[j]='\0';
    sprintf(temppathname,"%sAssignment/",temppathname);
    sprintf(temppathname2,"%s",temppathname);
    sprintf(pathname1,"%s%s",temppathname,temp_ifn);
    temp_ifn[0]='2';
    temp_ifn[1]='_';
    sprintf(pathname2,"%s%s",temppathname,temp_ifn);
    struct stat dirperms;
    char *output=(char*)calloc(1000,sizeof(char));
    if(stat(temppathname,&dirperms)==-1)
    {
        sprintf(output,"Directory is created: No");
        write(STDOUT_FILENO,output,strlen(output));
        _exit(1);
    }
    else{
        sprintf(output,"Directory is created: Yes\n");
        write(STDOUT_FILENO,output,strlen(output));
    }
    free(output);
    file_perms(1,pathname1);
    file_perms(2,pathname2);
    directory_perms(1,temppathname2);
    return 0;
}
