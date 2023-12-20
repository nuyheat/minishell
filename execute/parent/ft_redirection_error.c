/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:01:07 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/15 18:34:45 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error_grate(char *token, int *status)
{
	int	fd;

	fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(token);
		*status = 1;
		return (END);
	}
	close(fd);
	return (NEXT);
}

int	redirection_error_dgrate(char *token, int *status)
{
	int	fd;

	fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(token);
		*status = 1;
		return (END);
	}
	close(fd);
	return (NEXT);
}

int	redirection_error_less(char *token, int *status)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		perror(token);
		*status = 1;
		return (END);
	}
	close(fd);
	return (NEXT);
}

int	redirection_error(t_list *list, int *status)
{
	while (list != NULL && list->info.flgs != F_PIPE)
	{
		if (list->info.flgs == F_GRATE)
		{
			if (redirection_error_grate(list->next->info.token, status))
				return (ERROR);
		}
		else if (list->info.flgs == F_DGRATE)
		{
			if (redirection_error_dgrate(list->next->info.token, status))
				return (ERROR);
		}
		else if (list->info.flgs == F_LESS)
		{
			if (redirection_error_less(list->next->info.token, status))
				return (ERROR);
		}
		list = list->next;
	}
	return (NEXT);
}
