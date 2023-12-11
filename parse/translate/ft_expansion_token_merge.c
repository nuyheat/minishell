/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_token_merge.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 20:16:41 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 18:19:08 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_merge(char **merged_token, char **splited_token)
{
	int	split_row;
	int	merge_idx;
	int	idx;

	split_row = 0;
	merge_idx = 0;
	while (splited_token[split_row] != NULL)
	{
		idx = 0;
		while (splited_token[split_row][idx] != '\0')
			(*merged_token)[merge_idx++] = splited_token[split_row][idx++];
		split_row++;
	}
	(*merged_token)[merge_idx] = '\0';
}

char	*expansion_token_merge(char **splited_token)
{
	char	*merged_token;
	int		merge_len;
	int		idx;

	merge_len = 0;
	idx = 0;
	while (splited_token[idx] != NULL)
	{
		merge_len += ft_strlen(splited_token[idx]);
		idx++;
	}
	merged_token = malloc(merge_len + 1);
	if (merged_token == NULL)
		error_end("malloc failed");
	token_merge(&merged_token, splited_token);
	return (merged_token);
}
