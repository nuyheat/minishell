/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 10:44:14 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd(char **argv, int *status)
{
	int		idx;
	int		flg;
	char	*str;

	idx = 1;
	if (argv[idx] != NULL)
	{
		flg = chdir(argv[idx]);
		if (flg == -1)
		{
			str = ft_strjoin("minishell: cd: ", argv[idx]);
			if (str == NULL)
				perror ("ft_strjoin:");
			else
			{
				perror(str);
				*status = 1;
				free(str);
			}
		}
	}
}
