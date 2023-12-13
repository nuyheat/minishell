/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/13 19:24:27 by taehkim2         ###   ########.fr       */
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
				*status = 257;
				free(str);
			}
		}
		else
			*status = 0;
	}
}
