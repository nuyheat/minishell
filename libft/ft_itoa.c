/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:24:11 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/20 17:55:27 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	num_length(long long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_charcat(char *dest, char c)
{
	int	dest_length;

	dest_length = 0;
	while (dest[dest_length])
		dest_length++;
	dest[dest_length++] = c;
	dest[dest_length] = '\0';
	return (dest);
}

void	nbr_to_base(long long num, char *base, int cipher, char *str)
{
	if (num <= cipher - 1)
	{
		ft_charcat(str, base[num]);
		return ;
	}
	nbr_to_base(num / cipher, base, cipher, str);
	nbr_to_base(num % cipher, base, cipher, str);
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*str;
	int			size;

	num = n;
	if (num < 0)
	{
		num = -num;
		size = num_length(num) + 1;
		str = malloc(sizeof(char) * (size + 1));
	}
	else
	{
		size = num_length(num);
		str = malloc(sizeof(char) * (size + 1));
	}
	if (!str)
		return (NULL);
	str[size] = 0;
	str[0] = 0;
	if (n < 0)
		ft_charcat(str, '-');
	nbr_to_base(num, "0123456789", 10, str);
	return (str);
}
