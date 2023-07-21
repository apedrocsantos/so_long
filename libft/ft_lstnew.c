/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:26:53 by anda-cun          #+#    #+#             */
/*   Updated: 2023/05/26 11:25:32 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	else
	{
		newnode->content = content;
		newnode->next = NULL;
		newnode->previous = NULL;
	}
	return (newnode);
}
/*
int	main(void)
{
	printf("%s\n", ft_lstnew("aeiou") -> content);
}*/
