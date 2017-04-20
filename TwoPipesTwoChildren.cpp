// file: TwoPipesTwoChildren.cpp
// author: Blake Grabsky
// date: 04/06/2017
// purpose: CS3376
// description:
// this program executes "ls -ltr | grep 3376 | wc -l", by dividing the three commands among two child and one parent process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int pid, pid2;
	int fd[2];
	int fd2[2];
	char *arg[3];
	char *arg2[3];
	char *arg3[3];

	// pipe error
	if (pipe(fd) == -1){
    		perror("pipe");
    		exit(1);
	}

	// fork
	pid = fork();

	// fork error
	if (pid == -1){
   		perror("fork");
		exit(2);
	}
	// child processes
	if (pid == 0){

		// pipe error
		if (pipe(fd2) == -1){
        		perror("pipe");
        		exit(11);
    		}

		// fork
    		pid2=fork();

		// fork error
    		if(pid2 == -1){
        		perror("fork 2");
        		exit(22);
    		}
		
		// executes "wc -l"
    		if (pid2 == 0){
			close(fd[1]);
			close(fd[0]);
        		close (fd2[1]);
        		dup2 (fd2[0],0);
        		close (fd2[0]);
        		arg3[0] = "wc";
        		arg3[1] = "-l";
        		arg3[2] = NULL;
        		execvp("wc", arg3);
        		perror("execvp second child");
    		}	
		
		// executes "grep 3376"
    		else{
        		close (fd[1]);
        		dup2(fd[0],0);
        		close (fd[0]);
        		close (fd2[0]);
        		dup2(fd2[1],1);
        		close (fd2[1]);
        		arg2[0] = "grep";
        		arg2[1] = "3376";
        		arg2[2] = NULL;
        		execvp("grep", arg2);
        		perror("execvp first child");
    		}
	}

	// parent process
	else{
    		// executes " ls -ltr"
    		close (fd[0]);
    		dup2(fd[1],1);
    		close (fd[1]);
    		arg[0] = "ls";
    		arg[1] = "-ltr";
    		arg[2] = NULL;
    		execvp("ls", arg);
    		perror("execvp father");    
	}

	return(0);
}
