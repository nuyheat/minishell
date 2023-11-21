/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_flgs_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:15:50 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/21 11:12:14 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flgs_quote(int *new_flgs, char now_char)
{
	if (now_char == '\"')
		(*new_flgs) |= DQUOTE;
	else if (now_char == '\'')
		(*new_flgs) |= QUOTE;
}

void	flgs_command(t_list **list, int *new_flgs, char now_char)
{
	if ((now_char >= 'a' && now_char <= 'z') \
			|| (now_char >= 'A' && now_char <= 'Z'))
	{
		if ((*list)->info.flgs == 0)
			(*new_flgs) |= COMMAND;
		else if ((*list)->info.token[0] == '|')
			(*new_flgs) |= COMMAND;
	}
	if (now_char == '-')
	{
		if ((*list)->info.flgs & COMMAND)
			(*new_flgs) |= OPTION;
	}
	(*new_flgs) |= STRING;
}

void	flgs_redirect(int *new_flgs, char now_char)
{
	if (!((*new_flgs) & DQUOTE) && !((*new_flgs) & QUOTE))
	{
		if (now_char == '<')
		{
			if ((*new_flgs) & REDIRECT_LEFT)
				(*new_flgs) |= REDIRECT_LEFT_END;
			else
				(*new_flgs) |= REDIRECT_LEFT;
		}
		else if (now_char == '>')
		{
			if ((*new_flgs) & REDIRECT_RIGHT)
				(*new_flgs) |= REDIRECT_RIGHT_END;
			else
				(*new_flgs) |= REDIRECT_RIGHT;
		}
	}
}

void	flgs_pipe(int *new_flgs, char now_char)
{
	if (!((*new_flgs) & DQUOTE) && !((*new_flgs) & QUOTE))
	{
		if (now_char == '|')
			(*new_flgs) |= PIPE;
	}
}

void	flgs_dollar(int *new_flgs, char now_char)
{
	if (now_char == '$')
		(*new_flgs) |= DOLLAR;
}
// TODO 수정 필요
