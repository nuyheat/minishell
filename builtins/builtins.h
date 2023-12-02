/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:17:36 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/02 11:46:17 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

void	cd(char **argv);
void	echo(char **argv);
void	export(char **argv, char **envp);
void	pwd(char **argv);
void	unset(char **argv, char **envp);
void	env(char **argv, char **envp);
void    my_exit(char **argv);
// void	exit(char **argv);

    int namelen(const char *str, char find);
int		ft_putenv(const char *str, char **envp);
char	*findenv(const char *name, int *offset, char **envp);
char	*ft_getenv(char *name, char **envp);
void	printexport(char **envp);
void	cleanenv(char **envp);
void	sortenv(char **envp);

void	*ft_realloc(void *memblock, size_t size);
void	swap(char **envp1, char **envp2);
#endif
