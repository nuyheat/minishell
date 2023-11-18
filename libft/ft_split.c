/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:16:43 by sihlee            #+#    #+#             */
/*   Updated: 2023/09/20 16:23:36 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	return (NULL);
}

static int	word_count(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*charset == *str && *str)
			str++;
		if (!(*charset == *str) && *str)
		{
			count++;
			while (!(*charset == *str) && *str)
				str++;
		}
	}
	return (count);
}

static char	*return_word(char *str, char *charset, int *len)
{
	while (*charset == *str && *str)
		str++;
	while (!(*charset == *(str + *len)) && *(str + *len))
		(*len)++;
	return (str);
}

static char	**save_word(char **result, char *str, char *charset, int word)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (i < word)
	{
		j = 0;
		str = return_word(str, charset, &len);
		result[i] = malloc(sizeof(char) * (len + 1));
		if (!result[i])
			return (ft_free(result));
		result[i][len] = 0;
		while (len)
		{
			result[i][j++] = *str;
			str++;
			len--;
		}
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word;

	word = word_count((char *)s, &c);
	result = malloc(sizeof(char *) * (word + 1));
	if (!result)
		return (NULL);
	result[word] = NULL;
	return (save_word(result, (char *)s, &c, word));
}
