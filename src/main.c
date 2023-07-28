/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:14 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/28 18:29:33 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Hold key; Exit routines (error and clean); Bonus; Norminette; Edge cases;*/

void	counter(t_data *data, int *x, int *y)
{
	char	*move_count;
	char	*str;

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr,
		*x * data->size, *y * data->size);
	if (data->map.tab[*y][*x] == 'C')
	{
		data->map.collectibles--;
		data->map.tab[*y][*x] = '0';
	}
	data->move_count++;
	move_count = ft_itoa(data->move_count);
	str = ft_strjoin("MOVES: ", move_count);
	draw_rectangle(data);
	mlx_string_put(data->mlx_ptr, data->win_ptr, (data->map.size.x - 0.5) / 2
		* 31, data->map.size.y * data->size + data->size / 1.5, 0xFFFFFF,
		str);
	ft_printf("Moves: %d\n", data->move_count);
	free(move_count);
	free(str);
}

int	key_func(int key, t_data *data)
{
	if (key == XK_Escape)
		close_success(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr,
		data->map.start.x * data->size, data->map.start.y * data->size);
	if ((key == XK_w || key == XK_Up) && data->map.tab[data->map.start.y
			- 1][data->map.start.x] != '1')
		(data->map.start.y)--;
	else if ((key == XK_a || key == XK_Left)
		&& data->map.tab[data->map.start.y][data->map.start.x - 1] != '1')
		(data->map.start.x)--;
	else if ((key == XK_s || key == XK_Down) && data->map.tab[data->map.start.y
			+ 1][data->map.start.x] != '1')
		(data->map.start.y)++;
	else if ((key == XK_d || key == XK_Right)
		&& data->map.tab[data->map.start.y][data->map.start.x + 1] != '1')
		(data->map.start.x)++;
	else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player.img_ptr, data->map.start.x * data->size,
			data->map.start.y * data->size);
		return (0);
	}
	counter(data, &data->map.start.x, &data->map.start.y);
	return (0);
}

void	*draw_screen(t_data *data, int j, int i)
{
	while (data->map.tab[j] && data->map.tab[j][++i])
	{
		if (data->map.tab[j][i] == '1')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->wall.img_ptr, i * data->size, j * data->size);
		else if (data->map.tab[j][i] == 'C')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->collectible.img_ptr, i * data->size, j * data->size);
		else if (data->map.tab[j][i] == 'P')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->player.img_ptr, i * data->size, j * data->size);
		else
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->floor.img_ptr, i * data->size, j * data->size);
		if (!data->map.tab[j][i + 1])
		{
			j++;
			i = -1;
		}
	}
	return (NULL);
}

int	game_init(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->move_count = 0;
	check_map(&data->map);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		close_window(data, "Error\nError creating window.", 10);
	init_imgs(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map.size.x * data->size,
			data->map.size.y * data->size + data->size, "so_long");
	if (!data->win_ptr)
		close_window(data, "Error\nError creating window.", 10);
	draw_screen(data, 0, -1);
	draw_rectangle(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.map.addr = av[1];
	if (ac != 2)
	{
		ft_putendl_fd("Error\nTry ./so_long path/to/map.ber", 2);
		return (-1);
	}
	game_init(&data);
	mlx_key_hook(data.win_ptr, key_func, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_success, &data);
	mlx_loop_hook(data.mlx_ptr, &check_victory, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
