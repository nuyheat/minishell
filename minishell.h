/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:16:01 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/15 21:24:40 by taehkim2         ###   ########.fr       */
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

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token_info		info;
}	t_token_list;

void			error_end(char *str);
void			token_add(t_token_list **token_list, char *new_token, int new_flags);
int				get_flags(t_token_list *list);
char			*get_token(t_token_list *list);
void			list_add(t_token_list **list);
t_token_list	*list_init(t_token_list **list);
void			list_free(t_token_list **list);
void			parse(t_token_list **list, char *line);


#endif
