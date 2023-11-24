/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:24:31 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/24 15:39:50 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokenize(t_list **list, char *line)
{
	int		idx;
	char	*buf;

	idx = 0;
	buf = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (buf == NULL)
		error_end("calloc failed");
	while (line[idx] != '\0')
	{
		if (token_rules(list, &buf, line[idx]) == END)
			break ;
		idx++;
	}
	token_delimited(list, &buf);
	free(buf);
}

// void	parse_translate(t_list *now_list, t_list **new_list, char **envp)
// {
// 	char	*buf;

// 	while (now_list != NULL)
// 	{
// 		buf = translate_token(now_list, envp);
// 		// if ((prev_list->info.flgs & F_QUOTED) &&
// 		// 	(prev_list->info.flgs & F_DOLLAR))
// 		// {
// 		// 	token_add(new_list, prev_list->info.token, prev_list->info.flgs);
// 		// else if (prev_list->info.flgs & F_QUOTED)
// 		// {

// 		// }
// 		// else if (prev_list->info.flgs & F_DOLLAR)
// 		// {
// 		// 	// 버퍼 만들기 (길이 재서 그 크기만큼 calloc  하여 돌려줌)
// 		// 	// 해당 버퍼에 한 char씩 넣기 ($??? 발견시 -> 환경변수명 구하기. 이후 getenv(환경변수명) 사용)
// 		// 	// 넣는 과정 중 " 나 ' 만나면 넣지 않고 ++.
// 		// 	buf = translate_dollar();
// 		// 	parse_tokenize(new_list, buf);
// 		// 	token_add(new_list, prev_list->info.token, prev_list->info.flgs);
// 		// }
// 		token_add(new_list, buf, now_list->info.flgs);
// 		now_list = now_list->next;
// 	}
// }

// a="ls -al"
// b="echo H"
// $b"fknsfkesbf$a"sklfhslefih

void	parse_expend(t_list **token_list, char **envp)
{
	t_list	*list_ptr;

	list_ptr = *token_list;
	while ((list_ptr != NULL))
	{
		if ((list_ptr)->info.flgs & F_DOLLAR)
		{
			while (1)
			{
				char *variable = ft_strchr((list_ptr)->info.token, '$');
				if (variable == NULL) 								// $가 여러개 있을 경우를 대비해 while문으로 돌려줌
					break ;
				char *name = my_strtrim(variable + 1, "#$ \t\n\"\'");	// $ 다음부터 공백, 탭, 개행문자, "가 나오기 전까지의 문자열을 name에 저장
				char *value = getenv(name);							// name에 해당하는 환경변수의 value를 value에 저장
				if (value == NULL)									// 환경변수가 없을 경우
					value = "\0";										// value에 빈 문자열을 넣어줌
				if (*name && ft_strncmp(name, "a", ft_strlen(name)) == 0) value = "echo HH"; //for test
				// 버퍼 만들기 (길이 재서 그 크기만큼 calloc  하여 돌려줌)
				int buflen = ft_strlen((list_ptr)->info.token) - (ft_strlen(name) + 1) + ft_strlen(value);
				char *buf = ft_calloc(buflen + 1, sizeof(char));
				if (buf == NULL)
					error_end("calloc failed");
				// 해당 버퍼에 한 char씩 넣기 ($??? 발견시 -> 환경변수명 구하기. 이후 getenv(환경변수명) 사용)
				ft_strlcpy(buf, (list_ptr)->info.token, ft_strlen((list_ptr)->info.token) - ft_strlen(variable) + 1);
				ft_strlcpy(buf + ft_strlen(buf), value, ft_strlen(value) + 1);
				ft_strlcpy(buf + ft_strlen(buf), variable + 1 + ft_strlen(name), ft_strlen(variable + 1 + ft_strlen(name)) + 1); //ft_strlen(variable + ft_strlen(name) + 1));
				free((list_ptr)->info.token);
				(list_ptr)->info.token = NULL;
				free(name);
				list_ptr->info.token = buf;
			}
		}
		list_ptr = (list_ptr)->next;
	}	
}

void	parse_translate(t_list **old, t_list **new)
{
	t_list	*old_ptr;

	old_ptr = *old;
	while (old_ptr != NULL)
	{
		parse_tokenize(new, old_ptr->info.token);
		old_ptr = old_ptr->next;
	}
}
void	parse_delitmit(t_list **trans_list)
{
	t_list	*trans_list_ptr;
	char	*token;
	char	*buf;
	int		token_idx;
	int		buf_idx;

	trans_list_ptr = *trans_list;
	while (trans_list_ptr != NULL)
	{
		token = trans_list_ptr->info.token;
		if ((token != NULL) && (trans_list_ptr->info.flgs & F_QUOTED))
		{
			buf = ft_calloc(ft_strlen(token) + 1, sizeof(char));
			token_idx = 0;
			buf_idx = 0;
			while (token[token_idx] != '\0')
			{
				if ((token[token_idx] != '\"') && (token[token_idx] != '\''))
				{
					buf[buf_idx] = token[token_idx];
					buf_idx++;
				}
				token_idx++;
			}
			free(trans_list_ptr->info.token);
			trans_list_ptr->info.token = NULL;
			trans_list_ptr->info.token = buf;
		}
		trans_list_ptr = trans_list_ptr->next;
	}
}

t_list	*parse(char *line, char **envp)
{
	t_list	*token_list;
	t_list	*token_list_head;
	t_list	*trans_list;
	t_list	*trans_list_head;

	token_list_head = list_init(&token_list);
	parse_tokenize(&token_list, line);
	token_list = token_list_head;
	parse_expend(&token_list, envp);
	trans_list_head = list_init(&trans_list);
	parse_translate(&token_list, &trans_list);
	parse_delitmit(&trans_list);

	//trans_list_head = list_init(&trans_list);
	//parse_translate(token_list_head, &trans_list, envp);
	list_free(&token_list_head);
	// return (token_list_head);
	return (trans_list_head);
}
