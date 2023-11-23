/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:53:01 by sihlee            #+#    #+#             */
/*   Updated: 2023/11/23 17:27:01 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "minishell.h"

static int	check_set(char const *set, char const c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*my_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*result;

	size = 0;
	while (!check_set(set, s1[size]))
	{
		size++;
		if (s1[size] == '\0')
			break ;
	}
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_bzero(result, (size + 1) * sizeof(char));
	ft_strlcpy(result, s1, (size + 1) * sizeof(char));
	return (result);
}
