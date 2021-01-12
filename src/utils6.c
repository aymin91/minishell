/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:20:15 by amin              #+#    #+#             */
/*   Updated: 2021/01/13 00:28:58 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_right_end_quote(char **command, int i, t_quote *q)
{
	while ((*command)[++i])
	{
		if ((*command)[i] == '\"')
		{
			q->end = i;
			break ;
		}
		else if ((*command)[i] == '\'')
		{
			q->end = i;
			break ;
		}
	}
}

void	check_right_start_quote(char **command, int i, t_quote *q)
{
	while ((*command)[++i])
	{
		if ((*command)[i] == '\"')
		{
			q->type = D_QUOTE;
			q->start = i;
			break ;
		}
		else if ((*command)[i] == '\'')
		{
			q->type = S_QUOTE;
			q->start = i;
			break ;
		}
	}
	check_right_end_quote(command, i, q);
}
