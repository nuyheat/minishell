/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/19 06:16:15 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_tokenize(t_list **list, char **buf, char now_char)
{
	if (tokenize_one(buf, now_char))
		return (0); // 토큰분리규칙 2번
	if (tokenize_two(buf, now_char) || tokenize_four(buf, now_char))
	{
		if (ft_strlen(*buf) > 0)
			token_delimited(list, buf);
		(*buf)[0] = now_char;
		return (0);
	}// 토큰분리규칙 3번, 6번
	if (tokenize_five(buf, now_char))
	{
		if (ft_strlen(*buf) > 0)
			token_delimited(list, buf);
		return (0);
	}// 토큰분리규칙 7번
	if (tokenize_seven(buf, now_char))
	{
		if (ft_strlen(*buf) > 0)
			token_delimited(list, buf);
		return (1);
	}// 토큰분리규칙 9번
	tokenize_six(buf, now_char);// 토큰분리규칙 8번
	return (0);
}

void	parse(t_list **list, char *line)
{
	int		idx;
	char	*buf;

	idx = 0;
	buf = ft_calloc(sizeof(ft_strlen(line)) + 1, sizeof(char));
	if (buf == NULL)
		error_end("malloc failed");
	while (line[idx] != '\0')
	{
		if (parse_tokenize(list, &buf, line[idx]))
			break ;
		if (line[idx + 1] == '\0' && buf[0] != '\0')
			token_delimited(list, &buf);
		idx++;
	}
	free(buf);
}
