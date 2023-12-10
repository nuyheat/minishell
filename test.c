#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>

int main()
{
	// int fds[2];

	// pipe(fds);
	int fd = open("tmp", O_CREAT | O_RDWR, 0644);
	dup2(fd, STDOUT_FILENO);
	char str[10];
	read(0, str, 9);
	// char *line = readline("> ");
	// write(fds[1], line, 10);
}
