/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/12 12:04:45 by sihlee           ###   ########.fr       */
=======
/*   Updated: 2023/12/12 17:01:40 by taehkim2         ###   ########.fr       */
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
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

int	check_exit_num(char *num)
{
	int		idx;

	if (ft_strncmp(num, "9223372036854775808", 20) == 0
		|| ft_strncmp(num, "-9223372036854775810", 21) == 0)
	{
		write(2, "minishell: exit: ", 17);
		write(2, num, ft_strlen(num));
		write(2, ": numeric argument required\n", 28);
		return (-1);
	}
	idx = 0;
	if (num[0] == '-')
		idx++;
	while (num[idx])
	{
		if (ft_isdigit(num[idx]) == 0)
		{
			write(2, "minishell: exit: ", 17);
			write(2, num, ft_strlen(num));
			write(2, ": numeric argument required\n", 28);
			return (-1);
		}
		idx++;
	}
	return (ft_atol(num));
}

void	my_exit(char **argv)
{
	int		argv_idx;
	int		exit_num;

	argv_idx = 2;
	exit_num = 0;
<<<<<<< HEAD
	printf("exit\n");
	if (argv == NULL || argv[1] == NULL)
=======
	if (argv == NULL || argv[1] == NULL)
	{
		printf("\b\bexit\n");
>>>>>>> 3171dfb6db91a062e0e4a4d70f3b4b2ec3ffa799
		exit(exit_num); // 이거 이전 $? 리턴값으로 exit_num을 넘겨줘야함
	}
	else if (argv[2] == NULL)
	{
		printf("exit\n");
		exit_num = check_exit_num(argv[1]);
		exit(exit_num);
	}
	else
	{
		printf("exit\n");
		write(2, "minishell: exit: too many arguments\n", 36);
	}
}
