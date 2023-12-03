/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:57:04 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/03 19:16:01 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	syntax_error(t_list *node)
{
	int	flag;

	flag = node->info.flgs;
	if (flag & (F_LESS | F_DLESS | F_DGRATE | F_GRATE) != 0)
	{
		printf("minishell: syntax error near unexpected token");
		printf("`%s'\n", node->info.token);
		return (ERROR);
	}
	return (NEXT);
}

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
