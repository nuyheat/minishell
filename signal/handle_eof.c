/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:16:11 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/14 21:44:28 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eof_in_interactive(void)
{
	if (g_signal == 15)
	{
		ft_putstr_fd("\033[1A", STDERR_FILENO);
		ft_putstr_fd("\033[13C", STDERR_FILENO);
		ft_putstr_fd("exit\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("\033[1A", STDERR_FILENO);
		ft_putstr_fd("\033[11C", STDERR_FILENO);
		ft_putstr_fd("exit\n", STDERR_FILENO);
	}
}

void	eof_in_heredoc(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[2C", STDERR_FILENO);
	exit(15);
}

void	eof_in_line_creat(void)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putstr_fd("\033[2C", STDERR_FILENO);
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd("unexpected end of file\n", STDERR_FILENO);
	exit(15);
}
