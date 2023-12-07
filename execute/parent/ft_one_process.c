/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:51:15 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 15:33:02 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_process(t_list *list, char **envp)
{
	int		pid;
	char	**args;
	char	*command;

	if (is_it_builtin(list->info.token))
	{
		// redirection handling
		args = args_make(list);
		builtin(args, envp);
		args_free(&args);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		// redirection handling
		args = args_make(list);
		simple_command(args, envp);
		args_free(&args);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
