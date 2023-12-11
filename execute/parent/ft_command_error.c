/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:44 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/11 15:48:32 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_directory(char *command)
{
	char	*current_path;

	if (chdir(command) != -1)
	{
		write(2, "minishell: ", 11);
		write(2, command, ft_strlen(command));
		write(2, ": is a directory\n", 17);
		return (END);
	}
	chdir(current_path);
	return (NEXT);
}

int	is_it_external(char *filename, char **envp)
{
	int		found;
	int		table_idx;
	char	*path;
	char	**path_table;
	char	current_path[BUFSIZ];
	
	found = NEXT;
	table_idx = 0;
	path = ft_getenv("PATH", envp);
	path_table = ft_split(path, ':');
	path = getcwd(current_path, BUFSIZ);
	while (path_table[table_idx] != NULL)
	{
		chdir(path_table[table_idx]);
		if (access(filename, F_OK) == 0)
			found = END;
		table_idx++;
	}
	my_free2(path_table);
	chdir(path);
	return (found);
}

int	is_it_path(char *command, char *path, char *filename)
{
	char	current_path[BUFSIZ];

	getcwd(current_path, BUFSIZ);
	if (chdir(path) == 0 && access(filename, X_OK) == 0)
	{
		chdir(current_path);
		free(path);
		free(filename);
		return (END);
	}
	chdir(current_path);
	free(path);
	free(filename);
	write(2, "minishell: ", 11);
	perror(command);
	return (NEXT);
}

int	command_error(char *token, char **envp)
{
	char	*path;
	char	*filename;

	if (token == NULL)
		return (NEXT);
	else if (is_it_directory(token))
		return (ERROR);
	else if (is_it_builtin(token) || is_it_external(token, envp))
		return (NEXT);
	path = get_path(token);
	filename = get_filename(token);
	if (path != NULL)
	{
		if (is_it_path(token, path, filename))
			return (NEXT);
		else
			return (ERROR);
	}
	write(2, "minishell: ", 11);
	write(2, token, ft_strlen(token));
	write(2, ": command not found\n", 20);
	return (ERROR);
}
