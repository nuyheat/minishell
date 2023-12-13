/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:19:17 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/13 12:55:05 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_echo_off(struct termios *terminal)
{
	tcgetattr(STDIN_FILENO, terminal);
	terminal->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, terminal);
}

void	ctrl_echo_on(struct termios *terminal)
{
	tcgetattr(STDIN_FILENO, terminal);
	terminal->c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, terminal);
}
