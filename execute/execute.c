/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:19:47 by taehkim2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/12 17:14:56 by sihlee           ###   ########.fr       */
=======
/*   Updated: 2023/12/12 17:03:16 by taehkim2         ###   ########.fr       */
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	int child_signal_occured = 0;

// void	handle_sigint(int sig)
// {
// 	if (child_signal_occured == 0)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0); // 현재 버퍼를 비워줌
// 		rl_redisplay(); // readline 메시지를 다시 출력
// 	}
// 	else
// 	{
// 		printf("\n");
// 		child_signal_occured = 0;
// 	}
// }

void	child_process(t_list *list, t_pipe *pipes, char **envp, struct termios* terminal)
{
	int	pid;

	signal(SIGINT, handle_sigint2);
	pipe(pipes->next_fd);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		child_mode_sig();
		ctrl_echo_on(terminal);
		child(list, pipes, envp);
	}
	else if (pid > 0)
	{
		pipe_setting_for_parent(pipes);
		if (is_it_last_order(list))
<<<<<<< HEAD
			waitpid(pid, &status, 0);
			// printf("status is %d\n", status);
=======
			waitpid(pid, &(pipes->status), 0);
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
	}
	ctrl_echo_off(terminal);
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

<<<<<<< HEAD
void	execute(t_list *list, char **envp, int flg, struct termios* terminal)
=======
void	execute(t_list *list, t_pipe *pipes, char **envp, int flg)
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
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
<<<<<<< HEAD
				child_process(list, &pipes, envp, terminal);
=======
				child_process(list, pipes, envp);
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
		}
		pipes->heredoc_cnt++;
		args_next(&list);
	}
	heredoc_close(pipes);
}
