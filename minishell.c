/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:12:56 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 17:38:16 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*list;
	t_pipe	pipes;

	copy_envp(envp);
	pipes.status = 0;
	while (1)
	{
		line = line_creat();
		if (line[0] != '\0')
		{
			add_history(line);
			list = parse(line, envp, pipes.status);
			if (list != NULL)
			{
				execute(list, &pipes, envp, pipe_find(list));
				list_free(&list);
			}
		}
		free(line);
	}
}
