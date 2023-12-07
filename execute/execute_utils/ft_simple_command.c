/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:52:44 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 15:06:46 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_path(char *path, char *filename)
{
	char	*result;
	int		path_len;
	int		filename_len;

	path_len = ft_strlen(path);
	filename_len = ft_strlen(filename);
	result = malloc(sizeof(char) * (path_len + filename_len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, path, path_len + 1);
	result[path_len] = '/';
	ft_strlcpy(result + path_len + 1, filename, filename_len + 1);
	return (result);
}

char	*get_external_path(char *command, char **envp)
{
	char	*found;
	int		table_idx;
	char	*path;
	char	**path_table;
	char	current_path[BUFSIZ];

	found = NULL;
	table_idx = 0;
	path = ft_getenv("PATH", envp);
	path_table = ft_split(path, ':');
	path = getcwd(current_path, BUFSIZ);
	while (path_table[table_idx] != NULL)
	{
		chdir(path_table[table_idx]);
		if (access(command, F_OK) == 0)
			found = make_path(path_table[table_idx], command);
		table_idx++;
	}
	my_free2(path_table);
	chdir(path);
	return (found);
}

void	simple_command(char **args, char **envp)
{
	char	*command;

	command = get_external_path(args[0], envp);
	execve(command, args, envp);
}
