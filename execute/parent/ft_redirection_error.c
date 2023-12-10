/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:01:07 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 01:35:44 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error_grate(char *token)
{
	if (access(token, W_OK) == 1)
	{
		write(2, "minishell: ", 11);
		perror(token);
		return (END);
	}
	return (NEXT);
}

int	redirection_error_less(char *token)
{
	if (access(token, F_OK) == 1)
	{
		write(2, "minishell: ", 11);
		perror(token);
		return (END);
	}
	else if (access(token, R_OK) == 1)
	{
		write(2, "minishell: ", 11);
		perror(token);
		return (END);
	}
	return (NEXT);
}

int	redirection_error(t_list *list)
{
	while (list != NULL && list->info.flgs != F_PIPE)
	{
		if (list->info.flgs == F_GRATE || list->info.flgs == F_DGRATE)
		{
			list = list->next;
			if (redirection_error_grate(list->info.token))
				return (ERROR);
		}
		else if (list->info.flgs == F_LESS)
		{
			list = list->next;
			if (redirection_error_less(list->info.token))
				return (ERROR);
		}
		list = list->next;
	}
	return (NEXT);
}
