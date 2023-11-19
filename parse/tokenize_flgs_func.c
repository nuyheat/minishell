/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_flgs_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:15:50 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/19 22:44:45 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flgs_quote(int *new_flgs, char now_char)
{
	if (now_char == '\"')
	{
		if ((*new_flgs) & DQUOTE)
			(*new_flgs) |= DQUOTE_END;
		else
			(*new_flgs) |= DQUOTE;
	}
	else if (now_char == '\'')
	{
		if ((*new_flgs) & QUOTE)
			(*new_flgs) |= QUOTE_END;
		else
			(*new_flgs) |= QUOTE;
	}
}
// DQUOTE, QUOTE flgs 설정 함수

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
	else if (now_char == '-')
	{
		if ((*list)->info.flgs & COMMAND)
			(*new_flgs) |= OPTION;
	}
	(*new_flgs) |= STRING;
}
// command flgs 설정 함수 

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
} // redirect flgs 설정 함수

void	flgs_pipe(int *new_flgs, char now_char)
{
	if (!((*new_flgs) & DQUOTE) && !((*new_flgs) & QUOTE))
	{
		if (now_char == '|')
			(*new_flgs) |= PIPE;
	}
} // pipe flgs 설정 함수

void	flgs_dollar(int *new_flgs, char now_char)
{
	if (now_char == '$')
	{
		if (((*new_flgs) & DQUOTE) || ((*new_flgs) & QUOTE))
			(*new_flgs) |= DOLLAR;
		else
			(*new_flgs) |= DOLLAR_PARAM;
	}
} // $ flgs 설정 함수
