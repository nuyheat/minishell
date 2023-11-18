#include "minishell.h"

int	main()
{
	int		new_flgs;
	char	*buf;

	buf = calloc(10, 10);
	new_flgs = 0;
	buf[0] = '<';
	tokenize_flgs(NULL, &new_flgs, '<');
	tokenize_flgs(NULL, &new_flgs, '<');
	tokenize_one(new_flgs, &buf, '<');
	for (int i = 0; buf[i] != '\0'; i++)
		printf("buf[%d] : %c\n", i, buf[i]);
	printf("new_flgs : %d\n", new_flgs);
} // tokenize_one 테스트용 main