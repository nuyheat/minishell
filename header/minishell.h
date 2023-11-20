/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:16:01 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 22:59:14 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>

# include "../libft/libft.h"

typedef struct s_token_info
{
	char	*token;
	int		flgs;
}	t_token_info;

typedef struct s_list
{
	struct s_list	*next;
	t_token_info	info;
}	t_list;

# define QUOTED				1
# define NOT_QUOTED			0

# define NEXT				0
# define END				1

# define DQUOTE         	1    // flgs_quote 함수에서 사용
// # define DQUOTE_END   		2	 // flgs_quote 함수에서 사용
# define QUOTE        		4	 // flgs_quote 함수에서 사용
// # define QUOTE_END    		8	 // flgs_quote 함수에서 사용
# define PIPE	     		16	 // flgs_pipe 함수에서 사용
# define DOLLAR				32	 // flgs_dollar 함수에서 사용
//# define DOLLAR_PARAM		64	 // flgs_dollar 함수에서 사용
# define COMMAND      		128	 // flgs_command 함수에서 사용
# define OPTION 	 		256
# define STRING      		512
# define REDIRECT_LEFT		1024 // flgs_redirect 함수에서 사용
# define REDIRECT_LEFT_END	2048 // flgs_redirect 함수에서 사용
# define REDIRECT_RIGHT		4096 // flgs_redirect 함수에서 사용
# define REDIRECT_RIGHT_END	8192 // flgs_redirect 함수에서 사용


void	error_end(char *str);
void	token_add(t_list **list, char *new_token, int new_flags);
int		get_flags(t_list *list);
char	*get_token(t_list *list);
void	list_node_add(t_list **list);
t_list	*list_init(t_list **list);
void	list_free(t_list **list);
void	parse(t_list **list, char *line);
void	tokenize_flgs(t_list **list, int *new_flgs, char now_char);
void	flgs_quote(int *new_flgs, char now_char);
void	flgs_command(t_list **list, int *new_flgs, char now_char);
void	flgs_redirect(int *new_flgs, char now_char);
void	flgs_pipe(int *new_flgs, char now_char);
void	flgs_dollar(int *new_flgs, char now_char);
int		tokenize_operator_double(char **buf, char now_char);
int		tokenize_operator_end(char **buf, char now_char);
int		tokenize_operator_start(char **buf, char now_char);
int		tokenize_space(char **buf, char now_char);
//void	tokenize_six(char **buf, char now_char);
int		tokenize_comment(char **buf, char now_char);
int		quote_check(char *buf);
int		operator_check(char prev_char);
// int		operator_check(char *buf);
void	token_delimited(t_list **list, char **buf);

#endif
