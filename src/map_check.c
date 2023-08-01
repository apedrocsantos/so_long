/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:16:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/30 19:07:36 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill(char **tab, t_map *map, t_point cur)
{
	if (cur.y < 0 || cur.y >= map->size.y || cur.x < 0 || cur.x >= map->size.x
		|| (tab[cur.y][cur.x] == 'F' || tab[cur.y][cur.x] == '1'))
		return (0);
	if (tab[cur.y][cur.x] == 'C')
		map->collectibles -= 1;
	else if (tab[cur.y][cur.x] == 'E')
		map->exits -= 1;
	map->tab[cur.y][cur.x] = 'F';
	flood_fill(tab, map, (t_point){cur.y + 1, cur.x});
	flood_fill(tab, map, (t_point){cur.y - 1, cur.x});
	flood_fill(tab, map, (t_point){cur.y, cur.x + 1});
	flood_fill(tab, map, (t_point){cur.y, cur.x - 1});
	if (!map->collectibles && !map->exits)
		return (0);
	return (1);
}

int	parse_map(t_map *map, int i, int j)
{
	if (check_chars(map))
		return (2);
	get_start_pos_and_exit(map);
	while (map->tab[j] && map->tab[j][++i])
	{
		if (j == 0 || j == map->size.y - 1 || i == 0 || i == map->size.x - 1)
			if (map->tab[j][i] != '1')
				return (3);
		if (!map->tab[j][i + 1])
		{
			j++;
			i = -1;
		}
	}
	if (map->checked)
		return (0);
	if (flood_fill(map->tab, map, map->start))
		return (5);
	map->checked = 1;
	free_map(map);
	get_map(map);
	return (0);
}

int	get_map(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	map->fd = open(map->addr, O_RDONLY);
	map->tab = (char **)ft_calloc((map->size.y + 1), sizeof(char **));
	if (!map->tab)
		return (6);
	line = get_next_line(map->fd);
	if (!line)
		return (7);
	while (line)
	{
		map->tab[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			break ;
	}
	close(map->fd);
	return (parse_map(map, -1, 0));
}

int	read_map(t_map *map)
{
	char	*line;

	map->fd = open(map->addr, O_RDONLY);
	if (map->fd < 0)
		return (8);
	line = get_next_line(map->fd);
	if (line == NULL)
		return (9);
	map->size.x = ft_strlen(line);
	while (line)
	{
		map->size.y++;
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		if ((int)ft_strlen(line) != map->size.x)
		{
			free(line);
			close(map->fd);
			return (10);
		}
	}
	close(map->fd);
	return (get_map(map));
}

int	check_map(t_map *map)
{
	int	a;

	map->checked = 0;
	map->size.y = 0;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	map->tab = NULL;
	check_ber(map->addr);
	a = read_map(map);
	if (!a)
		return (0);
	if (map->tab)
		free_map(map);
	ft_putendl_fd("Error\nInvalid map.", 2);
	exit (a);
}
