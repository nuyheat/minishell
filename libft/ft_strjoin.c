/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:00:01 by sihlee            #+#    #+#             */
/*   Updated: 2023/09/06 17:25:56 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
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

static void	*ft_memmove(void *dst, const void *src, size_t len)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	void	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (ptr)
	{
		ft_bzero(ptr, (s1_len + s2_len + 1) * sizeof(char));
		ft_memmove(ptr, s1, s1_len);
		ft_memmove(ptr + s1_len, s2, s2_len + 1);
		return (ptr);
	}
	return (NULL);
}
