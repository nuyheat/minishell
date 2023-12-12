/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:53:12 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 16:57:44 by taehkim2         ###   ########.fr       */
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
