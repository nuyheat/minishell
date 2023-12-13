/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_dollar_convert.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:50:37 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/13 13:44:26 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_convert(char **token, char **envp, int status)
{
	char	*buf;
	int		buf_len;
	int		buf_idx;
	int		token_idx;

	buf_len = 0;
	buf_idx = 0;
	token_idx = 0;
	if ((*token)[1] == '?')
		buf = ft_itoa(status / 256);
	else
		buf = ft_getenv((*token) + 1, envp);
	if (buf != NULL)
		buf_len = ft_strlen(buf);
	free(*token);
	*token = malloc(buf_len + 1);
	if ((*token) == NULL)
		error_end("malloc failed");
	while (buf != NULL && buf[buf_idx] != '\0')
		(*token)[token_idx++] = buf[buf_idx++];
	(*token)[token_idx] = '\0';
	free(buf);
}

void	dquoted_handling(char ***splited_token, int *idx, \
						char **envp, int status)
{
	(*idx)++;
	while ((*splited_token)[*idx][0] != '\"')
	{
		if ((*splited_token)[*idx][0] == '$' && \
			(*splited_token)[*idx][1] != '\0')
			dollar_convert(&(*splited_token)[*idx], envp, status);
		(*idx)++;
	}
}

int	is_quoted_2d(char **str, int idx, char quote)
{
	if (str[idx][0] == quote && str[idx][1] == '\0')
	{
		idx++;
		while (str[idx] != NULL)
		{
			if (str[idx][0] == quote && str[idx][1] == '\0')
				return (QUOTED);
			idx++;
		}
	}
	return (NOT_QUOTED);
}

void	expansion_dollar_convert(char ***splited_token, char **envp, int status)
{
	int	idx;

	idx = 0;
	while ((*splited_token)[idx] != NULL)
	{
		if (is_quoted_2d(*splited_token, idx, '\"'))
			dquoted_handling(splited_token, &idx, envp, status);
		if ((*splited_token)[idx][0] == '$')
		{
			if ((*splited_token)[idx][1] == '\0')
			{
				if ((*splited_token)[idx + 1] != NULL && \
					(*splited_token)[idx + 1][0] != '/')
					(*splited_token)[idx][0] = '\0';
			}
			else if ((*splited_token)[idx][1] != '.')
				dollar_convert(&(*splited_token)[idx], envp, status);
		}
		idx++;
	}
}
