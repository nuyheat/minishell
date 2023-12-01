/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:26 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 20:14:05 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(char **argv)
{
	char	*str;

	(void)argv;
	str = getcwd(NULL, BUFSIZ);
	if (str == NULL)
	{
		perror("minishell: pwd: ");
	}
	else
		printf("%s\n", str);
	free(str);
}
