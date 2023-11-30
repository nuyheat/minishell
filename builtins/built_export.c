/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:24:56 by sihlee            #+#    #+#             */
/*   Updated: 2023/11/30 18:11:12 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	namelen(const char *str, char find)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && (str[i] != find))
		i++;
	return (i);
}

int	comparename(const char *have_to_find, const char *now_im_at)
{
	int	len1;
	int	len2;

	len1 = namelen(have_to_find, '=');
	len2 = namelen(now_im_at, '=');
	if (len1 == len2)
	{
		if (ft_strncmp(have_to_find, now_im_at, len1) == 0)
			return (len1);
	}
	return (0);
}

//envp 배열을 순회하면서 입력된 환경 변수 이름(name)과 일치하는 환경 변수를 찾습니다. 
//이름이 발견되면 해당 환경 변수의 값의 시작 지점을 반환하고, 
//offset에는 찾은 환경 변수의 배열 인덱스가 설정됩니다. 만약 일치하는 환경 변수가 없으면 NULL을 반환합니다.
// https://opensource.apple.com/source/Libc/Libc-583/stdlib/getenv-fbsd.c
char	*findenv(const char *name, int *offset, char **envp)
{
	int			i;
	const char	**envp_ptr;

	if (name == NULL || envp == NULL)
		return (NULL);
	envp_ptr = (const char **)envp;
	i = 0;
	while (*envp_ptr != NULL)
	{
		if (comparename(name, *envp_ptr) > 0)
		{
			*offset = i;
			return ((char *)(*envp_ptr + namelen(name, '=')));
		}
		envp_ptr++;
		i++;
	}
	*offset = i;
	envp[i + 1] = NULL;
	return (NULL);
}

//setenv 함수는 주어진 환경 변수(name)의 값을 설정하거나 변경하는 함수입니다. 
//함수는 성공하면 0을 반환하고, 실패하면 -1을 반환합니다.
// https://opensource.apple.com/source/Libc/Libc-167/stdlib.subproj/setenv.c.auto.html
int	ft_setenv(const char *name, const char *value, char **envp)
{
	char	*change_here;
	int		idx;
	int		name_len;
	int		value_len;

	name_len = namelen(name, '=');
	value_len = ft_strlen(value);
	change_here = findenv(name, &idx, envp);
	if (change_here == NULL)
	{
		envp[idx] = malloc(name_len + 2 + value_len + 2);
		ft_memmove(envp[idx], name, name_len);
	}
	else
		envp[idx] = ft_realloc(envp[idx], (name_len + 2 + value_len + 2));
	change_here = findenv(name, &idx, envp);
	if (change_here != NULL)
	{
		// ft_memmove(change_here, "=\"", 2);
		// ft_memmove(change_here + 2, value, value_len);
		// ft_memmove(change_here + 2 + value_len, "\"\0", 2);
		ft_memmove(change_here, "=", 1);
		ft_memmove(change_here + 1, value, value_len);
		ft_memmove(change_here + 1 + value_len, "\0", 2);
	}
	return (-1);
}

int	ft_putenv(const char *str, char **envp)
{
	char	*change_here;
	int		idx;

	if (namelen(str, '=') == 0) //이름을 달지 않으면 export를 수행할 수 없습니다
		return (-1);
	change_here = findenv(str, &idx, envp);
	if ((change_here == NULL) && (ft_strchr(str, '=') == NULL))
		envp[idx] = (char *)str;
	else if (ft_strchr(str, '=') != NULL)
		ft_setenv(str, ft_strchr(str, '=') + 1, envp);
	return (0);
}

void	printenv(char **envp)
{
	char	**envp_ptr;

	envp_ptr = envp;
	while (*envp_ptr != NULL)
	{
		printf("%s\n", *envp_ptr);
		envp_ptr++;
	}
}

char	*my_getenv(char *name, char **envp)
{
	char	*value;
	int		envp_index;

	value = findenv(name, &envp_index, envp);
	if (*value == '=')
		return (value + 1);
	return (value);
}

int	export(char **argv, char **envp)
{
	int		argv_idx;

	// envp = copy_envp(envp);
	argv_idx = 1;
	if (argv[argv_idx] == NULL)
		printenv(envp);
	else
	{
		while (argv[argv_idx] != NULL)
		{
			if (ft_putenv(argv[argv_idx], envp) == -1)
			{
				printf("minishell: export: `%s': ", argv[argv_idx]);
				printf("not a valid identifier\n");
			}
			argv_idx++;
		}
		// printf("%s\n", getenv("a"));
	}
}
