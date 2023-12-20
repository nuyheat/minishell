/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:16 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/16 14:51:14 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_skip(char *str, int *idx)
{
	(*idx) += 1;
	while (str[*idx] != '\'')
		(*idx)++;
}

int	is_quoted2(char *token, int idx, char quote)
{
	if (token[idx] == quote)
	{
		idx++;
		while (token[idx] != '\"')
		{
			if (token[idx] == quote)
				return (QUOTED);
			idx++;
		}
	}
	return (NOT_QUOTED);
}

int	is_quoted1(char *token, int idx, char quote)
{
	if (token[idx] == quote)
	{
		idx++;
		while (token[idx] != '\0')
		{
			if (token[idx] == quote)
				return (QUOTED);
			idx++;
		}
	}
	return (NOT_QUOTED);
}
