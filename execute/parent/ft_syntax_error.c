/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:02:15 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/15 16:45:01 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_pipe(t_list *list, int redirection)
{
	if (list->info.flgs == F_PIPE)
		return (END);
	while (list->next != NULL)
	{
		if (list->info.flgs == F_PIPE && list->next->info.flgs == F_PIPE)
			return (END);
		else if ((list->info.flgs & redirection) && \
				list->next->info.flgs == F_PIPE)
			return (END);
		list = list->next;
	}
	return (NEXT);
}

int	syntax_error_redirection(t_list *list, int redirection)
{
	while (list->next != NULL)
	{
		if ((list->info.flgs & redirection) && \
			(list->next->info.flgs & redirection))
		{
			write(STDERR_FILENO, "syntax error near unexpected token", 34);
			write(STDERR_FILENO, " `", 2);
			write(STDERR_FILENO, list->next->info.token, \
				ft_strlen(list->next->info.token));
			write(STDERR_FILENO, "'\n", 2);
			return (END);
		}
		list = list->next;
	}
	return (NEXT);
}

int	syntax_error_newline(t_list *list, int redirection)
{
	if ((list->info.flgs & redirection) && list->next == NULL)
		return (END);
	while (list->next != NULL)
		list = list->next;
	if (list->info.flgs & redirection)
		return (END);
	return (NEXT);
}

int	syntax_error(t_list *list, int *status)
{
	int	redirection;

	redirection = F_GRATE | F_DGRATE | F_LESS | F_DLESS;
	if (syntax_error_pipe(list, redirection))
	{
		write(STDERR_FILENO, "syntax error near unexpected token `|'\n", 40);
		*status = 258;
		return (ERROR);
	}
	else if (syntax_error_redirection(list, redirection))
	{
		*status = 258;
		return (ERROR);
	}
	else if (syntax_error_newline(list, redirection))
	{
		write(STDERR_FILENO, "syntax error near unexpected token `newline'\n", \
			46);
		*status = 258;
		return (ERROR);
	}
	return (NEXT);
}
