/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_make.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:39:38 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/13 18:23:50 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_dollar_expansion(t_pipe *pipes, char **line, \
									char **envp, int cnt)
{
	int		idx;
	char	*new_line;

	idx = 0;
	while ((*line)[idx] != '\0')
	{
		if ((*line)[idx] == '$')
		{
			new_line = trans_param_expansion(*line, envp, pipes->status);
			write(pipes->heredoc[cnt][1], new_line, ft_strlen(new_line));
			write(pipes->heredoc[cnt][1], "\n", 1);
			free(new_line);
			free(*line);
			return ;
		}
		idx++;
	}
	write(pipes->heredoc[cnt][1], *line, idx);
	write(pipes->heredoc[cnt][1], "\n", 1);
	free(*line);
}

void	heredoc_child(t_pipe *pipes, char *eof, int cnt, char **envp)
{
	char	*line;

	heredoc_mode_sig();
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit(1);
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		heredoc_dollar_expansion(pipes, &line, envp, cnt);
	}
	heredoc_close(pipes);
	exit(0);
}

int	heredoc_put_char(t_pipe *pipes, char *eof, int cnt, char **envp)
{
	int	pid;
	int	status_tmp;

	signal(SIGINT, SIG_IGN);
	if (pipes->heredoc[cnt][0] != -1 && pipes->heredoc[cnt][1] != -1)
		close(pipes->heredoc[cnt][0]);
	if (pipe(pipes->heredoc[cnt]) == -1)
		error_end("pipe failed");
	pid = fork();
	if (pid < 0)
		error_end("fork failed");
	else if (pid == 0)
		heredoc_child(pipes, eof, cnt, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status_tmp, 0);
		if (status_check(&(pipes->status), status_tmp) == END)
			return (END);
	}
	close(pipes->heredoc[cnt][1]);
	return (NEXT);
}

int	heredoc_init(t_list *list, t_pipe *pipes, int cnt, char **envp)
{
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
		{
			if (heredoc_put_char(pipes, list->next->info.token, cnt, envp))
			{
				heredoc_close(pipes);
				return (END);
			}
		}
		else if (list->info.flgs == F_PIPE)
			cnt++;
		list = list->next;
	}
	return (NEXT);
}

int	heredoc_creat(t_list *list, t_pipe *pipes, char **envp)
{
	t_list	*head;

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
	if (heredoc_init(head, pipes, 0, envp))
		return (END);
	return (NEXT);
}
