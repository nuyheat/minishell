/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:10:27 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/07 15:10:38 by taehkim2         ###   ########.fr       */
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

void	error_end(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}

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
		// free(value); 이거 왜 free하면 에러나는지 모르겠음
	}
	return (result);
}
