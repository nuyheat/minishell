/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:50:45 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/30 18:55:26 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
