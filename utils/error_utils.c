/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:20:44 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/05 19:24:04 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	error_end(char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
}
// 에러 커스텀 메세지 출력 및 종료

int	syntax_error(t_list *node)
{
	int	flag;

	flag = node->info.flgs;
	if (flag & (F_LESS | F_DLESS | F_DGRATE | F_GRATE) != 0)
	{
		printf("minishell: syntax error near unexpected token");
		printf("`%s'\n", node->info.token);
		return (1);
	}
	return (0);
}

int	redirection_error(t_list *node)
{
	int	flag;

	flag = node->info.flgs;
	while (node != NULL && node->info.flgs != F_PIPE)
	{
		if (((flag & F_LESS) && access(node->info.token, F_OK)))
		{
			printf("minishell: %s: No such file or directory", node->info.token);
			return (1);
		}
		else if (((flag & F_GRATE) && access(node->info.token, F_OK))
			|| ((flag & F_DGRATE) && access(node->info.token, F_OK)))
				continue;
		else if (((flag & F_LESS) && access(node->info.token, R_OK))
			|| ((flag & F_GRATE) && access(node->info.token, W_OK))
			|| ((flag & F_DGRATE) && access(node->info.token, W_OK)))
		{
			printf("minishell: %s: Permission denied", node->info.token);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

int	is_it_builtin(char *command)
{
	if ((ft_strncmp(command, "echo", 3) == 0)
		|| (ft_strncmp(command, "cd", 5) == 0)
		|| (ft_strncmp(command, "pwd", 4) == 0)
		|| (ft_strncmp(command, "export", 7) == 0)
		|| (ft_strncmp(command, "unset", 6) == 0)
		|| (ft_strncmp(command, "env", 4) == 0)
		|| (ft_strncmp(command, "exit", 5) == 0))
		return (1);
	return (0);
}

int	command_not_found(t_list *node, char **envp)
{
	int		flag;
	int		table_idx;
	char	*path;
	char	**path_table;

	flag = node->info.flgs;
	table_idx = 0;	
	if ((flag & F_STRING) && !is_it_builtin(node->info.token))
	{
		path = ft_getenv("PATH", envp);
		path_table = ft_split(path, ':');
		while (path_table[table_idx] != NULL)
		{
			chdir(path_table[table_idx]);
			if (access(node->info.token, F_OK) == 0)
				return (0);
			table_idx++;
		}
		my_free2(path_table);
		return (1);
	}
	return (0);
}
