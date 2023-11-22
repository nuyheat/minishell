/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:15:50 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 15:04:30 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flgs_quote(char *buf, int *new_flgs)
{
	int	quote_flg;

	quote_flg = quote_check(buf);
	if (quote_flg == QUOTED)
	{
		if (ft_strchr(buf, '\'') == NULL && ft_strchr(buf, '\"') == NULL)
			return (NEXT);
		(*new_flgs) |= F_QUOTED;
		return (END);
	}
	(*new_flgs) |= F_NOT_QUOTED;
	return (END);
} // quoted, not_quoted 체크한 후 F_DOLLAR 가 존재하면 F_DOLLAR flgs 를 달아준다

void	flgs_quote_dollar(char *buf, int *new_flgs)
{
	int	idx;

	idx = 0;
	while (buf[idx] != '\0')
	{
		if (buf[idx] == '$')
		{
			(*new_flgs) |= F_DOLLAR;
			return ;
		}
		if (buf[idx] == '\'')
		{
			idx++;
			while (buf[idx] != '\'')
				idx++;
		}
		idx++;
	}
}

int	flgs_redirection(char *buf, int *new_flgs)
{
	int	buf_len;

	buf_len = ft_strlen(buf);
	if (buf_len == 1 && buf[0] == '<')
	{
		(*new_flgs) |= F_LESS;
		return (END);
	}
	else if (buf_len == 1 && buf[0] == '>')
	{
		(*new_flgs) |= F_GRATE;
		return (END);
	}
	else if (buf_len == 2 && buf[0] == '<' && buf[1] == '<')
	{
		(*new_flgs) |= F_DLESS;
		return (END);
	}
	else if (buf_len == 2 && buf[0] == '>' && buf[1] == '>')
	{
		(*new_flgs) |= F_DGRATE;
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
		(*new_flgs) |= F_PIPE;
		return (END);
	}
	return (NEXT);
}

int	flgs_dollar(char *buf, int *new_flgs)
{
	int	idx;

	idx = 0;
	while (buf[idx] != '\0')
	{
		if (buf[idx] == '$')
		{
			(*new_flgs) |= F_DOLLAR;
			return (END);
		}
		idx++;
	}
	return (NEXT);
}
