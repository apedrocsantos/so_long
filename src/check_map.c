/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 08:16:30 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/20 12:23:50 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

// int check_walls(char **tab, t_point size)
// {

// }

void	flood_fill(char **tab, t_point size, t_point cur, int *collectibles,
		int *exits)
{
	if (tab[cur.y][cur.x] == 'C')
		*collectibles -= 1;
	else if (tab[cur.y][cur.x] == 'E')
		*exits -= 1;
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x
		|| (tab[cur.y][cur.x] != 'C' && tab[cur.y][cur.x] != 'E'
			&& tab[cur.y][cur.x] != '0' && tab[cur.y][cur.x] != 'P'))
		return ;
	tab[cur.y][cur.x] = 'F';
	flood_fill(tab, size, (t_point){cur.x + 1, cur.y}, collectibles, exits);
	flood_fill(tab, size, (t_point){cur.x - 1, cur.y}, collectibles, exits);
	flood_fill(tab, size, (t_point){cur.x, cur.y + 1}, collectibles, exits);
	flood_fill(tab, size, (t_point){cur.x, cur.y - 1}, collectibles, exits);
}

// void get_size(char **tab, int y, int x)
// {
// 	char *line = get_next_line()
// }

int	check_map(char **tab, t_point size)
{
	int		collectibles;
	int		exits;
	int		j;
	int		i;
	int		player;
	t_point	begin;

	collectibles = 0;
	exits = 0;
	j = 0;
	player = 0;
	if (size.x == size.y || !size.x || !size.y)
		return (-1);
	while (j < size.y)
	{
		i = 0;
		while (i < size.x)
		{
			if (tab[j][i] == 'C')
				collectibles++;
			else if (tab[j][i] == 'E')
				exits++;
			else if (tab[j][i] == 'P')
			{
				player++;
				begin.y = j;
				begin.x = i;
			}
			i++;
		}
		if (exits > 1 || player > 1)
			return (-1);
		j++;
	}
	if (exits == 0)
		return (-1);
	flood_fill(tab, size, begin, &collectibles, &exits);
	if (collectibles || exits)
		return (-1);
	return (0);
}

int	get_map(char *str)
{
	char	*line;
	// char	**tab;
	int		fd;
	size_t		x;
	size_t		y;

	// tab = malloc(sizeof (char **));
	y = 0;
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line)
		y++;
	x = ft_strlen(line);
	ft_printf("%s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (x != ft_strlen(line))
			break ;
		y++;
	ft_printf("%s", line);
	}
	if(line)
		free(line);
	printf("x: %ld, y: %ld\n", x, y);
	return (0);
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
	if (ac == 2)
	{
		if (!check_ber(av[1]))
			return (-1);
		if (get_map(av[1]))
			return (-1);
	}
}
