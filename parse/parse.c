/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 14:57:56 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokenize(t_list **list, char *line)
{
	int		idx;
	char	*buf;

	idx = 0;
	if (line[0] == '\0')
	{
		token_add(list, line, F_STRING);
		return ;
	}
	buf = (char *)ft_calloc(ft_strlen(line) + 1, sizeof(char));
	int	i = ft_strlen(line);
	if (buf == NULL)
		error_end("calloc failed");
	while (line[idx] != '\0')
	{
		if (token_rules(list, &buf, line, idx) == END)
			break ;
		idx++;
	}
	token_delimited(list, &buf);
	free(buf);
}

void	parse_translate(t_list *now_list, t_list **new_list, char **envp)
{
	t_list	*new_list_head;
	char	*new_token;

	new_list_head = *new_list;
	while (now_list != NULL)
	{
		if (now_list->info.flgs & F_DOLLAR)
		{
			new_token = trans_param_expansion(now_list->info.token, envp);
			parse_tokenize(new_list, new_token);
			free(new_token);
		}
		else
			token_add(new_list, now_list->info.token, now_list->info.flgs);
		now_list = now_list->next;
	}
	while (new_list_head != NULL)
	{
		if (new_list_head->info.flgs & F_QUOTED)
		{
			trans_quoted_remove(&new_list_head->info.token);
			new_list_head->info.flgs = F_STRING;
		}
		new_list_head = new_list_head->next;
	}
}

t_list	*parse(char *line, char **envp)
{
	t_list	*token_list;
	t_list	*token_list_head;
	t_list	*trans_list;
	t_list	*trans_list_head;

	token_list_head = list_init(&token_list);
	parse_tokenize(&token_list, line);
	if (token_list_head->info.token == NULL)
	{
		free(token_list_head);
		return (NULL);
	}
	trans_list_head = list_init(&trans_list);
	parse_translate(token_list_head, &trans_list, envp);
	list_free(&token_list_head);
	return (trans_list_head);
}
