/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:16:01 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/08 19:42:45 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "../builtins/builtins.h"

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

typedef struct s_pipe
{
	int	next_fd[2];
	int	prev_fd[2];
	int redir_less_occured;
	int redir_heredoc_occured;
	int	redir_grate_occured;
	int	here_doc[2];
	int	std_fds[2];
}	t_pipe;

# define NOT_QUOTED			0
# define QUOTED				1

# define ERROR				-1
# define NEXT				0
# define END				1

# define START				1
# define F_QUOTED			2
# define F_PIPE	     		8
# define F_DOLLAR			16
# define F_STRING      		32
# define F_GRATE			64
# define F_DGRATE			128
# define F_LESS				256
# define F_DLESS			512

/* main utils */
char	*line_creat(void);
void	copy_envp(char **envp);

/* all utils */
void	error_end(char *str);
void	my_free(char *str);
void	my_free2(char **strs);
char	*my_strjoin(char **s1, char *s2);

/* list utils */
void	list_node_add(t_list **list);
t_list	*list_init(t_list **list);
void	list_free(t_list **list);
t_list	*list_delete(t_list **list, t_list **trash);

/* parse tokenize*/
t_list	*parse(char *line, char **envp);
void	token_flgs(t_list **list, int *new_flgs, char *buf);
int		token_rules(t_list **list, char **buf, char *line, char now_idx);
void	token_add(t_list **list, char *new_token, int new_flags);
void	token_delimited(t_list **list, char **buf);

int		flgs_redirection(char *buf, int *new_flgs);
int		flgs_pipe(char *buf, int *new_flgs);
int		flgs_dollar(char *buf, int *new_flgs);
int		flgs_quote(char *buf, int *new_flgs);
void	flgs_quote_dollar(char *buf, int *new_flgs);

int		rules_operator_double(char **buf, char now_char);
int		rules_operator_end(char **buf, char now_char);
int		rules_operator_start(char **buf, char *line, int now_idx);
int		rules_space(char **buf, char *line, int now_idx);
int		rules_comment(char **buf, char *line, int now_idx);

int		is_char(char *line, int now_idx);
int		is_quoted(char *token, int idx, char quote);
int		have_quoted(char *buf);
int		operator_check(char prev_char);

/* parse translate */
char	*trans_param_expansion(char *now_token, char **envp);
char	*expansion_token_merge(char **split_token);
void	expansion_dollar_convert(char ***split_token, char **envp);
char	**expansion_token_split(char *token);
char	**splited_token_init(char *token);

void	trans_quoted_remove(char **token);
void	quote_skip(char *str, int *idx);
int		row_cnt(char **str);

/* execute */
void	execute(t_list *list, char **envp, int flg);

/* excute parent */
/* error */
int		syntax_error(t_list *list);
int		redirection_error(t_list *list);
int		command_error(char *token, char **envp);
/* utils */
char	*command_find(t_list *list);
void	pipe_setting_for_parent(t_pipe *pipes);

/* excute utils args */
void	args_next(t_list **list);
void	args_free(char ***args);
char	**args_make(t_list *list);

/* excute utils builtin */
int		builtin(char **args, char **envp);
int		is_it_builtin(char *command);

/* excute utils redirection */
void	token_change(t_list *list);
void	redirection_handling(t_list *list, t_pipe *pipes);

/* excute child */
void	simple_command(char **args, char **envp);
int		child(t_list *list, t_pipe *pipes, char **envp);
/* utils */
int		is_it_last_order(t_list *list);

#endif
