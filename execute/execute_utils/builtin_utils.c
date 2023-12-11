/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:55:16 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/08 17:34:58 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_builtin(char *command)
{
	if (command == NULL)
		return (NEXT);
	if (ft_strncmp(command, "echo", 5) == 0 || \
		ft_strncmp(command, "cd", 3) == 0 || \
		ft_strncmp(command, "pwd", 4) == 0 || \
		ft_strncmp(command, "export", 7) == 0 || \
		ft_strncmp(command, "unset", 6) == 0 || \
		ft_strncmp(command, "env", 4) == 0 || \
		ft_strncmp(command, "exit", 5) == 0)
		return (END);
	return (NEXT);
}

int	builtin(char **args, char **envp)
{
	char	*command;

	command = args[0];
	if (ft_strncmp(command, "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(command, "cd", 3) == 0)
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