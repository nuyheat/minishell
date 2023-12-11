/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:13:03 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/11 15:22:45 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *command)
{
	int		command_len;
	char	*path;

	command_len = ft_strlen(command);
	while (command_len > 0 && command[command_len] != '/')
		command_len--;
	if (command_len == 0)
		return (NULL);
	path = malloc(sizeof(char) * (command_len + 1));
	if (!path)
        error_end("malloc failed");
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
