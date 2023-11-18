/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:21:27 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/21 15:03:43 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_strlen(char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	s_index;
	size_t	f_index;

	if (!*needle)
		return (haystack);
	if (len <= 0)
		return (NULL);
	s_index = 0;
	while (s_index < len && s_index < ft_strlen(haystack))
	{
		f_index = 0;
		while (haystack[s_index + f_index] == needle[f_index])
		{
			f_index++;
			if (s_index + f_index >= len)
				break ;
			else if (!needle[f_index])
				break ;
		}
		if (!needle[f_index])
			return (&haystack[s_index]);
		s_index++;
	}
	return ((char *)0);
}
