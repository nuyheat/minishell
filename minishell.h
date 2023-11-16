/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:16:01 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/16 15:04:18 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_token_info
{
	char	*token;
	int		flags;
}	t_token_info;

typedef struct s_list
{
	struct s_list	*next;
	t_token_info	info;
}	t_list;

# define DQUOTE     1
# define DQUOTE_END 2
# define QUOTE      4
# define QUOTE_END  8
# define OPERATOR   16
# define DOLLAR     32
# define COMMAND    64
# define COMMENT    128

void	error_end(char *str);
void	parse_token_add(t_list **list, char *new_token, int new_flags);
int		get_flags(t_list *list);
char	*get_token(t_list *list);
void	list_add(t_list **list);
t_list	*list_init(t_list **list);
void	list_free(t_list **list);
void	parse(t_list **list, char *line);


#endif
