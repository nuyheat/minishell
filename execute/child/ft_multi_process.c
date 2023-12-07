/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:54:15 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 15:03:28 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child(t_list *list, t_pipe pipe, char **envp)
{
	char	**args;

	// redirection_handling
	args = args_make(list);
	if (builtin(args, envp) == 0)
		// simple_command 호출
	args_free(&args);
	exit(0);
}

void	multi_process(t_list *list, t_pipe *pipe, char **envp)
{
	int	pid;

	// pipe 생성 및 설정
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		child(list, *pipe, envp);
}
