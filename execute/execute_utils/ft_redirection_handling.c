/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:23:43 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/15 18:28:09 by taehkim2         ###   ########.fr       */
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

void	case_dless(t_list *list, t_pipe *pipes)
{
	if (pipes->redir_heredoc_occured == 0)
	{
		pipes->redir_heredoc_occured = 1;
		dup2(pipes->std_fds[0], STDIN_FILENO);
		if (dup2(pipes->heredoc[pipes->heredoc_cnt][0], STDIN_FILENO) == -1)
			error_end("dup2 failed");
	}
	token_change(list);
}

void	case_grate(t_list *list, t_pipe *pipes, char *file)
{
	int	fd;

	pipes->redir_grate_occured = 1;
	dup2(pipes->std_fds[1], STDOUT_FILENO);
	fd = open(file, O_WRONLY);
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
	fd = open(file, O_WRONLY | O_APPEND);
	if (fd == -1)
		error_end("open failed");
	else if (dup2(fd, STDOUT_FILENO) == -1)
		error_end("dup2 failed");
	close(fd);
	token_change(list);
}

void	redirection_handling(t_list *list, t_pipe *pipes)
{
	while (list != NULL && list->info.flgs != F_PIPE)
	{
		if (list->info.flgs == F_LESS)
			case_less(list, pipes, list->next->info.token);
		else if (list->info.flgs == F_DLESS)
			case_dless(list, pipes);
		else if (list->info.flgs == F_GRATE)
			case_grate(list, pipes, list->next->info.token);
		else if (list->info.flgs == F_DGRATE)
			case_dgrate(list, pipes, list->next->info.token);
		list = list->next;
	}
}
