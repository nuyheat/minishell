/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/13 01:27:48 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*list;
	t_pipe			pipes;
	struct termios	terminal;

	(void)argc;
	(void)argv;
	pipes.status = 0;
	interactive_mode_sig();
	ctrl_echo_off(&terminal);
	copy_envp(envp);
	while (1)
	{
		interactive_mode_sig();
		line = line_creat(pipes.status);
		if (line != NULL && line[0] != '\0')
		{
			add_history(line);
			list = parse(line, envp, pipes.status);
			if (list != NULL)
			{
				execute(list, &pipes, envp, &terminal);
				list_free(&list);
			}
		}
		if (line != NULL)
			free(line);
	}
}
