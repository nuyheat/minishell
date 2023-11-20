/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 21:46:05 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_print(t_list *list_head)
{
	int new_flgs;

	while (list_head != NULL)
	{
		new_flgs = get_flags(list_head);
		printf("token : %s\n", get_token(list_head));
		// printf("COMMAND           : %d\n", new_flgs & COMMAND);
		// printf("OPTION 	          : %d\n", new_flgs & OPTION);
		// printf("STRING            : %d\n", new_flgs & STRING);
		// printf("DQUOTE            : %d\n", new_flgs & DQUOTE);
		// printf("DQUOTE_END        : %d\n", new_flgs & DQUOTE_END);
		// printf("QUOTE             : %d\n", new_flgs & QUOTE);
		// printf("QUOTE_END         : %d\n", new_flgs & QUOTE_END);
		// printf("REDIRECT_LEFT     : %d\n", new_flgs & REDIRECT_LEFT);
		// printf("REDIRECT_LEFT_END : %d\n", new_flgs & REDIRECT_LEFT_END);
		// printf("REDIRECT_RIGHT    : %d\n", new_flgs & REDIRECT_RIGHT);
		// printf("REDIRECT_RIGHT_END: %d\n", new_flgs & REDIRECT_RIGHT_END);
		// printf("PIPE              : %d\n", new_flgs & PIPE);
		// printf("DOLLAR            : %d\n", new_flgs & DOLLAR);
		// printf("DOLLAR_PARAM      : %d\n\n", new_flgs & DOLLAR_PARAM);
		list_head = list_head->next;
	}
}

int	main(void)
{
	char	*line;
	t_list	*list;
	t_list	*list_head;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			error_end("readline error");
		if (line[0])
		{
			list_head = list_init(&list);
			parse(&list, line);
			//해석 진행
			//수행 진행
			list_print(list_head);
			list_free(&list_head);
		}
		free(line);
	}
}
