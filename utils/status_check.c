/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:13:19 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 13:53:44 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	status_check_child(int *status)
{
	int	status_tmp;

	status_tmp = *status;
	if ((status_tmp & 255) == 0)
		*status = status_tmp >> 8;
	else
	{
		if (status_tmp == 2)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			*status = 128 + 2;
		}
		else if (status_tmp == 3)
		{
			ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			*status = 128 + 3;
		}
		else if (status_tmp == 15)
			g_signal = 0;
	}
}

void	status_check_heredoc(int *status)
{
	int	status_tmp;

	status_tmp = *status;
	if ((status_tmp & 255) == 0)
	{
		status_tmp = status_tmp >> 8;
		if (status_tmp == 2)
			*status = 1;
		else if (status_tmp == 15)
		{
			g_signal = 15;
			*status = 0;
		}
	}
}

void	status_check_line_creat(int *status)
{
	int	status_tmp;

	status_tmp = *status;
	if ((status_tmp & 255) == 0)
	{
		status_tmp = status_tmp >> 8;
		if (status_tmp == 2)
			*status = 1;
		else if (status_tmp == 15)
		{
			g_signal = 0;
			*status = 128 + 130;
		}
	}
}
