/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:53:12 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/03 18:21:30 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_node_add(t_list **list)
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
	(*list)->info.flgs = START;
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

t_list	*list_delete(t_list **list, t_list **trash)
{
	t_list	*ptr;

	ptr = *list;
	if (ptr == (*trash))
	{
		ptr = ptr->next;
		(*trash)->next = NULL;
		list_free(trash);
		return (ptr);
	}
	while (ptr->next != (*trash))
		ptr = ptr->next;
	if (ptr->next == (*trash))
	{
		ptr->next = ptr->next->next;
		(*trash)->next = NULL;
		list_free(trash);
	}
	return (*list);
}
