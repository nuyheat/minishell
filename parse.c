/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/16 15:37:45 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parse_tokenize
// parse_validation
// parse_make_line

int	parse_tokenize_six(char **buf, int *flags, char now_char, char prev_char)
{

}



void	parse_tokenize(t_list **list, char *buf, char now_char)
{
	int	new_flags;

	new_flags = 0;
	// -1번 조건
	// -2번 조건
	// 1번 조건 검사 : 토큰분리규칙 2번
	// 2번 조건 검사 : 토큰분리규칙 3번
	// 3번 조건 검사 : 토큰분리규칙 5번 -- 이시하


	// 4번 조건 검사 : 토큰분리규칙 6번
	// 5번 조건 검사 : 토큰분리규칙 7번
	// 6번 조건 검사 : 토큰분리규칙 8번 -- 김태현
	// 7번 조건 검사 : 토큰분리규칙 9번
}
// 10개의 조건들 검사

void	parse(t_list **list, char *line)
{
	int		idx;
	char	*buffer;

	idx = 0;
	buffer = ft_calloc(sizeof(ft_strlen(line)) + 1);
	if (buffer == NULL)
		error_end("malloc failed");
	while (line[idx] != '\0')
	{
		parse_tokenize(list, buffer, line[idx]);
		idx++;
	}
	free(buffer);
}


int main()
{
	int flag;

	flag = func_two;

	if (flag == 1)
		printf("OK\n");
	else if (flag == 0)
		printf("KO\n");
}
