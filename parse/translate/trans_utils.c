/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:08:33 by taehkim2          #+#    #+#             */
/*   Updated: 2024/01/15 14:02:44 by taehkim2         ###   ########.fr       */
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

char	**splited_token_init(char *token)
{
	char	**splited_token;

	splited_token = malloc(sizeof(char *) * (ft_strlen(token) + 1));
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
