/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:19:47 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/08 17:37:49 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_list *list, t_pipe *pipes, char **envp)
{
	int	pid;
	int	status;

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
			waitpid(pid, &status, 0);
	}
}

void	parent_process(t_list *list, t_pipe *pipe, char **envp)
{
	char	**args;

	redirection_handling(list, pipe);
	args = args_make(list);
	builtin(args, envp);
	args_free(&args);
	if (dup2(pipe->std_fds[0], STDIN_FILENO) == -1 \
		|| dup2(pipe->std_fds[1], STDOUT_FILENO) == -1)
		error_end("dup2 failed");
}

void	execute(t_list *list, char **envp, int flg)
{
	t_pipe	pipes;
	char	*command;

	pipes.prev_fd[0] = -1;
	pipes.prev_fd[1] = -1;
	if (syntax_error(list) == ERROR)
		return ;
	while (list != NULL)
	{
		command = command_find(list);
		if (redirection_error(list) != ERROR && \
			command_error(command, envp) != ERROR)
		{
			if (flg != F_PIPE && is_it_builtin(command))
				parent_process(list, &pipes, envp);
			else
				child_process(list, &pipes, envp);
		}
		args_next(&list);
	}
}
