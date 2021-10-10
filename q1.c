#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// block size logic
// 0<filesize<=1024  block size = 64
// 1024<filesize<=32768 block size = 1024
// filesize> 32768  block size 8192
int get_bs(int fz)
{
    if(fz<=1024)
        return 64;
    else if (fz >1024 && fz<=32768)
        return 1024;
    else
        return 8192;
}
int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        write(STDOUT_FILENO,"Incorrect Input\n",16);
        exit(1);
    }
    int source, dest, n, m;
    char *buf = (char *)calloc(10000, sizeof(char));
    char *buf2 = (char *)calloc(10000, sizeof(char));
    char *percentage_buffer = (char *)calloc(100, sizeof(char));
    long long filesize, number_of_reads;
    long long i, last;
    // source is the unique identification for source file
    source = open(argv[1], O_RDONLY);
    if(source<0)
    {        
        perror("Error: ");
        exit(-1);
    }
    // argv[1] is the path pf source file
    char search='/';
    int pos_search=0;
    for(int i=0;i<strlen(argv[1]);i++)
    {
        if(argv[1][i]==search)
        {
            pos_search=i;
        }
    }
    // after this i have the last position of '/' in the path
    // this implies after that position file's name start
    if(pos_search!=0)
    {
        pos_search++;
    }
    // above is an edge case when the file is in current directory
    char *temp_ifn=(char *) calloc(1000, sizeof(char));
    char *temppathname=(char *) calloc(1000, sizeof(char));
    char *pathname=(char *) calloc(1000, sizeof(char));
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
    // temp_ifn now conatins the name of the output file
    sprintf(temppathname,"%sAssignment/",temppathname);
    // temppathname contains the path of the directory
    mkdir(temppathname,0700);
    sprintf(pathname,"%s%s",temppathname,temp_ifn);
    // pathname contains th epath of destination
    dest = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(dest<0)
    {        
        perror("Error: ");
        exit(-1);
    }
    filesize = lseek(source, (off_t)0, SEEK_END);
    //filesize is lastby +offset
    // to find number of times i have to raed from the file
    if(filesize<=0)
    {
        write(STDOUT_FILENO,"Error\n",6);
        exit(-1);
    }
    int block_size=get_bs(filesize);
    // block size is the max number of bytes i can read in one time
    if (filesize % block_size == 0)
    {
        number_of_reads = filesize / block_size;
    }
    else
    {
        number_of_reads = (filesize / block_size);
        last = filesize - (number_of_reads * block_size);
        number_of_reads++;
    }
    // in 1st i went to the first position of the last block and reverse that block and write
    // then went to 1st position of second last block and reverse that and so ..on
    long long int rea=0;
    for (i = number_of_reads - 1; i >= 0; i--)
    { //read byte by byte from end
        lseek(source, (off_t)(i * block_size), SEEK_SET);
        n = read(source, buf, block_size);
        rea+=n;
        if (n < 1)
        {
            // for error handling printf("%lld", i);
            perror("Error: ");
            exit(-1);
        }
        // reverse kar dete hai
        // o(block size) constant time
        for(int j=0;j<n;j++)
        {
            buf2[j]=buf[n-j-1];
        }
        m = write(dest, buf2, n);
        if (m < 1)
        {
            perror("Error: ");
            exit(-1);
        }
        double percentage = (rea * (100.0)) / filesize;
        sprintf(percentage_buffer, "Total progres= %0.2f%%\r", percentage);
        write(STDOUT_FILENO, percentage_buffer, strlen(percentage_buffer));
        fflush(stdout);
    }
    write(STDOUT_FILENO, "\nDONE\n", 6);
    close(source);
    close(dest);

    return 0;
}
