/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gicho <gicho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:41:29 by amin              #+#    #+#             */
/*   Updated: 2021/01/08 17:16:03 by gicho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long long n, int size)
{
	if (n < 10)
		return (size + 1);
	return (ft_size(n / 10, size + 1));
}

static void	tmp(int *i, long long *nbr, int n)
{
	if (n < 0)
	{
		*i = 1;
		*nbr = (long long)n * -1;
	}
	else
	{
		*i = 0;
		*nbr = (long long)n;
	}
}

char		*ft_itoa(int n)
{
	char		*num;
	int			size;
	int			i;
	long long	nbr;

	tmp(&i, &nbr, n);
	size = ft_size(nbr, i);
	if (!(num = (char *)malloc(size + 1)))
		return (0);
	if (i == 1)
		num[0] = '-';
	num[size] = '\0';
	while (--size >= i)
	{
		num[size] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (num);
}
