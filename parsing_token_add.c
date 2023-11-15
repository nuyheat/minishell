/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:33:17 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/15 19:38:29 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}
// libft 사용할 예정이라서 지워야 함함

void	list_add(t_token_list **list)
{
	t_token_list	*new_list;

	new_list = malloc(sizeof(t_token_list));
	if (new_list == NULL)
		error_end("malloc failed");
	new_list->next = NULL;
	(*list)->next = new_list;
	(*list) = (*list)->next;
}
// 연결리스트 노드 생성

void	token_add(t_token_list **list, char *new_token, int new_flags)
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
}

// token 문자열 생성

int main()
{
	t_token_list	*list;
	t_token_list	*list_head;

	list = malloc(sizeof(t_token_list));
	if (list == NULL)
		error_end("malloc failed");
	list->info.flags = 0;
	list->next = NULL;
	list_head = list;
	token_add(&list, "ls", 1);
	token_add(&list, "cat", 2);
	while (list_head != NULL)
	{
		printf("token : %s\nflags : %d\n", get_token(list_head), get_flags(list_head));
		list_head = list_head->next;
	}
}
