/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:23:43 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/08 17:47:35 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_less(t_list *list, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_end("open failed");
	if (dup2(fd, STDIN_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	case_dless(t_list *list, char *eof, int *here_doc)
{
	char	*line;

	if (here_doc[0] != -1 && here_doc[1] != -1)
		close(here_doc[1]);
	if (pipe(here_doc) == -1)
		error_end("pipe failed");
	if (dup2(here_doc[0], STDIN_FILENO) == -1)
		error_end("dup2 failed");
	close(here_doc[0]);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			error_end("readline failed");
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(here_doc[1], line, ft_strlen(line));
		free(line);
	}
	token_change(list);
}

void	case_grate(t_list *list, char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_end("open failed");
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	case_dgrate(t_list *list, char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error_end("open failed");
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	redirection_handling(t_list *list, t_pipe *pipe)
{
	pipe->here_doc[0] = -1;
	pipe->here_doc[1] = -1;
	pipe->std_fds[0] = dup(STDIN_FILENO);
	pipe->std_fds[1] = dup(STDOUT_FILENO);
	if (pipe->std_fds[0] == -1 || pipe->std_fds[1] == -1)
		error_end("dup failed");
	while (list != NULL && list->info.flgs != F_PIPE)
	{
		if (list->info.flgs == F_LESS)
			case_less(list, list->next->info.token);
		else if (list->info.flgs == F_DLESS)
			case_dless(list, list->next->info.token, pipe->here_doc);
		else if (list->info.flgs == F_GRATE)
			case_grate(list, list->next->info.token);
		else if (list->info.flgs == F_DGRATE)
			case_dgrate(list, list->next->info.token);
		list = list->next;
	}
	if (pipe->here_doc[1] != -1)
		close(pipe->here_doc[1]);
}
