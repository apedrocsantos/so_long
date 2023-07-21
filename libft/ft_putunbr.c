/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 23:17:16 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/06 19:39:15 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(long unsigned int n, unsigned int base, char fs)
{
	int		i;
	char	*str;

	str = "0123456789abcdef";
	if (fs == 'X')
		str = "0123456789ABCDEF";
	i = 0;
	if (n < base)
		i += ft_putchar(str[n]);
	else
	{
		i += ft_putunbr(n / base, base, fs);
		i += ft_putunbr(n % base, base, fs);
	}
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i;

	i = ft_putunbr(21596, 16, 'p');
	printf("\n%d\n", i);
}*/
