/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_expansion_dollar_convert.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:50:37 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/26 15:58:23 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_convert(char **token)
{
	char	*buf;
	int		buf_len;
	int		buf_idx;
	int		token_idx;

	buf_len = 0;
	buf_idx = 0;
	token_idx = 0;
	buf = getenv((*token) + 1);
	if (buf != NULL)
		buf_len = ft_strlen(buf);
	free(*token);
	*token = malloc(buf_len + 1);
	if ((*token) == NULL)
		error_end("malloc failed");
	while (buf != NULL && buf[buf_idx] != '\0')
		(*token)[token_idx++] = buf[buf_idx++];
	(*token)[token_idx] = '\0';
}

void	expansion_dollar_convert(char ***splited_token)
{
	int	idx;

	idx = 0;
	while ((*splited_token)[idx] != NULL)
	{
		if ((*splited_token)[idx][0] == '$')
		{
			if ((*splited_token)[idx][1] != '\0')
				dollar_convert(&(*splited_token)[idx]);
			else if ((*splited_token)[idx + 1] != NULL)
				(*splited_token)[idx][0] = '\0';
		}	
		idx++;
	}
}
