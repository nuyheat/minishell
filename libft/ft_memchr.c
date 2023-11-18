/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:18:55 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/20 12:32:06 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	if ((unsigned char)c >= 0)
	{
		while (n--)
		{
			if (*(unsigned char *)s == (unsigned char)c)
				return ((void *)s);
			else
				s++;
		}
		return ((void *)0);
	}
	return ((void *)s);
}
