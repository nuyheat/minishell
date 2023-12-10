/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:03:36 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/10 19:30:27 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_find(t_list *list)
{
	int	redirection;

	redirection = F_LESS | F_DLESS | F_GRATE | F_DGRATE;
	while (list != NULL && list->info.flgs != F_PIPE)
	{
		if (list->info.flgs & redirection)
			list = list->next;
		else
			return (list->info.token);
		list = list->next;
	}
	return (NULL);
}

void	pipe_setting_for_parent(t_pipe *pipes)
{
	if (pipes->prev_fd[0] != -1 && pipes->prev_fd[1] != -1)
	{
		close(pipes->prev_fd[0]);
		close(pipes->prev_fd[1]);
	}
	pipes->prev_fd[0] = pipes->next_fd[0];
	pipes->prev_fd[1] = pipes->next_fd[1];
}
