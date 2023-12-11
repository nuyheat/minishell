/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:08:50 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/11 13:01:53 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_init(t_pipe *pipes)
{
	pipes->std_fds[0] = dup(STDIN_FILENO);
	pipes->std_fds[1] = dup(STDOUT_FILENO);
	if (pipes->std_fds[0] == -1 || pipes->std_fds[1] == -1)
		error_end("dup failed");
	pipes->redir_less_occured = 0;
	pipes->redir_grate_occured = 0;
	pipes->redir_heredoc_occured = 0;
}
