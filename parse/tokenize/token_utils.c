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

int	is_char(char *line, int now_idx)
{
	char	prev_char;
	int		start_idx;
	int		end_idx;
	int		idx;

	idx = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == '\'' || line[idx] == '\"')
		{
			start_idx = idx;
			prev_char = line[idx++];
			while (line[idx] != prev_char && line[idx] != '\0')
				idx++;
			end_idx = idx;
			if (line[idx] == '\0')
				idx = start_idx;
			else if (start_idx < now_idx && end_idx > now_idx)
				return (0);
		}
		idx++;
	}
	return (1);
}

int	have_quoted(char *buf)
{
	char	prev_char;
	int		start_idx;
	int		idx;

	idx = 0;
	while (buf[idx] != '\0')
	{
		if (buf[idx] == '\"' || buf[idx] == '\'')
		{
			start_idx = idx;
			prev_char = buf[idx++];
			while (buf[idx] != prev_char && buf[idx] != '\0')
				idx++;
			if (buf[idx] == '\0')
				idx = start_idx;
			else
				return (QUOTED);
		}
		idx++;
	}
	return (NOT_QUOTED);
}

int	operator_check(char prev_char)
{
	if (prev_char == '<' || prev_char == '>' || prev_char == '|')
		return (1);
	return (0);
}
