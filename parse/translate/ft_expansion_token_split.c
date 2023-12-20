/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_token_split.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:39:36 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/16 14:55:50 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_split(char *token, char ***result, int start, int end)
{
	int	idx;
	int	row;

	idx = 0;
	row = row_cnt(*result);
	if (start == end)
		return ;
	(*result)[row] = malloc(end - start + 2);
	if ((*result)[row] == 0)
		error_end("malloc failed");
	while (start < end)
		(*result)[row][idx++] = token[start++];
	(*result)[row][idx] = '\0';
	(*result)[row + 1] = NULL;
}

void	not_dequoted_handling(char *token, char ***result, int *idx)
{
	int	start;

	while (token[*idx] != '\0')
	{
		start = *idx;
		if (set_find(token[*idx], "$/?= "))
			(*idx)++;
		while (token[*idx] != '$' && token[*idx] != '\0')
		{
			if (token[start] == '$' && is_quoted1(token, *idx, '\''))
				break ;
			else if (is_quoted1(token, *idx, '\''))
				quote_skip(token, idx);
			if (is_quoted1(token, *idx, '\"') || set_find(token[*idx], "/?= "))
				break ;
			(*idx)++;
		}
		if ((((*idx) - start == 1) && \
			(token[start] == '$' && token[*idx] == '$'))
			|| (token[start] == '$' && token[*idx] == '?'))
			(*idx)++;
		token_split(token, result, start, *idx);
		if (is_quoted1(token, *idx, '\"'))
			break ;
	}
}

void	quoted_handling(char *token, char ***result, int *idx, int *prev_start)
{
	int	start;

	token_split(token, result, *prev_start, *idx);
	token_split("\'", result, 0, 1);
	(*idx)++;
	while (token[*idx] != '\'')
	{
		start = *idx;
		if (set_find(token[*idx], "$/?= "))
			(*idx)++;
		while (token[*idx] != '$')
		{
			if (token[*idx] == '\'' || set_find(token[*idx], "/?= "))
				break ;
			(*idx)++;
		}
		if ((((*idx) - start == 1) && \
			(token[start] == '$' && token[*idx] == '$'))
			|| (token[start] == '$' && token[*idx] == '?'))
			(*idx)++;
		token_split(token, result, start, *idx);
	}
	token_split("\'", result, 0, 1);
	(*prev_start) = (*idx) + 1;
}

void	dequoted_handling(char *token, char ***result, int *idx)
{
	int	start;

	token_split("\"", result, 0, 1);
	(*idx)++;
	while (token[*idx] != '\"')
	{
		start = *idx;
		if (set_find(token[*idx], "$/?= "))
			(*idx)++;
		while (token[*idx] != '$')
		{
			if (is_quoted2(token, *idx, '\''))
				quoted_handling(token, result, idx, &start);
			if (token[*idx] == '\"' || set_find(token[*idx], "/?= "))
				break ;
			(*idx)++;
		}
		if ((((*idx) - start == 1) && (token[start] == '$') && \
			(token[*idx] == '$' || token[*idx] == '?')))
			(*idx)++;
		token_split(token, result, start, *idx);
	}
	token_split("\"", result, 0, 1);
}

char	**expansion_token_split(char *token)
{
	char	**splited_token;
	int		idx;

	idx = 0;
	splited_token = splited_token_init(token);
	while (token[idx] != '\0')
	{
		not_dequoted_handling(token, &splited_token, &idx);
		if (token[idx] == '\0')
			break ;
		dequoted_handling(token, &splited_token, &idx);
		idx++;
	}
	return (splited_token);
}
