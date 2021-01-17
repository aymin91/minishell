/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:28:50 by amin              #+#    #+#             */
/*   Updated: 2021/01/17 16:41:03 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_redir(t_redir *redir)
{
	free(redir->type);
	ft_freearr(redir->argv);
	if (redir->commands != NULL)
		ft_freearr(redir->commands);
}
