/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:37:55 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/17 14:53:21 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_bzero(void *s, size_t n)
{
	int	i;

	i = 0;
	while (n--)
		((char *)s)[i++] = 0;
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = ft_strlen(src);
	i = 0;
	while (src[i] && (i + 1 < dstsize))
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (count);
}

char	*ft_strdup(const char *s1)
{
	void	*ptr;

	ptr = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (ptr)
	{
		ft_bzero(ptr, (ft_strlen(s1) + 1) * sizeof(char));
		ft_strlcpy(ptr, s1, (ft_strlen(s1) + 1) * sizeof(char));
		return (ptr);
	}
	return ((void *)0);
}
