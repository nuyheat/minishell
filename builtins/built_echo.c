/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:59:35 by sihlee            #+#    #+#             */
/*   Updated: 2023/11/30 15:59:54 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo(char **argv)
{
	int	idx;
	int	newline;

	idx = 1;
	newline = 1;
	while (argv[idx] != NULL)
	{
		if (idx == 1 && (ft_strncmp("-n", argv[idx], 3) == 0))
			newline = 0;
		else if (argv[idx + 1] == NULL)
			printf("%s", argv[idx]);
		else
			printf("%s ", argv[idx]);
		idx++;
	}
	if (newline)
		printf("\n");
}
