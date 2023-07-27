/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:14 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/27 17:32:43 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_img(t_data *data, t_img *img, char *str)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, str, &img->w, &img->h);
	if (!img->img_ptr)
		error_end_program(data, "Error loading images.", 12);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->sl,
			&img->endian);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img->img_ptr, 10, 10);
	if (!img->addr)
		error_end_program(data, "Error loading images.", 12);
}

void	init_imgs(t_data *data)
{
	get_img(data, &data->player, "./assets/player.xpm");
	get_img(data, &data->wall, "./assets/wall.xpm");
	get_img(data, &data->floor, "./assets/floor.xpm");
	get_img(data, &data->collectible, "./assets/collectible.xpm");
	get_img(data, &data->exit, "./assets/exit.xpm");
}

void	counter(t_data *data, int *x, int *y)
{
	char	*move_count;

	data->move_count++;
	move_count = ft_itoa(data->move_count);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr,
		*x * 32, *y * 32);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall.img_ptr,
		(data->map.size.x - 1) / 2 * 32, (data->map.size.y - 1) * 32);
	mlx_string_put(data->mlx_ptr, data->win_ptr, (data->map.size.x - 0.5) / 2
		* 31, data->map.size.y * 31, 0x000000, move_count);
	free(move_count);
	if (data->map.tab[*y][*x] == 'C')
	{
		data->map.collectibles--;
		data->map.tab[*y][*x] = '0';
	}
	if (!data->map.collectibles)
		data->map.tab[data->map.exit_pos.y][data->map.exit_pos.x] = 'E';
	if (data->map.tab[*y][*x] == 'E')
	{
		ft_printf("GG!\n");
		close_window(data);
	}
}

int	key_func(int key, t_data *data)
{
	int	*y;
	int	*x;

	y = &data->map.start.y;
	x = &data->map.start.x;
	if (key == XK_Escape)
		close_window(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr,
		*x * 32, *y * 32);
	if ((key == XK_w || key == XK_Up) && data->map.tab[*y - 1][*x] != '1')
		(*y)--;
	else if ((key == XK_a || key == XK_Left) && data->map.tab[*y][*x
		- 1] != '1')
		(*x)--;
	else if ((key == XK_s || key == XK_Down) && data->map.tab[*y
			+ 1][*x] != '1')
		(*y)++;
	else if ((key == XK_d || key == XK_Right) && data->map.tab[*y][*x
		+ 1] != '1')
		(*x)++;
	else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player.img_ptr, *x * 32, *y * 32);
		return (0);
	}
	counter(data, x, y);
	return (0);
}

int	nothing(void *data)
{
	data++;
	return (0);
}

void	*draw_screen(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (data->map.tab[j] && data->map.tab[j][++i])
	{
		if (data->map.tab[j][i] == '1')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->wall.img_ptr, i * 32, j * 32);
		if (data->map.tab[j][i] == '0' || data->map.tab[j][i] == 'C'
			|| data->map.tab[j][i] == 'P' || data->map.tab[j][i] == 'E')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->floor.img_ptr, i * 32, j * 32);
		if (data->map.tab[j][i] == 'E')
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->exit.img_ptr, i * 32, j * 32);
			data->map.tab[j][i] = '1';
		}
		if (data->map.tab[j][i] == 'C')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->collectible.img_ptr, i * 32, j * 32);
		if (data->map.tab[j][i] == 'P')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->player.img_ptr, i * 32, j * 32);
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
	int	rtn;

	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->move_count = 0;
	rtn = check_map(data->map.addr, &data->map);
	if (rtn)
	{
		ft_putendl_fd("Invalid map.", 2);
		exit(rtn);
	}
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map.size.x * 32,
			data->map.size.y * 32, "so_long");
	if (!data->mlx_ptr || !data->win_ptr)
		error_end_program(data, "Error while creating window.", 10);
	init_imgs(data);
	draw_screen(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		j;

	j = 0;
	data.map.addr = av[1];
	if (ac != 2)
	{
		ft_putendl_fd("Error: invalid command. Try ./so_long path/to/map.ber",
			2);
		return (-1);
	}
	game_init(&data);
	mlx_key_hook(data.win_ptr, key_func, &data);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx_ptr, &nothing, 0);
	mlx_loop(data.mlx_ptr);
	return (0);
}
