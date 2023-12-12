/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 21:33:04 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*list;
	t_pipe			pipes;
	struct termios	terminal;

	pipes.status = 0;
	interactive_mode_sig();
	copy_envp(envp);
	ctrl_echo_off(&terminal);
	while (1)
	{
		interactive_mode_sig();
		line = line_creat();
		if (line != NULL && line[0] != '\0')
		{
			add_history(line);
			list = parse(line, envp, pipes.status);
			if (list != NULL)
			{
				execute(list, &pipes, envp, pipe_find(list), &terminal);
				list_free(&list);
			}
		}
		if (line != NULL)
			free(line);
	}
}
