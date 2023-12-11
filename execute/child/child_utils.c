/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:31:26 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 17:03:17 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_last_order(t_list *list)
{
	while (list != NULL)
	{
		if (list->info.flgs & F_PIPE)
			return (0);
		list = list->next;
	}
	return (1);
}
