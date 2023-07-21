/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:52:28 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/06 19:39:15 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr(long unsigned int n, unsigned int base, char fs)
{
	int	i;

	if (n == 0)
		return (i = ft_putstr("(nil)"));
	i = ft_putstr("0x");
	i += ft_putunbr(n, base, fs);
	return (i);
}
