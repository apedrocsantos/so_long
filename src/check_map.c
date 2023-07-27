/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:16:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/27 17:23:55 by anda-cun         ###   ########.fr       */
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

int	parse_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
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
	if (map->exits != 1 || map->players != 1 || map->collectibles < 1)
		return (4);
	if (!map->checked && !flood_fill(map->tab, map, map->start))
	{
		map->checked = 1;
		free_map(map);
		get_map(map->addr, map);
	}
	else
		return (1);
	return (0);
}

int	get_map(char *str, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	map->tab = (char **)ft_calloc((map->size.y + 1), sizeof(char **));
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (5);
	while (line)
	{
		map->tab[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	close(fd);
	return (parse_map(map));
}

int	read_map(char *str, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (5);
	map->size.x = ft_strlen(line);
	while (line)
	{
		map->size.y++;
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)ft_strlen(line) != map->size.x)
		{
			free(line);
			close(fd);
			return (6);
		}
	}
	close(fd);
	return (get_map(map->addr, map));
}

int	check_map(char *str, t_map *map)
{
	int	a;
	int	b;

	map->checked = 0;
	map->size.y = 0;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	map->tab = NULL;
	a = check_ber(str);
	if (a)
		return (a);
	b = read_map(str, map);
	if (b)
	{
		if (map->tab)
			free_map(map);
		return (b);
	}
	return (0);
}
