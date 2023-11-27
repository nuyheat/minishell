/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:38:55 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/27 13:46:58 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	dollar_cnt(char *token)
// {
// 	int	idx;
// 	int	dollar_cnt;

// 	idx = 0;
// 	while (token[idx] != '\0')
// 	{
// 		if (token[idx] == '$')
// 			dollar_cnt++;
// 		idx++;
// 	}
// 	return (dollar_cnt);
// }

void	dollar_expand(t_list **token_list)
{
	t_list	*list_ptr;
	char	*token;
	char	*dollar_position;
	char	*buf;

	list_ptr = *token_list;
	while ((list_ptr != NULL))
	{
		if (get_flags(list_ptr) & F_DOLLAR)
		{
			token = list_ptr->info.token;
			while (find_dollar_position(token) != NULL)
			{
				dollar_position = find_dollar_position(token);
				buf = create_expanded_buffer(token);
				compose_expanded_token(&buf, token);
				free(token);
				token = NULL;
				list_ptr->info.token = buf;
				token = list_ptr->info.token;
			}
		}
		list_ptr = (list_ptr)->next;
	}	
}

void	move_content(t_list **old, t_list **new)
{
	t_list	*old_ptr;

	old_ptr = *old;
	while (old_ptr != NULL)
	{
		parse_token(new, old_ptr->info.token);
		old_ptr = old_ptr->next;
	}
}

void	quote_delimit(t_list **trans_list)
{
	t_list	*trans_list_ptr;
	char	*token;
	char	*buf;
	int		token_idx;
	int		buf_idx;

	trans_list_ptr = *trans_list;
	while (trans_list_ptr != NULL)
	{
		token = trans_list_ptr->info.token;
		if ((token != NULL) && (trans_list_ptr->info.flgs & F_QUOTED))
		{
			buf = ft_calloc(ft_strlen(token) + 1, sizeof(char));
			token_idx = 0;
			buf_idx = 0;
			while (token[token_idx] != '\0')
			{
				if ((token[token_idx] != '\"') && (token[token_idx] != '\''))
				{
					buf[buf_idx] = token[token_idx];
					buf_idx++;
				}
				token_idx++;
			}
			free(trans_list_ptr->info.token);
			trans_list_ptr->info.token = NULL;
			trans_list_ptr->info.token = buf;
		}
		trans_list_ptr = trans_list_ptr->next;
	}
}

void	translate_token(t_list **token_list, t_list **trans_list)
{
	dollar_expand(token_list);
	move_content(token_list, trans_list);
	quote_delimit(trans_list);
}
