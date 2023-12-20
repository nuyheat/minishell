/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 19:06:56 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*findenv(const char *name, int *offset, char **envp)
{
	int			i;
	const char	**envp_ptr;

	if (name == NULL || envp == NULL)
		return (NULL);
	envp_ptr = (const char **)envp;
	i = 0;
	while (*envp_ptr != NULL)
	{
		if (comparename(name, *envp_ptr) > 0)
		{
			*offset = i;
			return ((char *)(*envp_ptr + namelen(name, '=')));
		}
		envp_ptr++;
		i++;
	}
	*offset = i;
	envp[i + 1] = NULL;
	return (NULL);
}

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
		envp[idx] = ft_calloc(name_len + 2 + value_len + 2, sizeof(char));
		ft_memmove(envp[idx], name, name_len);
	}
	else
		envp[idx] = ft_realloc(envp[idx], (name_len + 2 + value_len + 2));
	change_here = findenv(name, &idx, envp);
	if (change_here != NULL)
	{
		ft_memmove(change_here, "=", 1);
		ft_memmove(change_here + 1, value, value_len);
		change_here[1 + value_len] = 0;
	}
	return (-1);
}

int	ft_putenv(const char *str, char **envp)
{
	char	*change_here;
	int		idx;

	if (!name_ok(str))
		return (-1);
	change_here = findenv(str, &idx, envp);
	if ((change_here == NULL) && (ft_strchr(str, '=') == NULL))
	{
		envp[idx] = ft_strdup(str);
		envp[idx + 1] = NULL;
	}
	else if (ft_strchr(str, '=') != NULL)
		ft_setenv(str, ft_strchr(str, '=') + 1, envp);
	return (0);
}

void	export(char **argv, char **envp, int *status)
{
	int		argv_idx;

	argv_idx = 1;
	sortenv(envp);
	if (argv[argv_idx] == NULL)
		printexport(envp);
	else
	{
		while (argv[argv_idx] != NULL)
		{
			if (ft_putenv(argv[argv_idx], envp) == -1)
			{
				write(2, "minishell: export: `", 20);
				write(2, argv[argv_idx], ft_strlen(argv[argv_idx]));
				write(2, "': not a valid identifier\n", 26);
				*status = 1;
			}
			argv_idx++;
		}
	}
	*status = 0;
}
