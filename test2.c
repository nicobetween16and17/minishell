#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10

void execute_pipeline(char *commands[MAX_COMMANDS]) {
	int i;
	pid_t pid;
	int pipefds[MAX_COMMANDS][2];

	// Create the pipes
	for (i = 0; i < MAX_COMMANDS - 1; i++) {
		if (pipe(pipefds[i]) == -1) {
			perror("Error creating pipe");
			exit(1);
		}
	}

	// Fork the processes and execute the commands
	for (i = 0; commands[i] != NULL; i++) {
		pid = fork();
		if (pid == -1) {
			perror("Error forking process");
			exit(1);
		}
		if (pid == 0) {
			// This is the child process

			// If this is not the last command, redirect stdout to the next pipe
			if (commands[i+1] != NULL) {
				if (dup2(pipefds[i][1], STDOUT_FILENO) == -1) {
					perror("Error redirecting stdout");
					exit(1);
				}
			}

			// If this is not the first command, redirect stdin from the previous pipe
			if (i > 0) {
				if (dup2(pipefds[i-1][0], STDIN_FILENO) == -1) {
					perror("Error redirecting stdin");
					exit(1);
				}
			}

			// Close all pipes
			for (int j = 0; j < MAX_COMMANDS - 1; j++) {
				close(pipefds[j][0]);
				close(pipefds[j][1]);
			}

			// Execute the command
			execve(commands[0], commands, NULL);
			perror("Error executing command");
			exit(1);
		}
	}

	// Close all pipes in the parent process
	for (i = 0; i < MAX_COMMANDS - 1; i++) {
		close(pipefds[i][0]);
		close(pipefds[i][1]);
	}

	// Wait for all child processes to finish
	for (i = 0; commands[i] != NULL; i++) {
		wait(NULL);
	}
}

int main() {
	char *commands[MAX_COMMANDS] = {
			"ls", "-l",
			"grep", "^d",
			"wc", "-l",
			NULL
	};

	execute_pipeline(commands);
	return 0;
}