#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main() {
    int pipe1[2]; // Pipe for parent to child communication (pathname)
    int pipe2[2]; // Pipe for child to parent communication (file contents)

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        close(pipe1[READ_END]);
        close(pipe2[WRITE_END]);

        char pathname[256];
        printf("Enter the pathname of the file: ");
        fgets(pathname, sizeof(pathname), stdin);

        write(pipe1[WRITE_END], pathname, sizeof(pathname));
        close(pipe1[WRITE_END]);

        char fileContents[4096];
        read(pipe2[READ_END], fileContents, sizeof(fileContents));
        close(pipe2[READ_END]);

        printf("\nFile Contents received from child:\n%s\n", fileContents);

    } else {
        close(pipe1[WRITE_END]);
        close(pipe2[READ_END]);

        char pathname[256];
        read(pipe1[READ_END], pathname, sizeof(pathname));
        close(pipe1[READ_END]);

        FILE *file = fopen(pathname, "r");
        if (file == NULL) {
            perror("File open failed");
            exit(EXIT_FAILURE);
        }

        char fileContents[4096];
        size_t bytesRead = fread(fileContents, 1, sizeof(fileContents), file);
        fclose(file);

        write(pipe2[WRITE_END], fileContents, bytesRead);
        close(pipe2[WRITE_END]);
    }

    return 0;
}