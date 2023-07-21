/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:22:58 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/21 22:24:23 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/so_long.h"
#include <stdlib.h>

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->tab[i])
		free(map->tab[i++]);
	free(map->tab);
}

int	check_ber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 4 && str[i - 4] && strncmp(&str[i - 4], ".ber", 4) == 0)
		return (0);
	return (9);
}
