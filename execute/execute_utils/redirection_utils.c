/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:24:47 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/08 16:28:26 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_change(t_list *list)
{
	free(list->info.token);
	free(list->next->info.token);
	list->info.token = NULL;
	list->info.flgs = F_STRING;
	list->next->info.token = NULL;
	list->next->info.flgs = F_STRING;
}
