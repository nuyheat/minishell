/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/22 14:03:00 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_print(t_list *list)
{
	int	new_flgs;

	while (list != NULL)
	{
		new_flgs = get_flags(list);
		printf("token : %s\n", get_token(list));
		if (list->info.flgs & F_QUOTED)
			printf("F_QUOTED is on\n");
		if (list->info.flgs & F_NOT_QUOTED)
			printf("F_NOT_QUOTED is on\n");
		if (list->info.flgs & F_LESS)
			printf("F_LESS flag is on\n");
		if (list->info.flgs & F_DLESS)
			printf("F_DLESS flag is on\n");
		if (list->info.flgs & F_GRATE)
			printf("F_GRATE flag is on\n");
		if (list->info.flgs & F_DGRATE)
			printf("F_DGRATE flag is on\n");
		if (list->info.flgs & F_PIPE)
			printf("F_PIPE flag is on\n");
		if (list->info.flgs & F_DOLLAR)
			printf("F_DOLLAR flag is on\n");
		if (list->info.flgs & F_STRING)
			printf("F_STRING flag is on\n");
		list = list->next;
	}
}

int	main(int argc, char **argv, char **envp)
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
			add_history(line);
			parse(&list, line);
			//해석 진행
			//수행 진행
			list_print(list_head);
			list_free(&list_head);
		}
		free(line);
	}
}
