/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:56:06 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/07 14:30:46 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <fcntl.h>

int	less(t_list *list, int *fd)
{
	int	less_idx;

	less_idx = 0;
	if (syntax_error(list))
		return (ERROR);
	// 파일 access 권한 handling
	*fd = open(list->info.token, O_RDONLY);
	if (*fd == -1)
		error_end("open failed");
}
