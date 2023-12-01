/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 20:21:19 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_setenv(const char *name, const char *value, char **envp)
{
	char	*change_here;
	int		idx;
	int		name_len;
	int		value_len;

	name_len = namelen(name, '=');
	value_len = ft_strlen(value);
	change_here = findenv(name, &idx, envp);
	if (change_here == NULL)
	{
		envp[idx] = malloc(name_len + 2 + value_len + 2);
		ft_memmove(envp[idx], name, name_len);
	}
	else
		envp[idx] = ft_realloc(envp[idx], (name_len + 2 + value_len + 2));
	change_here = findenv(name, &idx, envp);
	if (change_here != NULL)
	{
		ft_memmove(change_here, "=\"", 2);
		ft_memmove(change_here + 2, value, value_len);
		ft_memmove(change_here + 2 + value_len, "\"\0", 2);
	}
	return (-1);
}

int	ft_putenv(const char *str, char **envp)
{
	char	*change_here;
	int		idx;

	if (namelen(str, '=') == 0)
		return (-1);
	change_here = findenv(str, &idx, envp);
	if ((change_here == NULL) && (ft_strchr(str, '=') == NULL))
		envp[idx] = (char *)str;
	else if (ft_strchr(str, '=') != NULL)
		ft_setenv(str, ft_strchr(str, '=') + 1, envp);
	return (0);
}

void	export(char **argv, char **envp)
{
	int		argv_idx;

	argv_idx = 1;
	sortenv(envp);
	if (argv[argv_idx] == NULL)
		printenv(envp);
	else
	{
		while (argv[argv_idx] != NULL)
		{
			if (ft_putenv(argv[argv_idx], envp) == -1)
			{
				printf("minishell: export: `%s': ", argv[argv_idx]);
				printf("not a valid identifier\n");
			}
			argv_idx++;
		}
	}
}
