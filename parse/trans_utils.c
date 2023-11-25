/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:08:33 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/26 03:40:23 by taehkim2         ###   ########.fr       */
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
	int	dquote_cnt;

	idx = 0;
	dollar_cnt = 0;
	dquote_cnt = 0;
	while (token[idx] != '\0')
	{
		if (token[idx] == '$')
			dollar_cnt++;
		if (token[idx] == '\"')
			dquote_cnt++;
		idx++;
	}
	return (dollar_cnt * 3 + dquote_cnt + 1);
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
