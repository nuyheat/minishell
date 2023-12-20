/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 19:07:23 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cleanenv(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx + 1] != NULL)
	{
		if (*envp[idx] == 0)
			swap(envp + idx, envp + idx + 1);
		idx++;
	}
	envp[idx] = NULL;
}

void	unset(char **argv, char **envp, int *status)
{
	int		idx;
	int		envp_idx;
	char	*value;

	idx = 1;
	while (argv[idx] != NULL)
	{
		value = findenv(argv[idx], &envp_idx, envp);
		if (value != NULL)
		{
			ft_memset(envp[envp_idx], 0, ft_strlen(envp[envp_idx]));
			cleanenv(envp);
		}
		idx++;
	}
	sortenv(envp);
	*status = 0;
}
