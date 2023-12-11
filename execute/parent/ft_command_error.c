/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:44 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/11 12:19:54 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_it_directory(char *command)
{
	char	*current_path;

	if (chdir(command) == 0)
	{
		printf("minishell: %s: is a directory\n", command);
		return (END);
	}
	chdir(current_path);
	return (NEXT);
}

char	*get_path(char *command)
{
	int		command_len;
	char	*path;

	command_len = ft_strlen(command);
	while (command_len > 0 && command[command_len] != '/')
		command_len--;
	path = malloc(sizeof(char) * (command_len + 1));
	if (!path)
		return (NULL);
	ft_strlcpy(path, command, command_len + 1);
	return (path);
}

char	*get_filename(char *command)
{
	int		command_len;
	char	*filename;

	command_len = ft_strlen(command);
	while (command_len > 0 && command[command_len] != '/')
		command_len--;
	filename = malloc(sizeof(char) * (ft_strlen(command) - command_len + 1));
	if (!filename)
		return (NULL);
	ft_strlcpy(filename, command + command_len + 1, \
				ft_strlen(command) - command_len);
	return (filename);
}

int	is_it_external(char *filename, char **envp)
{
	int		found;
	int		table_idx;
	char	*path;
	char	**path_table;
	char	current_path[BUFSIZ];

	found = 0;
	table_idx = 0;
	path = ft_getenv("PATH", envp);
	path_table = ft_split(path, ':');
	path = getcwd(current_path, BUFSIZ);
	while (path_table[table_idx] != NULL)
	{
		chdir(path_table[table_idx]);
		if (access(filename, F_OK) == 0)
			found = 1;
		table_idx++;
	}
	my_free2(path_table);
	chdir(path);
	return (found);
}

int	command_error(char *token, char **envp)
{
	char	current_path[BUFSIZ];
	char	*path;
	char	*filename;

	if (token == NULL || is_it_builtin(token) || is_it_external(token, envp))
		return (NEXT);
	if (is_it_directory(token))
		return (ERROR);
	path = get_path(token);
	filename = get_filename(token);
	getcwd(current_path, BUFSIZ);
	if (chdir(path) == 0)
	{
		if (access(filename, X_OK) == -1)
		{
			write(2, "minishell: ", 11);
			perror(token);
			chdir(current_path);
			return (ERROR);
		}
		chdir(current_path);
		return (NEXT);
	}
	printf("minishell: %s: command not found\n", token);
	return (ERROR);
}
