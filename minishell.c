/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/15 21:24:43 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*line;
	t_token_list	*list;
	t_token_list	*list_head;

	while (1)
	{
		list_head = list_init(&list);
		line = readline("minishell$ ");
		if (line == NULL)
			error_end("readline error");
		parse(&list, line);
		list_free(&list_head);
		free(line);
	}
}
