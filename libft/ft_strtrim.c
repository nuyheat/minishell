/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:53:01 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/13 20:55:06 by taehkim2         ###   ########.fr       */
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

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	if (!ft_strlen(src))
		return (0);
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

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*result;

	while (check_set(set, *s1))
		s1++;
	size = ft_strlen(s1);
	if (size)
		while (check_set(set, s1[size - 1]))
			size--;
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_bzero(result, (size + 1) * sizeof(char));
	ft_strlcpy(result, s1, (size + 1) * sizeof(char));
	return (result);
}
