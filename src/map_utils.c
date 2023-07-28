/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:22:58 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/28 17:35:53 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_start_pos_and_exit(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (map->tab[j] && map->tab[j][++i])
	{
		if (map->tab[j][i] == 'P')
		{
			map->start.y = j;
			map->start.x = i;
		}
		if (map->tab[j][i] == 'E')
		{
			map->exit_pos.y = j;
			map->exit_pos.x = i;
		}
		if (!map->tab[j][i + 1])
		{
			j++;
			i = -1;
		}
	}
}

int	check_chars(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (map->tab[j] && map->tab[j][++i])
	{
		if (map->tab[j][i] == 'C')
			map->collectibles++;
		else if (map->tab[j][i] == 'E')
			map->exits++;
		else if (map->tab[j][i] == 'P')
			map->players++;
		else if (map->tab[j][i] != '1' && map->tab[j][i] != '0')
			return (2);
		if (!map->tab[j][i + 1])
		{
			j++;
			i = -1;
		}
	}
	if (map->exits != 1 || map->players != 1 || map->collectibles < 1)
		return (4);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->tab && map->tab[i])
		free(map->tab[i++]);
	free(map->tab);
}

int	check_ber(char *str)
{
	if (ft_strchr(str, '.'))
		if (!strncmp(ft_strchr(str, '.'), ".ber\0", 5))
			return (0);
	ft_putendl_fd("Error\nInvalid map.", 2);
	exit (7);
}
