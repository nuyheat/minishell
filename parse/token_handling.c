/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:25:04 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/27 15:19:24 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_rules(t_list **list, char **buf, char now_char)
{
	if (rules_operator_double(buf, now_char))
		return (NEXT);
	if (rules_operator_start(buf, now_char) \
		|| rules_operator_end(buf, now_char))
	{
		token_delimited(list, buf);
		if (now_char != ' ')
			(*buf)[0] = now_char;
		return (NEXT);
	}
	if (rules_space(buf, now_char))
	{
		token_delimited(list, buf);
		return (NEXT);
	}
	if (rules_comment(buf, now_char))
	{
		token_delimited(list, buf);
		return (END);
	}
	(*buf)[ft_strlen(*buf)] = now_char;
	return (NEXT);
}

void	token_flgs(t_list **list, int *new_flgs, char *buf)
{
	int	buf_len;

	buf_len = ft_strlen(buf);
	if (flgs_quote(buf, new_flgs))
	{
		if ((*new_flgs) == F_QUOTED)
			flgs_quote_dollar(buf, new_flgs);
		return ;
	}
	else if (flgs_redirection(buf, new_flgs))
		return ;
	else if (flgs_pipe(buf, new_flgs))
		return ;
	else if (flgs_dollar(buf, new_flgs))
		return ;
	(*new_flgs) |= F_STRING;
}

void	token_delimited(t_list **list, char **buf)
{
	int	new_flgs;
	int	idx;

	new_flgs = 0;
	idx = 0;
	if ((*buf)[0] == '\0')
		return ;
	token_flgs(list, &new_flgs, *buf);
	token_add(list, *buf, new_flgs);
	ft_bzero(*buf, ft_strlen(*buf));
}

void	token_add(t_list **list, char *new_token, int new_flags)
{
	int	token_len;
	int	idx;

	idx = 0;
	token_len = ft_strlen(new_token);
	if ((*list)->info.flgs != START)
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
