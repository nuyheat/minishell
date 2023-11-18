/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:16:16 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/20 13:25:10 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	dest_length;
	unsigned int	src_length;
	unsigned int	i;
	unsigned int	j;

	src_length = ft_strlen(src);
	if (dstsize == 0)
		return (src_length + dstsize);
	dest_length = ft_strlen(dst);
	if (!(dstsize <= dest_length))
	{
		i = dest_length;
		j = 0;
		while ((i + 1 < dstsize) && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (dest_length + src_length);
	}
	return (src_length + dstsize);
}
