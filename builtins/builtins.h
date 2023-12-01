/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihlee <sihlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:17:36 by sihlee            #+#    #+#             */
/*   Updated: 2023/12/01 14:38:43 by sihlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

int		cd(char **argv);
int		echo(char **argv);
int		export(char **argv, char **envp);
int		pwd(char **argv);
int		unset(char **argv, char **envp);

int		namelen(const char *str, char find);
char	*findenv(const char *name, int *offset, char **envp);
char	*ft_getenv(char *name, char **envp);
void	printenv(char **envp);
void	cleanenv(char **envp);
void	sortenv(char **envp);

void	*ft_realloc(void *memblock, size_t size);
void	swap(char **envp1, char **envp2);
#endif
