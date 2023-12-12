/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:19:47 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/12 17:34:43 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_list *list, t_pipe *pipes, char **envp)
{
	int	pid;

	pipe(pipes->next_fd);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		child(list, pipes, envp);
	else if (pid > 0)
	{
		pipe_setting_for_parent(pipes);
		if (is_it_last_order(list))
			waitpid(pid, &(pipes->status), 0);
	}
}

void	parent_process(t_list *list, t_pipe *pipes, char **envp)
{
	char	**args;

	pipe_init(pipes);
	redirection_handling(list, pipes);
	args = args_make(list);
	builtin(args, envp);
	args_free(&args);
	if (dup2(pipes->std_fds[0], STDIN_FILENO) == -1 \
		|| dup2(pipes->std_fds[1], STDOUT_FILENO) == -1)
		error_end("dup2 failed");
}

void	execute(t_list *list, t_pipe *pipes, char **envp, int flg)
{
	char	*command;

	pipes->prev_fd[0] = -1;
	pipes->prev_fd[1] = -1;
	if (syntax_error(list, &(pipes->status)) == ERROR)
		return ;
	heredoc_make(list, pipes);
	while (list != NULL)
	{
		command = command_find(list);
		if (redirection_error(list, &(pipes->status)) != ERROR)
		{
			if (flg != F_PIPE && is_it_builtin(command))
				parent_process(list, pipes, envp);
			else
				child_process(list, pipes, envp);
		}
		pipes->heredoc_cnt++;
		args_next(&list);
	}
	heredoc_close(pipes);
}
