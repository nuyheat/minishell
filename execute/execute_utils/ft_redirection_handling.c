/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:23:43 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 12:15:53 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_less(t_list *list, t_pipe *pipes, char *file)
{
	int	fd;

	pipes->redir_less_occured = 1;
	dup2(pipes->std_fds[0], STDIN_FILENO);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_end("open failed");
	else if (dup2(fd, STDIN_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	case_dless(t_list *list, t_pipe *pipes, char *eof)
{
	char	*line;

	pipes->redir_less_occured = 1;
	dup2(pipes->std_fds[0], STDIN_FILENO);
	if (pipe(pipes->here_doc) == -1)
		error_end("pipe failed");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit(1);
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			close(pipes->here_doc[1]);
			free(line);
			break ;
		}
		write(pipes->here_doc[1], line, ft_strlen(line));
		write(pipes->here_doc[1], "\n", 1);
		free(line);
	}
	if (dup2(pipes->here_doc[0], STDIN_FILENO) == -1)
		error_end("dup2 failed");
	close(pipes->here_doc[0]);
	token_change(list);
}

void	case_grate(t_list *list, t_pipe *pipes, char *file)
{
	int	fd;

	pipes->redir_grate_occured = 1;
	dup2(pipes->std_fds[1], STDOUT_FILENO);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_end("open failed");
	else if (dup2(fd, STDOUT_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	case_dgrate(t_list *list, t_pipe *pipes, char *file)
{
	int	fd;

	pipes->redir_grate_occured = 1;
	dup2(pipes->std_fds[1], STDOUT_FILENO);
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error_end("open failed");
	else if (dup2(fd, STDOUT_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	redirection_handling(t_list *list, t_pipe *pipes)
{
	t_list	*head;

	head = list;
	while (head != NULL && head->info.flgs != F_PIPE)
	{
		if (head->info.flgs == F_DLESS)
			case_dless(head, pipes, head->next->info.token);
		head = head -> next;
	}
	while (list != NULL && list->info.flgs != F_PIPE)
	{
		if (list->info.flgs == F_LESS)
			case_less(list, pipes, list->next->info.token);
		else if (list->info.flgs == F_GRATE)
			case_grate(list, pipes, list->next->info.token);
		else if (list->info.flgs == F_DGRATE)
			case_dgrate(list, pipes, list->next->info.token);
		list = list->next;
	}
}
