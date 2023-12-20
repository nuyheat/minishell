/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/15 18:48:53 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*list;
	t_pipe			pipes;
	struct termios	terminal;

	(void)argc;
	(void)argv;
	minishell_init(&pipes, &terminal, envp);
	while (1)
	{
		interactive_mode();
		line = line_creat(&(pipes.status));
		if (line != NULL)
		{
			add_history(line);
			list = parse(line, envp, pipes.status);
			free(line);
			if (list != NULL)
			{
				execute(list, &pipes, envp, &terminal);
				list_free(&list);
			}
		}
	}
}
