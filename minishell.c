/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/15 15:29:27 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*line;
	t_token_list	*token_list;
	t_token_list	*token_list_head;

	while (1)
	{
		token_list_head = token_list;
		line = readline("minishell$ ");
		if (line == NULL)
			error_end("readline error");
		parsing(&token_list, line);
		free(line);
	}
}
