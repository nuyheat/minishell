/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:08:33 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/27 13:38:20 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_dollar_position(const char *token)
{
	return (ft_strchr(token, '$'));
}

char	*get_variable_name(const char *variable_position)
{
	return (my_strtrim(variable_position + 1, "#$ \t\n\"\'"));
}

char	*get_variable_value(const char *variable_name)
{
	char	*value;

	value = getenv(variable_name);
	if (*variable_name && ft_strncmp(variable_name, "a", ft_strlen(variable_name)) == 0)
		value = ft_strdup("echo HH"); //for test
	if (value == NULL)
	{
		value = ft_calloc(1, sizeof(char));
		if (value == NULL)
			error_end("calloc failed");
	}
	return (value);
}

char	*create_expanded_buffer(const char *token)
{
	int		buffer_length;
	char	*buffer;
	char	*variable_name;
	char	*variable_value;

	variable_name = get_variable_name(token);
	variable_value = get_variable_value(variable_name);
	buffer_length = ft_strlen(token) - (ft_strlen(variable_name) + 1) \
					+ ft_strlen(variable_value);
	buffer = ft_calloc(buffer_length + 1, sizeof(char));
	if (buffer == NULL)
		error_end("calloc failed");
	free(variable_name);
	free(variable_value);
	return (buffer);
}

void	compose_expanded_token(char **buf, const char *token)
{
	char	*pos;
	char	*name;
	char	*value;
	int		length_before_dollar;
	int		length_after_dollar;

	pos = find_dollar_position(token);
	name = get_variable_name(pos);
	value = get_variable_value(name);
	length_before_dollar = ft_strlen(token) - ft_strlen(pos);
	length_after_dollar = ft_strlen(pos + 1 + ft_strlen(name));
	ft_strlcpy(*buf, token, length_before_dollar + 1);
	ft_strlcpy(*buf + ft_strlen(*buf), value, ft_strlen(value) + 1);
	ft_strlcpy(*buf + ft_strlen(*buf), pos + 1 + ft_strlen(name), length_after_dollar + 1);
}
