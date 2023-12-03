/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:56:06 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/03 19:15:45 by sihlee           ###   ########.fr       */
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
