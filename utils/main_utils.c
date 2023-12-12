/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:25:40 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 20:41:16 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	copy_envp(char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
}

int	line_check(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len == 1 && line[0] == '|')
		return (END);
	else if (line[len - 1] == '|')
	{
		len -= 2;
		while (len >= 0 && line[len] == ' ')
			len--;
		if (len == -1)
			return (END);
		else if (line[len] == '|' || line[len] == '<' || line[len] == '>')
			return (END);
		return (NEXT);
	}
	return (END);
}

void	child_wait(void)
{
	while (1)
	{
		if (wait(0) == -1)
			break ;
	}
}

char	*line_creat(void)
{
	char	*line;
	char	*tmp;
	int		pid;
	int		pipes[2];
	int		status;

	child_wait();
	line = readline("minishell$ ");
	if (line == NULL)
		my_exit(NULL);
	else if (line[0] == '\0')
		return (line);
	if (pipe(pipes) == -1)
		error_end("pipe failed");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		error_end("fork failed");
	else if (pid == 0)
	{
		heredoc_mode_sig();
		while (1)
		{
			if (line_check(line))
				break ;
			tmp = readline("> ");
			if (tmp == NULL)
				error_end("readline failed");
			write(pipes[1], tmp, ft_strlen(tmp));
			free(tmp);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (status > -1)
			return (NULL);
	}
	return (line);
}

int	pipe_find(t_list *list)
{
	while (list != NULL)
	{
		if (list->info.flgs == F_PIPE)
			return (F_PIPE);
		list = list->next;
	}
	return (END);
}
