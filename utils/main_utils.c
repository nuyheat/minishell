/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:25:40 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/13 13:31:58 by taehkim2         ###   ########.fr       */
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

void	child_wait(void)
{
	while (1)
	{
		if (wait(0) == -1)
			break ;
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
