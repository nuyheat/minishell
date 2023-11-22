/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:38:55 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 18:33:25 by taehkim2         ###   ########.fr       */
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


// void	token_quote(char prev_token, char **new_token)
// {

// }

// char	**dollar_expand(char *token, char **envp)
// {
// 	char	**expand_token;

// 	expand_token = malloc(sizeof(char *) * (dollar_cnt(token) + 1));
// 	if (expand_token == NULL)
// 		error_end("malloc failed");

// }

// void	token_expand_dollar(char *now_token, char **new_token, char **envp)
// {
// 	char	**expand_token;
// 	int		idx;

// 	idx = 0;
// 	expand_token = malloc(sizeof(char *) * (dollar_cnt(now_token) + 1));
// 	while (now_token[idx] != '\0')
// 	{
// 		if (now_token[idx])
// 		idx++;
// 	}
// }

char	*translate_token(t_list *list, char **envp)
{
	char	*now_token;
	char	*new_token;

	now_token = list->info.token;
	if ((list->info.flgs & F_QUOTED) && \
		(list->info.flgs & F_DOLLAR))
	{
		dollar_expand(now_token, &new_token, envp);
		quote_delite(now_token, &new_token);
	}
	else if (list->info.flgs & F_QUOTED)
		token_quote(now_token, &new_token);
	else if (list->info.flgs & F_DOLLAR)
		token_dollar(now_token, &new_token, envp);
}
