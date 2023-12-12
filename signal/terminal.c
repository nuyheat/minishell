/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:19:17 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/12 14:53:37 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_echo_off(struct termios* terminal)
{
	tcgetattr(STDIN_FILENO, terminal);
    terminal->c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, terminal);
}

void	ctrl_echo_on(struct termios* terminal)
{
	tcgetattr(STDIN_FILENO, terminal);
    terminal->c_lflag |= (ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, terminal);
}
