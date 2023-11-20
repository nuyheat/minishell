/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:53:12 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 16:52:42 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_add(t_list **list)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (new_list == NULL)
		error_end("malloc failed");
	new_list->next = NULL;
	(*list)->next = new_list;
	(*list) = (*list)->next;
}
// 연결리스트 노드 추가

t_list	*list_init(t_list **list)
{
	(*list) = malloc(sizeof(t_list));
	if (list == NULL)
		error_end("malloc failed");
	(*list)->info.flgs = 0;
	(*list)->info.token = NULL;
	(*list)->next = NULL;
	return (*list);
}
// 연결리스트 생성

void	list_free(t_list **list)
{
	t_list	*temp;

	while (*list != NULL)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->info.token != NULL)
			free(temp->info.token);
		free(temp);
	}
}
// 연결리스트 메모리 해제
