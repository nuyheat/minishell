/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:21:18 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/13 12:50:36 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	cnt = 0;
	free(pipes->heredoc);
}
