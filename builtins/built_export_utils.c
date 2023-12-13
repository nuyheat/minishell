/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:50:45 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/13 17:43:31 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	printexport(char **envp)
{
	char	**envp_ptr;
	char	*equal;

	envp_ptr = envp;
	while (*envp_ptr != NULL)
	{
		write(1, *envp_ptr, namelen(*envp_ptr, '='));
		equal = ft_strchr(*envp_ptr, '=');
		if (equal != NULL)
		{
			write(1, "=\"", 2);
			equal++;
			write(1, equal, ft_strlen(equal));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		envp_ptr++;
	}
}

int	countchar(const char *str, char find)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == find)
			count++;
		i++;
	}
	return (count);
}

int	namelen(const char *str, char find)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && (str[i] != find))
		i++;
	return (i);
}

int	comparename(const char *have_to_find, const char *now_im_at)
{
	int	len1;
	int	len2;

	len1 = namelen(have_to_find, '=');
	len2 = namelen(now_im_at, '=');
	if (len1 == len2)
	{
		if (ft_strncmp(have_to_find, now_im_at, len1) == 0)
			return (len1);
	}
	return (0);
}

int	name_ok(const char *str)
{
	int		name_len;
	int		str_idx;
	char	*equal;

	name_len = namelen(str, '=');
	equal = ft_strchr(str, '=');
	if (name_len == 0)
		return (0);
	str_idx = 0;
	while (str_idx < name_len)
	{
		if (str[str_idx] == '/' || str[str_idx] == '.' || str[str_idx] == ' ')
			return (0);
		str_idx++;
	}
	return (1);
}
