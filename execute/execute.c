/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:25:55 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/03 18:41:49 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_char(t_list *list, char ***args, int end)
{
	int	args_idx;
	int	idx;

	args_idx = 0;
	while (args_idx < end)
	{
		idx = 0;
		(*args)[args_idx] = malloc(ft_strlen(list->info.token) + 1);
		if ((*args)[args_idx] == NULL)
			error_end("malloc failed");
		while (list->info.token != NULL && list->info.token[idx] != '\0')
		{
			(*args)[args_idx][idx] = list->info.token[idx];
			idx++;
		}
		(*args)[args_idx][idx] = '\0';
		list = list->next;
		args_idx++;
	}
	(*args)[args_idx] = NULL;
}

char	**args_make(t_list **list)
{
	t_list	*list_head;
	char	**args;
	int		args_idx;

	args_idx = 0;
	list_head = *list;
	while (*list != NULL && (*list)->info.flgs != F_PIPE)
	{
		*list = (*list)->next;
		args_idx++;
	}
	if (*list != NULL)
		*list = (*list)->next;
	if (args_idx == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (args_idx + 1));
	if (args == NULL)
		error_end("malloc failed");
	put_char(list_head, &args, args_idx);
	return (args);
}

void	args_free(char ***args)
{
	int	idx;

	idx = 0;
	while ((*args)[idx] != NULL)
		free((*args)[idx++]);
	free(*args);
}

int	*builtin(char **args, char **envp)
{
	char	*command;

	command = args[0];
	if (ft_strncmp(command, "echo", 3) == 0)
		echo(args);
	else if (ft_strncmp(command, "cd", 5) == 0)
		cd(args);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		pwd(args);
	else if (ft_strncmp(command, "export", 7) == 0)
		export(args, envp);
	else if (ft_strncmp(command, "unset", 6) == 0)
		unset(args, envp);
	else if (ft_strncmp(command, "env", 4) == 0)
		env(args, envp);
	else if (ft_strncmp(command, "exit", 5) == 0)
		my_exit(args);
	else
		return (0);
	return (1);
}

char	*simple_command(char **args, char **envp)
{
	(void)args;
	(void)envp;
	return (NULL);
}

void	execute(t_list *list, char **envp)
{
	char	**args;
	int		error_check;

	while (list != NULL)
	{
 		if (redirection(&list) == ERROR)
			break ;
		args = args_make(&list);
		if (!builtin(args, envp))
			simple_command(args, envp);
		// 리다이렉션, 파이프가 있다면 result를 특정한 곳으로 보냄
		// list
		// else
		args_free(&args);
	}
}
