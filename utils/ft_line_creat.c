/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_creat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:44:43 by taehkim2          #+#    #+#             */
/*   Updated: 2023/12/15 13:53:21 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_char_is_pipe(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len == 1 && line[0] == '|')
		return (END);
	else if (line[len - 1] == '|')
	{
		len -= 2;
		while (len >= 0 && line[len] == ' ')
			len--;
		if (len == -1)
			return (END);
		else if (line[len] == '|' || line[len] == '<' || line[len] == '>')
			return (END);
		return (NEXT);
	}
	return (END);
}

void	line_remake_child(char *line, int *line_pipes)
{
	char	*tmp;

	line_creat_mode();
	close(line_pipes[0]);
	while (1)
	{
		if (end_char_is_pipe(line))
			break ;
		tmp = readline("> ");
		if (tmp == NULL)
			eof_in_line_creat();
		line = my_strjoin(&line, tmp);
		if (line == NULL)
			error_end("malloc failed");
		free(tmp);
	}
	write(line_pipes[1], line, ft_strlen(line));
	close(line_pipes[1]);
	exit(0);
}

char	*pull_line_to_pipe(int *line_pipes)
{
	char	*line;
	char	tmp[11];
	int		bytes;

	line = NULL;
	ft_bzero(tmp, 10);
	close(line_pipes[1]);
	while (1)
	{
		bytes = read(line_pipes[0], tmp, 10);
		if (bytes == 0)
			break ;
		line = my_strjoin(&line, tmp);
		if (line == NULL)
			error_end("malloc failed");
		ft_bzero(tmp, 10);
	}
	close(line_pipes[0]);
	return (line);
}

void	line_recreat(char **line, int *status)
{
	int	line_pipes[2];
	int	pid;

	if (pipe(line_pipes) == -1)
		error_end("pipe failed");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		error_end("fork failed");
	else if (pid == 0)
		line_remake_child(*line, line_pipes);
	else if (pid > 0)
	{
		waitpid(pid, status, 0);
		status_check_line_creat(status);
		free(*line);
		if (*status != 0)
		{
			close(line_pipes[0]);
			close(line_pipes[1]);
			*line = NULL;
		}
		else
			*line = pull_line_to_pipe(line_pipes);
	}
}

char	*line_creat(int *status)
{
	char	*line;

	line = readline("minishell$ ");
	if (g_signal == 2)
	{
		g_signal = 0;
		*status = 1;
	}
	if (line == NULL)
	{
		eof_in_interactive();
		exit(*status);
	}
	else if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	if (end_char_is_pipe(line) == 0)
		line_recreat(&line, status);
	return (line);
}
