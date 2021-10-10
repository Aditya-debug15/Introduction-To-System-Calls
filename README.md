# Introduction to System Calls
It is part of the first assignment of the OSNW course in Monsoon 2021 
Motivate of these questions were to establish a strong understanding of the various system-calls<br>

## System-Calls used
The system calls used to complete these questions are `write`,`read`,`perror`,`open`,`close`,`mkdir`,`lseek` and `stat`

# Ques 1
1. We are given a file and we need to reverse the content of that file and store the new file in the directory Assignment created under current working directory
2. Need to print a progress bar

## Procedure
1. For a given file, we can use `lseek` to get the total file size, we can also do this using stat.
2. Depending upon the file size need to decide how many bytes should be read.<br>
If the file size is too large so reading all the file in a single go won't be feasible.<br>
Also we should try to read parts of the file that are multiple of 2.
3. From the file size we can get the block size and from there we can calculate how many times we need to read and write.
4. Using `lseek` go to the desired location, read that block using `read` and reverse it<br>
5. Write that block using `write`.
6. For printing progress bar we can use combination of `sprintf`, `write` and `fflush`.

# Ques 2
1. We are given a file, number of parts the file is divided into, and the part of the file that has to be reversed.
2. Also we are required to print the progress bar.

## Procedure
It has a same procedure as that of 1st question only slight difference is the calculation part that decides from where to place the cursor using lseek.

# Ques 3
Given a file name 
1. We need to check if the directory Assignment exist or not
2. Need to check for 2 files in Assignment directory that are 1_file_name and 2_file_name.
3. Need to print the permissions of the two files and Assignment directory

## Procedure
1. Using `stat` to check file permissions. For that need to declare `struct stat fileperms`
2. Execute the system call `stat(file_name,&fileperms)`, it returns value tell us whether a file exist or not, if file exist it fills the fileperm variable with the data we need.
3. Use `fileperms.st_mode`, `&` and MACROS in stat file to check for each permission.
for example `fileperms.st_mode & S_IRUSR` returns true if user has read permission else it returns false 

# Some Assumptions
1. The progress bar works in efficient manner if the file size is large.
2. All the input paths are less than 1024 bytes long. 
