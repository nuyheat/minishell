/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:40:16 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/30 11:19:43 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_skip(char *str, int *idx)
{
	(*idx) += 1;
	while (str[*idx] != '\'')
		(*idx)++;
}

int	is_quoted(char *token, int idx, char quote)
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
