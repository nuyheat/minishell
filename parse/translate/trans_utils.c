/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:08:33 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/16 14:56:18 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	row_cnt(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx] != NULL)
		idx++;
	return (idx);
}

int	split_cnt(char *token)
{
	int	idx;
	int	dollar_cnt;
	int	another_cnt;

	idx = 0;
	dollar_cnt = 0;
	another_cnt = 0;
	while (token[idx] != '\0')
	{
		if (token[idx] == '$')
			dollar_cnt++;
		if (token[idx] == '\"' || token[idx] == '/' \
			|| token[idx] == '=' || token[idx] == '?' \
			|| token[idx] == '\'' || token[idx] == ' ')
			another_cnt++;
		idx++;
	}
	return (dollar_cnt * 3 + another_cnt + 1);
}

char	**splited_token_init(char *token)
{
	char	**splited_token;

	splited_token = malloc(sizeof(char *) * (split_cnt(token) + 1));
	if (splited_token == NULL)
		error_end("malloc failed");
	splited_token[0] = NULL;
	return (splited_token);
}

int	set_find(char c, char *set)
{
	int	idx;

	idx = 0;
	while (set[idx] != '\0')
	{
		if (c == set[idx])
			return (1);
		idx++;
	}
	return (0);
}
