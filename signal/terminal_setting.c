/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:19:17 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/14 13:25:08 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// terminal 의 ctrl echo 설정을 끄는 함수
void	ctrl_echo_off(struct termios *terminal)
{
	tcgetattr(STDIN_FILENO, terminal); // 현재 terminal의 속성정보를 받아옴
	terminal->c_lflag &= ~(ECHOCTL); // 제어문자(/C, /D 등)의 출력을 제거
	tcsetattr(STDIN_FILENO, TCSANOW, terminal); // 터미널 설정에 즉시 반영(TCSANOW -> terminal control set attribute now)
}

// terminal 의 ctrl echo 설정을 켜는 함수
void	ctrl_echo_on(struct termios *terminal)
{
	tcgetattr(STDIN_FILENO, terminal);
	terminal->c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, terminal);
}
