/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:14:42 by sihlee            #+#    #+#             */
/*   Updated: 2023/03/21 14:24:40 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_num(long long num, int fd)
{
	char	digit;

	if (num <= 9)
	{
		digit = num + '0';
		write(fd, &digit, 1);
		return ;
	}
	print_num(num / 10, fd);
	print_num(num % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	print_num(num, fd);
}
