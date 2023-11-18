/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:11:43 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/23 14:49:40 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (ft_strlen(s) < start + len)
	{
		if (ft_strlen(s) < start)
			len = 0;
		else if (ft_strlen(s) < len)
			len = ft_strlen(s) - start;
		else
			len = ft_strlen(s + start);
	}
	if (!len)
		len = 0;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr)
	{
		ptr[len] = 0;
		if (ft_strlen(s) > start)
			ft_strlcpy(ptr, s + start, (len + 1) * sizeof(char));
		return (ptr);
	}
	return (NULL);
}
