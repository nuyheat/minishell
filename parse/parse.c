/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 15:03:47 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokenize(t_list **list, char *line)
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

void	parse(t_list **list, char *line)
{
	t_list	*list_head;

	list_head = (*list);
	parse_tokenize(*list, line);
}
