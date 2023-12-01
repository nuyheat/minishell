/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/01 15:24:53 by sihlee           ###   ########.fr       */
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

void	copy_envp(char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		envp[idx] = ft_strdup(envp[idx]);
		ft_putenv(envp[idx], envp);
		idx++;
	}
}

void	le()
{
	system("leaks minishell");
}


char	**make_args(t_list *list)
{
	char 	**args;
	t_list *list_head;
	int		arg_idx;
	int		idx;

	arg_idx = 0;
	list_head = list;
	while (list != NULL)
	{
		list = list->next;
		arg_idx++;
	}
	args = malloc(sizeof(char *) * (arg_idx + 1));
	if (args == NULL)
		error_end("malloc failed");
	arg_idx = 0;
	while (list_head != NULL)
	{
		idx = 0;
		args[arg_idx] = malloc(ft_strlen(list_head->info.token) + 1);
		if (args[arg_idx] == NULL)
			error_end("malloc failed");
		while (list_head->info.token[idx] != '\0')
		{
			args[arg_idx][idx] = list_head->info.token[idx];
			idx++;
		}
		args[arg_idx][idx] = '\0';
		list_head = list_head->next;
		arg_idx++;
	}
	args[arg_idx] = NULL;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*list;
	char	**args;
	// atexit(le);
	copy_envp(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			error_end("renadline failed");
		if (line[0])
		{
			add_history(line);
			list = parse(line, envp);
			if (list != NULL)
			{
				// list_print(list);
				args = make_args(list);
				list_free(&list);
			}

			//export, unset test
			if (ft_strncmp(args[0], "export", 7) == 0)
				export(args, envp);
			else if (ft_strncmp(args[0], "unset", 7) == 0)
				unset(args, envp);
			//export, unset test fin.

			// args 만든거 free해야함. 줄 수 정리는 나중에 하자
			for (int i = 0; args[i] != NULL; i++)
				free(args[i]);
			free(args);
		}
		free(line);
	}
}
