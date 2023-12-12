/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:10:27 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 22:04:48 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../builtins/builtins.h"

void	my_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	my_free2(char **strs)
{
	int	idx;

	idx = 0;
	while (strs[idx] != NULL)
	{
		my_free(strs[idx]);
		idx++;
	}
}

void	error_end(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	exit(1);
}

char	*ft_getenv(char *name, char **envp)
{
	char	*value;
	char	*result;
	int		envp_index;

	result = NULL;
	value = findenv(name, &envp_index, envp);
	if (value != NULL)
		result = ft_strtrim(value, "=\"");
	return (result);
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
