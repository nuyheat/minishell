/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/13 20:20:36 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	newline_check(char **argv, int *idx, int *newline)
{
	int	char_idx;

	*idx = 1;
	*newline = 1;
	while (argv[*idx] != NULL)
	{
		if (argv[*idx][0] == '-')
		{
			char_idx = 1;
			while (argv[*idx][char_idx] != '\0')
			{
				if (argv[*idx][char_idx] != 'n')
					break ;
				char_idx++;
			}
			if (argv[*idx][char_idx] == '\0')
				*newline = 0;
			else
				break ;
		}
		else if (argv[*idx][0] != '-')
			break ;
		(*idx)++;
	}
}

void	echo(char **argv)
{
	int	idx;
	int	newline;

	newline_check(argv, &idx, &newline);
	while (argv[idx] != NULL)
	{
		if (argv[idx + 1] == NULL)
			printf("%s", argv[idx]);
		else
			printf("%s ", argv[idx]);
		idx++;
	}
	if (newline)
		printf("\n");
}
