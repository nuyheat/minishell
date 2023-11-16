/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/16 17:45:41 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse_tokenize
// parse_validation
// parse_make_line


void	flgs_quote(int *new_flgs, char now_char)
{
	if (now_char == '\"' || now_char == '\'')
	{
		if (now_char == '\"')
		{
			if ((*new_flgs) & DQUOTE)
				(*new_flgs) |= DQUOTE_END;
			else
				(*new_flgs) |= DQUOTE;
		}
		else
		{
			if ((*new_flgs) & QUOTE)
				(*new_flgs) |= QUOTE_END;
			else
				(*new_flgs) |= QUOTE;
		}
	}
}

void	flgs_command(t_list **list, int *new_flgs, char now_char)
{
	if ((now_char >= 'a' && now_char <= 'z') \
			|| (now_char >= 'A' && now_char <= 'Z'))
	{
		if ((*list)->info.flags == 0)
			(*new_flgs) |= COMMAND;
		else if ((*list)->info.token[0] == '|')
			(*new_flgs) |= COMMAND;
	}
}

void	flgs_operator(int *new_flgs, char now_char)
{
	if (now_char == '>' || now_char == '<' || now_char == '|')
		(*new_flgs) |= OPERATOR;
}

void	tokenize_flgs(t_list **list, int *new_flgs, char now_char)
{
	flgs_quote(new_flgs, now_char);
	flgs_command(list, new_flgs, now_char);
	flgs_operator(new_flgs, now_char);
}

int	tokenize_six(int new_flgs, char **buf)
{
	if (!(new_flgs & DQUOTE) && !(new_flgs & QUOTE) \
		&& (new_flgs & OPERATOR) && (*buf)[0] != '\0')
		return(1);
	return (0);
}

void	parse_tokenize(t_list **list, char **buf, int *new_flgs, char now_char)
{
	tokenize_flgs(list, new_flgs, now_char);
	// -1번 조건
	// -2번 조건
	// 1번 조건 검사 : 토큰분리규칙 2번
	// 2번 조건 검사 : 토큰분리규칙 3번
	// 3번 조건 검사 : 토큰분리규칙 5번 -- 이시하

	if (tokenize_six(new_flgs, buf))
	{
		parse_token_add(list, *buf, *new_flgs);
		ft_bzero(*buf, ft_strlen(*buf));
		buf[0] = now_char;
	}
	// 4번 조건 검사 : 토큰분리규칙 6번
	// 5번 조건 검사 : 토큰분리규칙 7번
	// 6번 조건 검사 : 토큰분리규칙 8번 -- 김태현
	// 7번 조건 검사 : 토큰분리규칙 9번
}
// 10개의 조건들 검사

void	parse(t_list **list, char *line)
{
	int		idx;
	int		flgs;
	char	*buf;

	idx = 0;
	flgs = 0;
	buf = ft_calloc(sizeof(ft_strlen(line)) + 1);
	if (buf == NULL)
		error_end("malloc failed");
	while (line[idx] != '\0')
	{
		parse_tokenize(list, buf, &flgs, line[idx]);
		idx++;
	}
	free(buf);
}

/*int	main()
{
	t_list	*list;
	int		new_flgs;

	new_flgs = 0;
	list = malloc(sizeof(t_list));
	list->next = NULL;
	list->info.flags = 0;
	tokenize_flgs(&list, &new_flgs, '\"');
	tokenize_flgs(&list, &new_flgs, '\'');
	tokenize_flgs(&list, &new_flgs, '1');
	tokenize_flgs(&list, &new_flgs, '1'); // 안들어감
	tokenize_flgs(&list, &new_flgs, 'a');
	printf("DQUOTE flgs     : %d\n", new_flgs & DQUOTE);
	printf("DQUOTE_END flgs : %d\n", new_flgs & DQUOTE_END);
	printf("QUOTE flgs      : %d\n", new_flgs & QUOTE);
	printf("QUOTE_END flgs  : %d\n", new_flgs & QUOTE_END);
	printf("COMMAND flgs    : %d\n", new_flgs & COMMAND);
}*/ // tokenize_flgs 테스트 코드
