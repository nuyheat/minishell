/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:21:18 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 20:13:32 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_put_char(t_pipe *pipes, char *eof, int cnt)
{
	char	*line;
	int		pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		error_end("fork failed");
	else if (pid == 0)
	{
		heredoc_mode_sig();
		if (pipes->heredoc[cnt][0] != -1 && pipes->heredoc[cnt][1] != -1)
			close(pipes->heredoc[cnt][0]);
		if (pipe(pipes->heredoc[cnt]) == -1)
			error_end("pipe failed");
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
			{
				close(pipes->heredoc[cnt][1]);
				break ;
			}
			if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
			{
				close(pipes->heredoc[cnt][1]);
				free(line);
				break ;
			}
			write(pipes->heredoc[cnt][1], line, ft_strlen(line));
			write(pipes->heredoc[cnt][1], "\n", 1);
			free(line);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	return (0);
}

int	heredoc_init(t_list *list, t_pipe *pipes)
{
	int	cnt;
	int	status;

	status = -1;
	cnt = 0;
	while (cnt < pipes->heredoc_fl_cnt)
	{
		pipes->heredoc[cnt][0] = -1;
		pipes->heredoc[cnt][1] = -1;
		cnt++;
	}
	cnt = 0;
	while (list != NULL)
	{
		if (list->info.flgs == F_DLESS)
			status = heredoc_put_char(pipes, list->next->info.token, cnt);
		else if (list->info.flgs == F_PIPE)
			cnt++;
		if (status > -1)
		{
			heredoc_close(pipes);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

void	heredoc_close(t_pipe *pipes)
{
	int	cnt;

	cnt = 0;
	while (cnt < pipes->heredoc_fl_cnt)
	{
		if (pipes->heredoc[cnt][0] != -1 && pipes->heredoc[cnt][1] != -1)
			close(pipes->heredoc[cnt][0]);
		cnt++;
	}
}

int	heredoc_make(t_list *list, t_pipe *pipes)
{
	t_list	*head;
	int		cnt;

	pipes->heredoc_cnt = 0;
	pipes->heredoc_fl_cnt = 1;
	head = list;
	while (list != NULL)
	{
		if (list->info.flgs == F_PIPE)
			pipes->heredoc_fl_cnt++;
		list = list->next;
	}
	pipes->heredoc = \
	(int (*)[2])malloc(sizeof(int [2]) * pipes->heredoc_fl_cnt);
	if (pipes->heredoc == NULL)
		error_end("malloc failed");
	if (heredoc_init(head, pipes))
		return (1);
	return (0);
}
