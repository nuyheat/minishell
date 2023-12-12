/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:54:15 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 16:55:43 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_child(t_pipe *pipes)
{
	close(pipes->next_fd[0]);
	if (!pipes->redir_grate_occured)
		dup2(pipes->next_fd[1], STDOUT_FILENO);
	close(pipes->next_fd[1]);
}

void	mid_child(t_pipe *pipes)
{
	close(pipes->prev_fd[1]);
	if (!pipes->redir_less_occured && !pipes->redir_heredoc_occured)
		dup2(pipes->prev_fd[0], STDIN_FILENO);
	close(pipes->prev_fd[0]);
	close(pipes->next_fd[0]);
	if (!pipes->redir_grate_occured)
		dup2(pipes->next_fd[1], STDOUT_FILENO);
	close(pipes->next_fd[1]);
}

void	last_child(t_pipe *pipes)
{
	if (pipes->prev_fd[0] != -1 && pipes->prev_fd[1] != -1)
	{
		close(pipes->prev_fd[1]);
		if (!pipes->redir_less_occured && !pipes->redir_heredoc_occured)
			dup2(pipes->prev_fd[0], STDIN_FILENO);
		close(pipes->prev_fd[0]);
	}
	close(pipes->next_fd[0]);
	close(pipes->next_fd[1]);
}

void	pipe_setting_for_child(t_pipe *pipes, int last)
{
	if (last)
		last_child(pipes);
	if (pipes->prev_fd[0] == -1 && pipes->prev_fd[1] == -1)
		first_child(pipes);
	else
		mid_child(pipes);
}

int	child(t_list *list, t_pipe *pipes, char **envp)
{
	char	**args;
	int		last_flag;

	pipe_init(pipes);
	last_flag = is_it_last_order(list);
	redirection_handling(list, pipes);
	heredoc_close(pipes);
	pipe_setting_for_child(pipes, last_flag);
	args = args_make(list);
	if (args != NULL)
	{
		if (command_error(args[0], envp) == ERROR)
			exit(127);
		if (builtin(args, envp) == 0)
			simple_command(args, envp);
	}
	args_free(&args);
	exit(0);
}
