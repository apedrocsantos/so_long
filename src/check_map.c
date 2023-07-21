/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:16:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/21 16:24:05 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	flood_fill(char **tab, t_map *map, t_point cur)
{
	ft_printf("aaa %c %d - %d %d - %d\n", tab[cur.y][cur.x], cur.y, map->size.y, cur.x, map->size.x);
	if (cur.y < 0 || cur.y >= map->size.y || cur.x < 0 || cur.x >= map->size.x
		|| (tab[cur.y][cur.x] == 'F' && tab[cur.y][cur.x] == '1'))
			return ;
	if (tab[cur.y][cur.x] == 'C')
		map->collectibles -= 1;
	else if (tab[cur.y][cur.x] == 'E')
		map->exits -= 1;
	map->tab[cur.y][cur.x] = 'F';
	ft_printf("aaa %c %d %d\n", tab[cur.y][cur.x], cur.y, cur.x);
	ft_printf("y + 1\n");
	flood_fill(tab, map, (t_point){cur.y + 1, cur.x});
	ft_printf("y - 1\n");
	flood_fill(tab, map, (t_point){cur.y - 1, cur.x});
	flood_fill(tab, map, (t_point){cur.y, cur.x + 1});
	flood_fill(tab, map, (t_point){cur.y, cur.x - 1});
}

int	parse_map(t_map *map)
{
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
	int i;
	int j;

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
		i++;
		if (!map->tab[j][i])
		{
			j++;
			i = 0;
		}
	}
	ft_printf("E %d, P %d, C %d, S %dy %dx\n", map->exits, map->players, map->collectibles, map->start.y, map->start.x);
	if (map->exits != 1 || map->players != 1 || map->collectibles < 2)
		return (-1);
	flood_fill(map->tab, map, map->start);
	return (0);
}

int	get_map(char *str, t_map *map)
{
	int		fd;
	size_t	i;
	char	*line;

	i = 0;
	map->tab = (char **)ft_calloc((map->size.y + 1), sizeof(char **));
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (-2);
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
			return (-1);
		}
	}
	close(fd);
	i = -1;
	while (++i < map->size.x)
		if (map->tab[0][i] != '1' || map->tab[map->size.y - 1][i] != '1')
			return (-1);
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
		return (-2);
	map->size.x = ft_strlen(line);
	while (line)
	{
		map->size.y++;
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) != map->size.x)
		{
			free(line);
			return (-1);
		}
	}
	close(fd);
	return (get_map(str, map));
}

int	check_ber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 4 && str[i - 4] && strncmp(&str[i - 4], ".ber", 4) == 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac == 2)
	{
		if (!check_ber(av[1]))
			return (-1);
		if (read_map(av[1], &map))
			return (-1);
	}
}
