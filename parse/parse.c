/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/24 17:04:43 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_token(t_list **list, char *line)
{
	int		idx;
	char	*buf;

	idx = 0;
	buf = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (buf == NULL)
		error_end("calloc failed");
	while (line[idx] != '\0')
	{
		if (token_rules(list, &buf, line[idx]) == END)
			break ;
		idx++;
	}
	token_delimited(list, &buf);
	free(buf);
}

t_list	*parse(char *line, char **envp)
{
	t_list	*token_list;
	t_list	*token_list_head;
	t_list	*trans_list;
	t_list	*trans_list_head;

	token_list_head = list_init(&token_list);
	parse_token(&token_list, line);
	token_list = token_list_head;
	trans_list_head = list_init(&trans_list);
	translate_token(&token_list, &trans_list);
	list_free(&token_list_head);
	return (trans_list_head);
}
