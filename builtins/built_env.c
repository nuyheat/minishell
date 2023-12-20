/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 19:06:45 by taehkim2         ###   ########.fr       */
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

void	env(char **argv, char **envp, int *status)
{
	int		argv_idx;

	argv_idx = 1;
	sortenv(envp);
	if (argv[argv_idx] == NULL)
		printenv(envp);
	*status = 0;
}
