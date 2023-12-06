/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:57:04 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/06 14:16:49 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	change_fd(int *fd)
{
	int	val;

	if (fd[0] != 0)
	{
		val = dup2(fd[0], STDIN_FILENO);
		if (val == -1)
			return (ERROR);
	}
	if (fd[1] != 1)
	{
		val = dup2(fd[1], STDOUT_FILENO);
		if (val == -1)
			return (ERROR);
	}
	return (END);
}

int	redirection(t_list **list)
{
	t_list	*list_ptr;
	int		fd[2];

	list_ptr = *list;
	fd[0] = 0;
	fd[1] = 1;
	while (list_ptr->next != NULL && !(list_ptr->info.flgs & F_PIPE))
	{
		if (list_ptr->info.flgs & F_LESS)
			less(list_ptr->next, &fd[0]);
		else if (list_ptr->info.flgs & F_DLESS)
			dless(list_ptr->next);
		else if (list_ptr->info.flgs & F_GRATE)
			grate(list_ptr->next, &fd[1]);
		else if (list_ptr->info.flgs & F_DGRATE)
			dgrate(list_ptr->next);
		list_ptr = list_ptr->next;
	}
	change_fd(fd);
	return (NEXT);
}
