/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:07:22 by amin              #+#    #+#             */
/*   Updated: 2020/12/24 10:07:23 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char* str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while ((unsigned char)*str1 == (unsigned char)*str2 && *str1 != 0 && n-- > 1)
	{
		str1++;
		str2++;
	}
	if ((unsigned char)*str1 == (unsigned char)*str2)
		return (0);
	else
		return ((unsigned char)*str1 - (unsigned char)*str2);
}
