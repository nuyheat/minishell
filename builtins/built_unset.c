/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 15:13:11 by sihlee           ###   ########.fr       */
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

int	unset(char **argv, char **envp)
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
}
