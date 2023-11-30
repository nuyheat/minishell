/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:26 by sihlee            #+#    #+#             */
/*   Updated: 2023/11/30 18:30:38 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(char **argv)
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
