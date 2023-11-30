/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:15:27 by sihlee            #+#    #+#             */
/*   Updated: 2023/11/29 18:00:14 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	*ft_realloc(void *memblock, size_t size)
{
	void	*new_memblock;

	if (size == 0)
	{
		free(memblock);
		return (NULL);
	}
	if (memblock == NULL)
		return (malloc(size));
	new_memblock = malloc(size);
	if (new_memblock != NULL)
	{
		ft_memcpy(new_memblock, memblock, size);
		free(memblock);
		return (new_memblock);
	}
	return (memblock);
}
