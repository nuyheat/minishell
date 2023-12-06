/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:19:47 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/06 20:08:22 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char **args, char **envp)
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

	if (syntax_error(list) == ERROR)
		return ;
	while (list != NULL)
	{
		if (redirection_error(list) == ERROR || \
			command_error(list->info.token, envp) == ERROR)
		{
			args_next(&list);
			continue ;
		}
		if (!builtin(args, envp))
			simple_command(args, envp);
		// 리다이렉션, 파이프가 있다면 result를 특정한 곳으로 보냄
		// list
		// else
		args_next(&list);
	}
}
