/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:15:50 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/21 20:05:46 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flgs_redirection(char *buf, int *new_flgs)
{
	int	buf_len;

	buf_len = ft_strlen(buf);
	if (buf_len == 1 && buf[0] == '<')
	{
		(*new_flgs) |= LESS;
		return (END);
	}
	else if (buf_len == 1 && buf[0] == '>')
	{
		(*new_flgs) |= GRATE;
		return (END);
	}
	else if (buf_len == 2 && buf[0] == '<' && buf[1] == '<')
	{
		(*new_flgs) |= DLESS;
		return (END);
	}
	else if (buf_len == 2 && buf[0] == '>' && buf[1] == '>')
	{
		(*new_flgs) |= DGRATE;
		return (END);
	}
	return (NEXT);
}

int	flgs_pipe(char *buf, int *new_flgs)
{
	int	buf_len;

	buf_len = ft_strlen(buf);
	if (buf_len == 1 && buf[0] == '|')
	{
		(*new_flgs) |= PIPE;
		return (END);
	}
	return (NEXT);
}

int	flgs_dollar(char *buf, int *new_flgs)
{
	int	idx;

	while (buf[idx] != '\0')
	{
		if (buf[idx] == '$')
		{
			(*new_flgs) |= DOLLAR;
			return (END);
		}
	}
	return (NEXT);
}

// void	flgs_quote(int *new_flgs, char now_char)
// {
// 	int	idx;
// 	int	prev_char;

// 	idx = 0;
// 	while (buf[idx] != '\0')
// 	{
// 		if (buf[idx] == '\"' || buf[idx] == '\'')
// 		{
// 			prev_char = buf[idx];

// 			if (prev_char == '\"')
// 				(*new_flgs) |= DQUOTE;
// 			else
// 				(*new_flgs) |= QUOTE;
// 			idx++;

// 			while (buf[idx] != '\n')
// 			{
// 				if (prev_char == buf[idx])
// 					break ;
// 				idx++;
// 			}
// 			if (buf[idx] == '\n')
// 		}
// 		idx++;
// 	}
// 	// if (now_char == '\"')
// 	// 	(*new_flgs) |= DQUOTE;
// 	// else if (now_char == '\'')
// 	// 	(*new_flgs) |= QUOTE;
// }

// void	flgs_command(t_list **list, int *new_flgs, char now_char)
// {
// 	if ((now_char >= 'a' && now_char <= 'z')
// 			|| (now_char >= 'A' && now_char <= 'Z'))
// 	{
// 		if ((*list)->info.flgs == 0)
// 			(*new_flgs) |= COMMAND;
// 		else if ((*list)->info.token[0] == '|')
// 			(*new_flgs) |= COMMAND;
// 	}
// 	if (now_char == '-')
// 	{
// 		if ((*list)->info.flgs & COMMAND)
// 			(*new_flgs) |= OPTION;
// 	}
// 	(*new_flgs) |= STRING;
// }

// void	flgs_redirect(int *new_flgs, char now_char)
// {
// 	if (!((*new_flgs) & DQUOTE) && !((*new_flgs) & QUOTE))
// 	{
// 		if (now_char == '<')
// 		{
// 			if ((*new_flgs) & REDIRECT_LEFT)
// 				(*new_flgs) |= REDIRECT_LEFT_END;
// 			else
// 				(*new_flgs) |= REDIRECT_LEFT;
// 		}
// 		else if (now_char == '>')
// 		{
// 			if ((*new_flgs) & REDIRECT_RIGHT)
// 				(*new_flgs) |= REDIRECT_RIGHT_END;
// 			else
// 				(*new_flgs) |= REDIRECT_RIGHT;
// 		}
// 	}
// }

// void	flgs_pipe(int *new_flgs, char now_char)
// {
// 	if (!((*new_flgs) & DQUOTE) && !((*new_flgs) & QUOTE))
// 	{
// 		if (now_char == '|')
// 			(*new_flgs) |= PIPE;
// 	}
// }

// void	flgs_dollar(int *new_flgs, char now_char)
// {
// 	if (now_char == '$')
// 		(*new_flgs) |= DOLLAR;
// }
// TODO 수정 필요
