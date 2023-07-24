/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:16:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/24 22:39:55 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	i = 0;
	j = 0;
	while (map->tab[j] && map->tab[j][i])
	{
		if (map->tab[j][i] == 'C')
			map->collectibles++;
		else if (map->tab[j][i] == 'E')
			map->exits++;
		else if (map->tab[j][i] == 'P')
		{
			map->players++;
			map->start.y = j;
			map->start.x = i;
		}
		else if (map->tab[j][i] != '1' && map->tab[j][i] != '0')
			return (2);
		i++;
		if (!map->tab[j][i])
		{
			j++;
			i = 0;
		}
	}
	if (map->exits != 1 || map->players != 1 || map->collectibles < 1)
		return (3);
	return (flood_fill(map->tab, map, map->start));
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
		return (4);
	while (line)
	{
		map->tab[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '1' || line[map->size.x - 1] != '1')
		{
			free(line);
			close(fd);
			return (5);
		}
	}
	close(fd);
	i = -1;
	while (++i < map->size.x)
		if (map->tab[0][i] != '1' || map->tab[map->size.y - 1][i] != '1')
			return (6);
	return (parse_map(map));
}

int	read_map(char *str, t_map *map)
{
	char	*line;
	int		fd;

	map->size.y = 0;
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (7);
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
			return (8);
		}
	}
	close(fd);
	return (get_map(str, map));
}

int	check_map(char *str, t_map *map)
{
	int	a;

	if ((a = check_ber(str)) || (a = read_map(str, map)))
		return (a);
	return (0);
}
