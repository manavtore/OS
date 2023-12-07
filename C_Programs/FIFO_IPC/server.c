#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
	FILE *fptr;
	char *np1="pipe3", *np2="pipe4", buffer[100];

int wfd, rfd, no, i=0, word=0, line=0, character=0;

	mkfifo(np1, 0666);
	mkfifo(np2, 0666);	
	
	rfd=open(np1, O_RDONLY);
	no=read(rfd, buffer, 100);

	buffer[no]='\0';
	
	close(rfd);
	
	printf("\nCatched string --> %s\n", buffer);
	
	for(i=0; buffer[i]!='\0'; i++)
	{
		if(buffer[i]==' ')
			word++;
		else if(buffer[i]=='.')
		{
			line++;
			word++;
		}
		else
			character++;
	}
	printf("\nWords=%d\nLines=%d\nCharacters=%d\n", word+1, line+1, character+1);
	fptr=fopen("info.txt", "a+");
	fprintf(fptr, "\nWords=%d\nLines=%d\nCharacters=%d\n", word+1, line+1, character);
	
	wfd=open(np2, O_WRONLY);
	
	no=write(wfd, fptr, 500);
	close(wfd);
	return 0;
}