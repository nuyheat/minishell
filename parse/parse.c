/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 21:44:52 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_tokenize(t_list **list, char **buf, char now_char)
{
	if (tokenize_operator_double(buf, now_char))
		return (NEXT);
	if (tokenize_operator_start(buf, now_char) \
		|| tokenize_operator_end(buf, now_char))
	{
		token_delimited(list, buf);
		if (now_char != ' ')
			(*buf)[0] = now_char;
		return (NEXT);
	}
	if (tokenize_space(buf, now_char))
	{
		token_delimited(list, buf);
		return (NEXT);
	}
	if (tokenize_comment(buf, now_char))
	{
		token_delimited(list, buf);
		return (END);
	}
	(*buf)[ft_strlen(*buf)] = now_char;
	return (NEXT);
}

void	parse(t_list **list, char *line)
{
	int		idx;
	char	*buf;

	idx = 0;
	buf = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (buf == NULL)
		error_end("malloc failed");
	while (line[idx] != '\0')
	{
		if (parse_tokenize(list, &buf, line[idx]) == END)
			break ;
		idx++;
	}
	token_delimited(list, &buf);
	free(buf);
}
