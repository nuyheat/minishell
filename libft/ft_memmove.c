/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:43:50 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/16 18:48:48 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst || src)
	{
		if ((char *)dst < (char *)src)
		{
			while (i < len)
			{
				((char *)dst)[i] = ((char *)src)[i];
				++i;
			}
		}
		else
		{
			while (len)
			{
				((char *)dst)[len - 1] = ((char *)src)[len - 1];
				len--;
			}
		}
	}
	return (dst);
}
