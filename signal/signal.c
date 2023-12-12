/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:16:11 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/12 17:14:52 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint1(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0); // 현재 버퍼를 비워줌
	rl_redisplay(); // readline 메시지를 다시 출력
}

void	handle_sigint2(int sig)
{
	printf("\n");
}

void	interactive_mode_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, handle_sigint1);
}
void	child_mode_sig(void)
{
	signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}

void	heredoc_mode_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_DFL);
}