/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_flgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkim2 <taehkim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:13:10 by taehkim2          #+#    #+#             */
/*   Updated: 2023/11/20 21:56:00 by taehkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_flgs(t_list **list, int *new_flgs, char now_char)
{
	flgs_quote(new_flgs, now_char);
	flgs_command(list, new_flgs, now_char);
	flgs_redirect(new_flgs, now_char);
	flgs_pipe(new_flgs, now_char);
	flgs_dollar(new_flgs, now_char);
}
