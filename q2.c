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
    if(argc!=4)
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
    source = open(argv[1], O_RDONLY);
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
    char *pathname=(char *) calloc(1000, sizeof(char));
    int k=0;
    for(int i=0;i<pos_search;i++,k++)
    {
        temppathname[k]=argv[1][i];
    }
    temppathname[k]='\0';
    temp_ifn[0]='2';
    temp_ifn[1]='_';
    int j=2;
    for(int i=pos_search;i<strlen(argv[1]);i++,j++)
    {
        temp_ifn[j]=argv[1][i];
    } 
    temp_ifn[j]='\0';
    sprintf(temppathname,"%sAssignment/",temppathname);
    mkdir(temppathname,0777);
    sprintf(pathname,"%s%s",temppathname,temp_ifn);
    dest = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0744);
    filesize = lseek(source, (off_t)0, SEEK_END);
    //filesize is lastby +offset
    // to find number of times i have to raed from the file
    // What i have done is i read 1000 bytes at a time
    int part_size,part_number,number_of_parts;
    number_of_parts=(argv[2][0]-'0');
    part_number=(argv[3][0]-'0');
    part_size=filesize/number_of_parts;
    printf("%d ",part_size);
    int block_size=get_bs(part_size);
    if (part_size % block_size == 0)
    {
        number_of_reads = part_size / block_size;
        last=0;
    }
    else
    {
        number_of_reads = (part_size / block_size);
        last = part_size - (number_of_reads * block_size);
        number_of_reads++;
    }
    printf("%lld %lld\n", number_of_reads, last);
    long long int rea=0;
    long long int where_to_read=(part_size*(part_number))-block_size;
    for (i = number_of_reads - 1; i >= 0; i--)
    { 
        if(i==0)
        {
            lseek(source, (off_t)(part_size*(part_number-1)), SEEK_SET);
            n = read(source, buf, last);
            rea+=n;
            if (n < 1)
            {
                printf("%lld", i);
                fprintf(stderr, "can't read 1 byte");
                exit(-1);
            }
            // buf is an array of 1024 bytes
            // reverse kar dete hai
            // o(512) constant time
            for(int j=0;j<n;j++)
            {
                buf2[j]=buf[n-j-1];
            }
            m = write(dest, buf2, n);
            if (m < 1)
            {
                fprintf(stderr, "can't write 1 byte");
                exit(-1);
            }
            double percentage = (rea * (100.0)) / part_size;
            sprintf(percentage_buffer, "Total progres= %0.2f%%\r", percentage);
            write(STDOUT_FILENO, percentage_buffer, strlen(percentage_buffer));
            fflush(stdout);
        }
        else
        {
            lseek(source, (off_t)where_to_read, SEEK_SET);
            n = read(source, buf, block_size);
            rea+=n;
            if (n < 1)
            {
                printf("%lld", i);
                fprintf(stderr, "can't read 1 byte");
                exit(-1);
            }
            // buf is an array of 1024 bytes
            // reverse kar dete hai
            // o(512) constant time
            for(int j=0;j<n;j++)
            {
                buf2[j]=buf[n-j-1];
            }
            m = write(dest, buf2, n);
            if (m < 1)
            {
                fprintf(stderr, "can't write 1 byte");
                exit(-1);
            }
            double percentage = (rea * (100.0)) / part_size;
            sprintf(percentage_buffer, "Total progres= %0.2f%%\r", percentage);
            write(STDOUT_FILENO, percentage_buffer, strlen(percentage_buffer));
            fflush(stdout);
            where_to_read-=block_size;
        }
    }
    write(STDOUT_FILENO, "\nDONE\n", 6);
    close(source);
    close(dest);

    return 0;
}
