/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:10:27 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/15 19:33:03 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_end(char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
}

char	*get_token(t_token_list *list)
{
	return (list->info.token);
}

int	get_flags(t_token_list *list)
{
	return (list->info.flags);
}

/*void	token_list_free(t_token_list *token_list)
{
	t_token_list	*tmp;

	tmp
	while (token_list->next != NULL)
	{
		free(token_list->token_info->token);
		free(token_list);
	}
}*/
