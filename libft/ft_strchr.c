/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:26:33 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/16 18:48:58 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{	
	char	*s_copy;

	s_copy = (char *)s;
	while (*s_copy)
		s_copy++;
	if ((char)c == 0)
		return ((char *)s_copy);
	else if ((char)c)
	{
		while (*s)
		{
			if (*s == (char)c)
				return ((char *)s);
			else
				s++;
		}
		return ((char *)0);
	}
	return ((char *)s);
}
