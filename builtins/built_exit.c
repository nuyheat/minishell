/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/15 14:08:02 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

long long	ft_atol(const char *str)
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
		i++;
	}
	return (result * flag);
}

int	is_it_longlong(char *num)
{
	long long	value;
	int			num_len;

	num_len = ft_strlen(num);
	if (num_len != 1 && (num[0] == '-' || num[0] == '+'))
		num++;
	while (*num && (*num == '0'))
		num++;
	num_len = ft_strlen(num);
	value = ft_atol(num);
	while (num_len--)
	{
		if ((value % 10LL) != (num[num_len] - '0'))
			return (0);
		value /= 10;
	}
	return (1);
}

long long	check_exit_num(char *num, int *error_flag)
{
	if (num[0] == '\0')
	{
		*error_flag = 1;
		return (255);
	}
	if (ft_strncmp(num, "-9223372036854775808", 21) == 0)
		return (-9223372036854775807LL - 1LL);
	else if (!is_it_longlong(num))
		*error_flag = 1;
	return (ft_atol(num));
}

void	my_exit(char **argv, int *status)
{
	int		error_flag;
	char	exit_num;

	exit_num = 0;
	error_flag = 0;
	printf("exit\n");
	if (argv == NULL || argv[1] == NULL)
		exit(*status);
	else
	{
		exit_num = check_exit_num(argv[1], &error_flag);
		if (error_flag == 1)
		{
			write(2, "minishell: exit: ", 17);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else if (argv[2] == NULL)
			exit(exit_num);
		write(2, "minishell: exit: too many arguments\n", 36);
		*status = 1;
	}
}
