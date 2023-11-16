/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokenization_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:29:45 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/16 11:23:19 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
} // libft 사용할 예정이라서 지워야 함

void	parse_token_add(t_list **list, char *new_token, int new_flags)
// new_flags는 0이 아니어야 한다.
{
	int	token_len;
	int	idx;

	idx = 0;
	token_len = ft_strlen(new_token);
	if ((*list)->info.flags != 0)
		list_add(list);
	(*list)->info.token = malloc(token_len + 1);
	if ((*list)->info.token == NULL)
		error_end("malloc failed");
	while (idx < token_len)
	{
		(*list)->info.token[idx] = new_token[idx];
		idx++;
	}
	(*list)->info.token[idx] = '\0';
	(*list)->info.flags = new_flags;
} // token 문자열 생성

void	le()
{
	system("leaks a.out");
}

/*int main()
{
	t_list	*list;
	t_list	*list_head;
	t_list	*list_head_free;

	atexit(le);
	list_head = list_init(&list);
	list_head_free = list_head;
	parse_token_add(&list, "ls", 1);
	parse_token_add(&list, "cat", 2);
	parse_token_add(&list, "cd", 3);
	parse_token_add(&list, "chmod", 4);
	while (list_head != NULL)
	{
		printf("token : %s\nflags : %d\n", get_token(list_head), get_flags(list_head));
		list_head = list_head->next;
	}
	list_free(&list_head_free);
}*/ // 'parse_token_add' 'list_init' 'list_add' 'list_free' 테스트 코드
