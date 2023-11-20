/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:29:45 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 22:59:19 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_delimited(t_list **list, char **buf)
{
	int	new_flgs;
	int	idx;

	new_flgs = 0;
	idx = 0;
	if ((*buf)[0] == '\0')
		return ;
	while ((*buf)[idx] != '\0')
	{
		tokenize_flgs(list, &new_flgs, (*buf)[idx]);
		idx++;
	}
	token_add(list, *buf, new_flgs);
	ft_bzero(*buf, ft_strlen(*buf));
}

void	token_add(t_list **list, char *new_token, int new_flags)
{
	int	token_len;
	int	idx;

	idx = 0;
	token_len = ft_strlen(new_token);
	if ((*list)->info.flgs != 0)
		list_node_add(list);
	(*list)->info.token = malloc(token_len + 1);
	if ((*list)->info.token == NULL)
		error_end("malloc failed");
	while (idx < token_len)
	{
		(*list)->info.token[idx] = new_token[idx];
		idx++;
	}
	(*list)->info.token[idx] = '\0';
	(*list)->info.flgs = new_flags;
}

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

// int	operator_check(char *buf)
// {
// 	int	idx;

// 	idx = 0;
// 	while (buf[idx] != '\0')
// 	{
// 		if (buf[idx] != '<' && buf[idx] != '>' && buf[idx] == '|')
// 			return (1);
// 	}
// 	return (0);
// }

int	operator_check(char prev_char)
{
	if (prev_char == '<' || prev_char == '>' || prev_char == '|')
		return (1);
	return (0);
}
