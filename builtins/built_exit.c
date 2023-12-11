/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/11 12:15:33 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_atol(const char *str)
{
	int			i;
	int			flag;
	long long	result;

	flag = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag = -flag;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		if (result > 9223372036854775807)
			return (-1);
		i++;
	}
	return (result * flag);
}

void	check_exit_num(char *num)
{
	if (ft_strncmp(num, "9223372036854775808", 20) >= 0
		|| ft_strncmp(num, "-9223372036854775810", 21) <= 0)
	{
		write(2, "minishell: exit: ", 17);
		write(2, num, ft_strlen(num));
		write(2, ": numeric argument required\n", 28);
		exit(-1);
	}
	if (num[0] == '-')
		num++;
	while (*num)
	{
		if (ft_isdigit(*num) == 0)
		{
			write(2, "minishell: exit: ", 17);
			write(2, num, ft_strlen(num));
			write(2, ": numeric argument required\n", 28);
			exit(-1);
		}
		num++;
	}
	printf("exit\n");
	exit(ft_atol(num));
}

void	my_exit(char **argv)
{
	int		argv_idx;

	argv_idx = 2;
	if (argv[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (argv[2] == NULL)
	{
		check_exit_num(argv[1]);
	}
	else
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit(1);
	}
}
