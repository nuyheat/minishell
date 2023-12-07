/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:25:40 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 13:13:33 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_envp(char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
}

char	*my_strjoin(char **s1, char *s2)
{
	void	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	ptr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr)
	{
		ft_bzero(ptr, (s1_len + s2_len + 1) * sizeof(char));
		ft_memmove(ptr, *s1, s1_len);
		ft_memmove(ptr + s1_len, s2, s2_len + 1);
		free(*s1);
		return (ptr);
	}
	return (NULL);
}

int	line_check(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len == 1 && line[0] == '|')
		return (END);
	else if (line[len - 1] == '|')
	{
		len -= 2;
		while (len >= 0 && line[len] == ' ')
			len--;
		if (len == -1)
			return (END);
		else if (line[len] == '|' || line[len] == '<' || line[len] == '>')
			return (END);
		return (NEXT);
	}
	return (END);
}

char	*line_creat(void)
{
	char	*line;
	char	*tmp;

	line = readline("minishell$ ");
	if (line == NULL)
		error_end("readline failed");
	if (line[0] == '\0')
		return (line);
	while (1)
	{
		if (line_check(line))
			break ;
		tmp = readline("> ");
		if (tmp == NULL)
			error_end("readline failed");
		line = my_strjoin(&line, tmp);
		if (line == NULL)
			error_end("malloc failed");
		free(tmp);
	}
	return (line);
}
