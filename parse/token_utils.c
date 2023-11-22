/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:29:45 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 12:24:22 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check_flgs(char *buf, int *idx)
{
	char	prev_char;

	prev_char = buf[*idx];
	(*idx)++;
	while (buf[*idx] != '\0')
	{
		if (buf[*idx] == prev_char)
			return (QUOTED);
		(*idx)++;
	}
	return (NOT_QUOTED);
}

int	quote_check(char *buf)
{
	int		idx;
	int		flgs;

	idx = 0;
	flgs = QUOTED;
	while (buf[idx] != '\0')
	{
		if (buf[idx] == '\"' || buf[idx] == '\'')
			flgs = quote_check_flgs(buf, &idx);
		if (buf[idx] == '\0')
			return (flgs);
		idx++;
	}
	return (flgs);
}

int	operator_check(char prev_char)
{
	if (prev_char == '<' || prev_char == '>' || prev_char == '|')
		return (1);
	return (0);
}
