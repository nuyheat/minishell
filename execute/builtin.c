/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:54:31 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 20:16:33 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// return value 확인 필요
char	*builtin(char **args, char **envp)
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
		exit(args);
	free(command);
	command = NULL;
}
