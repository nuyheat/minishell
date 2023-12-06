/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:15:40 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/06 20:03:32 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_char(t_list *list, char ***args, int end)
{
	int	args_idx;
	int	idx;

	args_idx = 0;
	while (args_idx < end)
	{
		idx = 0;
		(*args)[args_idx] = malloc(ft_strlen(list->info.token) + 1);
		if ((*args)[args_idx] == NULL)
			error_end("malloc failed");
		while (list->info.token != NULL && list->info.token[idx] != '\0')
		{
			(*args)[args_idx][idx] = list->info.token[idx];
			idx++;
		}
		(*args)[args_idx][idx] = '\0';
		list = list->next;
		args_idx++;
	}
	(*args)[args_idx] = NULL;
}

char	**args_make(t_list **list)
{
	t_list	*list_head;
	char	**args;
	int		args_idx;

	args_idx = 0;
	list_head = *list;
	while (*list != NULL && (*list)->info.flgs != F_PIPE)
	{
		*list = (*list)->next;
		args_idx++;
	}
	if (*list != NULL)
		*list = (*list)->next;
	if (args_idx == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (args_idx + 1));
	if (args == NULL)
		error_end("malloc failed");
	put_char(list_head, &args, args_idx);
	return (args);
}

void	args_free(char ***args)
{
	int	idx;

	idx = 0;
	while ((*args)[idx] != NULL)
		free((*args)[idx++]);
	free(*args);
}

void	args_next(t_list **list)
{
	while ((*list) != NULL && (*list)->info.flgs != F_PIPE)
		(*list) = (*list)->next;
	if ((*list) != NULL && (*list)->info.flgs == F_PIPE)
		(*list) = (*list)->next;
}
