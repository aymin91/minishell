/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amin <amin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:07:12 by amin              #+#    #+#             */
/*   Updated: 2020/12/24 10:07:13 by amin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *des, const char *src, size_t n)
{
	size_t	res;

	res = 0;
	while (src[res] && res + 1 < n)
	{
		des[res] = src[res];
		++res;
	}
	if (n != 0)
		des[res] = 0;
	while (src[res])
		++res;
	return (res);
}
