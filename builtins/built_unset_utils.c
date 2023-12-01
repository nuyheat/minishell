/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 15:05:22 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	order(char *str1, char *str2)
{
	int	idx;

	idx = 0;
	while ((str1[idx] != '=' || str1[idx]) && (str2[idx] != '=' || str2[idx]))
	{
		if (str1[idx] != str2[idx])
			return (str1[idx] - str2[idx]);
		idx++;
	}
	if (str1[idx] != '=' && !str1[idx])
		return (str1[idx] - 0);
	else
		return (0 - str2[idx]);
}

void	sortenv(char **envp)
{
	int		idx;
	int		cnt;
	int		envp_idx;
	int		len;

	idx = 1;
	while (envp[idx] != NULL)
	{
		cnt = idx;
		while (1 <= cnt)
		{
			if (order(envp[cnt - 1], envp[cnt]) > 0)
				swap(envp + cnt - 1, envp + cnt);
			cnt--;
		}
		idx++;
	}
}
