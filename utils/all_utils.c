/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:10:27 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/05 19:24:28 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../builtins/builtins.h"

void	my_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	my_free2(char **strs)
{
	int	idx;

	idx = 0;
	while (strs[idx] != NULL)
	{
		my_free(strs[idx]);
		idx++;
	}
}

char	*get_token(t_list *list)
{
	return (list->info.token);
}
// 토큰 받아오는 함수(필요 없을시 삭제)

int	get_flags(t_list *list)
{
	return (list->info.flgs);
}
// 플래그 받아오는 함수(필요 없을시 삭제)

char	*ft_getenv(char *name, char **envp)
{
	char	*value;
	char	*result;
	int		envp_index;

	result = NULL;
	value = findenv(name, &envp_index, envp);
	if (value != NULL)
	{
		result = ft_strtrim(value, "=\"");
		free(value);
	}
	return (result);
}
