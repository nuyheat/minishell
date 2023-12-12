/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:21:18 by taehkim2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/12 15:53:02 by sihlee           ###   ########.fr       */
=======
/*   Updated: 2023/12/12 16:56:09 by taehkim2         ###   ########.fr       */
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_put_char(t_pipe *pipes, char *eof, int cnt)
{
	char	*line;

	if (pipes->heredoc[cnt][0] != -1 && pipes->heredoc[cnt][1] != -1)
		close(pipes->heredoc[cnt][0]);
	if (pipe(pipes->heredoc[cnt]) == -1)
		error_end("pipe failed");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
<<<<<<< HEAD
			break ;
=======
		{
			close(pipes->heredoc[cnt][1]);
			break ;
		}
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
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

void	heredoc_init(t_list *list, t_pipe *pipes)
{
	int	cnt;

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
			heredoc_put_char(pipes, list->next->info.token, cnt);
		if (list->info.flgs == F_PIPE)
			cnt++;
		list = list->next;
	}
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

void	heredoc_make(t_list *list, t_pipe *pipes)
{
	t_list	*head;
	int		cnt;

	heredoc_mode_sig();
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
	heredoc_init(head, pipes);
	interactive_mode_sig();
}
