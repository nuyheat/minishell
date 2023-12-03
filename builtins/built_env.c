/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/03 14:38:37 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	printenv(char **envp)
{
	char	**envp_ptr;
	char	*equal;

	envp_ptr = envp;
	while (*envp_ptr != NULL)
	{
		equal = ft_strchr(*envp_ptr, '=');
		if (equal != NULL)
			printf("%s\n", *envp_ptr);
		envp_ptr++;
	}
}

void	env(char **argv, char **envp)
{
	int		argv_idx;

	argv_idx = 1;
	sortenv(envp);
	if (argv[argv_idx] == NULL)
		printenv(envp);
}
