// code for IPC using UnNamed Pipes
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
FILE *fp;
int fd1[2],fd2[2],i=0;
char ch1,ch2,str1[100],str2[100],path[100]="pipe.txt";
int ret1,ret2;
pid_t pid;
ret1=pipe(fd1);
ret2=pipe(fd2);
if(ret1==-1 || ret2==-1)
printf("\nERROR\n");
pid=fork();
if(pid==0)
{
read(fd1[0],str2,100);
fp=fopen(str2,"r");
while(!feof(fp))
{
ch2=fgetc(fp);
write(fd2[1],&ch2,1);
}}
else
{
write(fd1[1],path,strlen(path)+1);
while(read(fd2[0],&ch1,1)>0)
printf("%c",ch1);
}}

//code for 