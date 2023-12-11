/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 19:40:38 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	list_print(t_list *list)
// {
// 	int	new_flgs;

// 	while (list != NULL)
// 	{
// 		new_flgs = get_flags(list);
// 		printf("token : %s\n", get_token(list));
// 		if (list->info.flgs & F_QUOTED)
// 			printf("F_QUOTED is on\n");
// 		if (list->info.flgs & F_LESS)
// 			printf("F_LESS flag is on\n");
// 		if (list->info.flgs & F_DLESS)
// 			printf("F_DLESS flag is on\n");
// 		if (list->info.flgs & F_GRATE)
// 			printf("F_GRATE flag is on\n");
// 		if (list->info.flgs & F_DGRATE)
// 			printf("F_DGRATE flag is on\n");
// 		if (list->info.flgs & F_PIPE)
// 			printf("F_PIPE flag is on\n");
// 		if (list->info.flgs & F_DOLLAR)
// 			printf("F_DOLLAR flag is on\n");
// 		if (list->info.flgs & F_STRING)
// 			printf("F_STRING flag is on\n");
// 		list = list->next;
// 	}
// }

// void	le(void)
// {
// 	system("leaks minishell");
// }

int	pipe_find(t_list *list)
{
	while (list != NULL)
	{
		if (list->info.flgs == F_PIPE)
			return (F_PIPE);
		list = list->next;
	}
	return (END);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*list;

	// atexit(le);
	copy_envp(envp);
	while (1)
	{
		line = line_creat();
		if (line[0] != '\0')
		{
			add_history(line);
			list = parse(line, envp);
			if (list != NULL)
			{
				execute(list, envp, pipe_find(list));
				list_free(&list);
			}
		}
		free(line);
	}
}
