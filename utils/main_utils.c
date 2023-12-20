/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:25:40 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/15 11:03:22 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_find(t_list *list)
{
	while (list != NULL)
	{
		if (list->info.flgs == F_PIPE)
			return (F_PIPE);
		list = list->next;
	}
	return (END);
}

void	child_wait(struct termios *terminal)
{
	int	status;

	while (1)
	{
		if (wait(&status) == -1)
		{
			if (status == 2)
				ft_putstr_fd("\n", STDERR_FILENO);
			ctrl_echo_off(terminal);
			break ;
		}
	}
}

void	copy_envp(char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
}

void	minishell_init(t_pipe *pipes, struct termios *terminal, char **envp)
{
	pipes->status = 0;
	ctrl_echo_off(terminal);
	copy_envp(envp);
}
