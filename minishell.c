/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/24 15:35:24 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * 토큰 분리 결과를 보여주는 함수입니다. 추후 지울 예정입니다.
 */
// ANSI escape codes for text color
#define COLOR_RESET "\033[0m"
#define COLOR_BOLD "\033[1m"
#define COLOR_CYAN "\033[36m"
#define COLOR_YELLOW "\033[33m"

// Function to print flags with colors
void	print_flag(const char *flag_name, int is_on)
{
	if (is_on)
		printf("%s%s is on%s\n", COLOR_BOLD, flag_name, COLOR_RESET);
}

// Improved list_print function
void	list_print(t_list *list)
{
	int	new_flgs;

	while (list != NULL)
	{
		new_flgs = get_flags(list);

		// Print token with a separator
		printf("%sToken%s: %s\n", COLOR_CYAN, COLOR_RESET, get_token(list));

		// Print flags with colors
		print_flag("F_QUOTED", list->info.flgs & F_QUOTED);
		print_flag("F_NOT_QUOTED", list->info.flgs & F_NOT_QUOTED);
		print_flag("F_LESS", list->info.flgs & F_LESS);
		print_flag("F_DLESS", list->info.flgs & F_DLESS);
		print_flag("F_GRATE", list->info.flgs & F_GRATE);
		print_flag("F_DGRATE", list->info.flgs & F_DGRATE);
		print_flag("F_PIPE", list->info.flgs & F_PIPE);
		print_flag("F_DOLLAR", list->info.flgs & F_DOLLAR);
		print_flag("F_STRING", list->info.flgs & F_STRING);

		// Separator between entries
		printf("%s----------------------------------------%s\n", COLOR_YELLOW, COLOR_RESET);

		list = list->next;
	}
}
/* 
 * 토큰 분리 결과를 보여주는 함수입니다. 추후 지울 예정입니다.
 */

// void	list_print(t_list *list)
// {
// 	int	new_flgs;

// 	while (list != NULL)
// 	{
// 		new_flgs = get_flags(list);
// 		printf("token : %s\n", get_token(list));
// 		if (list->info.flgs & F_QUOTED)
// 			printf("F_QUOTED is on\n");
// 		if (list->info.flgs & F_NOT_QUOTED)
// 			printf("F_NOT_QUOTED is on\n");
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

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*list;

	atexit(leaks);
	// while (1)
	{
		line = readline("minishell$ ");
		if (ft_strchr(line, '\n'))
			printf("is has \\n\n");
		if (line == NULL)
			error_end("readline failed");
		if (line[0])
		{
			add_history(line);
			list = parse(line, envp);
			list_print(list);
			list_free(&list);
		}
		free(line);
	}
}
// void	export(char ***envp)
// {
// 	int	idx;

// 	idx = 0;
// 	while ((*envp)[idx] != NULL)
// 		idx++;
// 	(*envp)[idx] = "asdf";
// 	(*envp)[idx] = NULL;
// }