/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:02:15 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 13:13:36 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_pipe(t_list *list, int redirection)
{
	if (list->info.flgs == F_PIPE)
	{
		if (list->next == NULL || (list->next->info.flgs & redirection))
			return (END);
	}
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
			printf("minishell: syntax error near unexpected token");
			printf(" `%s'\n", list->next->info.token);
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

int	syntax_error(t_list *list)
{
	int	redirection;

	redirection = F_GRATE | F_DGRATE | F_LESS | F_DLESS;
	if (syntax_error_pipe(list, redirection))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (ERROR);
	}
	else if (syntax_error_redirection(list, redirection))
		return (ERROR);
	else if (syntax_error_newline(list, redirection))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (ERROR);
	}
	return (NEXT);
}
