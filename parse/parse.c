/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 19:00:10 by taehkim2         ###   ########.fr       */
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

// void	parse_translate(t_list *now_list, t_list **new_list, char **envp)
// {
// 	char	*buf;

// 	while (now_list != NULL)
// 	{
// 		buf = translate_token(now_list, envp);
// 		// if ((prev_list->info.flgs & F_QUOTED) &&
// 		// 	(prev_list->info.flgs & F_DOLLAR))
// 		// {
// 		// 	token_add(new_list, prev_list->info.token, prev_list->info.flgs);
// 		// else if (prev_list->info.flgs & F_QUOTED)
// 		// {

// 		// }
// 		// else if (prev_list->info.flgs & F_DOLLAR)
// 		// {
// 		// 	// 버퍼 만들기 (길이 재서 그 크기만큼 calloc  하여 돌려줌)
// 		// 	// 해당 버퍼에 한 char씩 넣기 ($??? 발견시 -> 환경변수명 구하기. 이후 getenv(환경변수명) 사용)
// 		// 	// 넣는 과정 중 " 나 ' 만나면 넣지 않고 ++.
// 		// 	buf = translate_dollar();
// 		// 	parse_tokenize(new_list, buf);
// 		// 	token_add(new_list, prev_list->info.token, prev_list->info.flgs);
// 		// }
// 		token_add(new_list, buf, now_list->info.flgs);
// 		now_list = now_list->next;
// 	}
// }

t_list	*parse(char *line, char **envp)
{
	t_list	*token_list;
	t_list	*token_list_head;
	t_list	*trans_list;
	t_list	*trans_list_head;

	token_list_head = list_init(&token_list);
	parse_tokenize(&token_list, line);
	//trans_list_head = list_init(&trans_list);
	//parse_translate(token_list_head, &trans_list, envp);
	//list_free(&token_list_head);
	return (token_list_head);
}
