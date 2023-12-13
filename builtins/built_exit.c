/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/13 19:24:11 by taehkim2         ###   ########.fr       */
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
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (-9223372036854775807LL - 1LL);
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

long long	check_exit_num(char *num, int *error_flag)
{
	int		idx;

	if (num[0] == '\0')
	{
		*error_flag = 1;
		return (255);
	}
	if ((ft_strchr(num, '-') == NULL && \
		ft_strncmp(num, "9223372036854775808", 20) >= 0)
		|| (ft_strchr(num, '-') != NULL && \
		ft_strncmp(num, "-9223372036854775809", 21) >= 0))
		*error_flag = 1;
	idx = 0;
	if (num[0] == '-')
		idx++;
	while (num[idx])
	{
		if (ft_isdigit(num[idx]) == 0)
			*error_flag = 1;
		idx++;
	}
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
		*status = 257;
	}
}
