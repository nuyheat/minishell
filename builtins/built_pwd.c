/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:17:26 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/07 15:05:30 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(char **argv)
{
	char	*str;
	char	current_path[BUFSIZ];

	(void)argv;
	str = getcwd(current_path, BUFSIZ);
	if (str == NULL)
	{
		perror("minishell: pwd: ");
	}
	else
		printf("%s\n", str);
}
