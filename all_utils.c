/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:10:27 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/16 11:09:33 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_end(char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
} // 에러 커스텀 메세지 출력 및 종료

char	*get_token(t_list *list)
{
	return (list->info.token);
} // 토큰 받아오는 함수(필요 없을시 삭제)

int	get_flags(t_list *list)
{
	return (list->info.flags);
} // 플래그 받아오는 함수(필요 없을시 삭제)
