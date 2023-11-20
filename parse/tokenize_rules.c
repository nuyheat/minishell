/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:29:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 23:00:37 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_operator_double(char **buf, char now_char)
{
	int		buf_len;
	char	prev_char;

	buf_len = ft_strlen(*buf);
	if (buf_len == 1)
	{
		prev_char = (*buf)[0];
		if ((now_char == '<' && prev_char == '<') || \
			(now_char == '>' && prev_char == '>'))
		{
			(*buf)[1] = now_char;
			return (1);
		}
	}
	return (0);
}

// int	tokenize_operator_end(char **buf, char now_char)
// {
// 	int		buf_len;

// 	buf_len = ft_strlen(*buf);
// 	if (buf_len == 1 && operator_check((*buf)[0]))
// 	{
// 		if ((now_char == '<' && (*buf)[0] == '<') || \
// 			(now_char == '>' && (*buf)[0] == '>'))
// 			return (0);
// 		return (1);
// 	}
// 	else if (buf_len == 2 && operator_check((*buf)[0]) \
// 		&& operator_check((*buf)[1]))
// 		return (1);
// 	return (0);
// }

int	tokenize_operator_end(char **buf, char now_char)
{
	int	buf_len;
	
	buf_len = ft_strlen(*buf);
	if (buf_len == 1 || buf_len == 2)
	{
		if (operator_check((*buf)[0]))
		{
			if (buf_len == 1 || operator_check((*buf)[1]))
				return (1);
		}
	}
	return (0);
}

// int	tokenize_operator_start(char **buf, char now_char)
// {
// 	int		buf_len;

// 	buf_len = ft_strlen(*buf);
// 	if (buf_len == 0 && operator_check(now_char))
// 		return (1);
// 	else if (operator_check(now_char) && quote_check(*buf))
// 	{
// 		if (buf_len == 1)
// 		{
// 			if (((now_char == '<' && (*buf)[0] == '<') || \
// 				(now_char == '>' && (*buf)[0] == '>')))
// 				return (0);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

int	tokenize_operator_start(char **buf, char now_char)
{
	int	buf_len;

	buf_len = ft_strlen(*buf);
	if (operator_check(now_char))
	{
		if (buf_len == 0 || quote_check(*buf))
			return (1);
	}
	return (0);
}

int	tokenize_space(char **buf, char now_char)
{
	int	buf_len;

	buf_len = ft_strlen(*buf);
	if (now_char == ' ')
	{
		if (buf_len == 0)
			return (1);
		if (quote_check(*buf))
			return (1);
	}
	return (0);
}

// void	tokenize_six(char **buf, char now_char)
// {
// 	int	buf_len;

// 	buf_len = ft_strlen(*buf);
// 	(*buf)[buf_len] = now_char;
// }

int	tokenize_comment(char **buf, char now_char)
{
	int	buf_len;

	buf_len = ft_strlen(*buf);
	if (now_char == '#')
	{
		if (buf_len == 0 || quote_check(*buf))
			return (1);
	}
	return (0);
}
