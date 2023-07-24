/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:14 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/24 22:38:59 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include "includes/mlx.h"

void *put_img(t_data *data)
{
	data->img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/Player/idle/idle1.xpm", &data->img.w, &data->img.h);
	mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.sl, &data->img.endian);
	data->img.bpp *= 2;
	return (data->img.img_ptr);
}

int key_func(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		return (0);
	}
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->img.pos_y > 0 && (key == XK_w || key == XK_Up))
		data->img.pos_y -= data->img.h;
	else if (data->img.pos_x > 0 && (key == XK_a  || key == XK_Left))
		data->img.pos_x -= data->img.w;
	else if (key == XK_s  || key == XK_Down)
		data->img.pos_y += data->img.h;
	else if (key == XK_d  || key == XK_Right)
		data->img.pos_x += data->img.w;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, put_img(data), data->img.pos_x, data->img.pos_y);
	return (0);
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return(0);
}

int handle_no_input(void *data)
{
	(void) data;
	return (0);
}

void mega_free(t_data *data, t_map *map)
{
	free(data->mlx_ptr);
	if (*map->tab)
		free_map(map);
}


int	main(int ac, char **av)
{
	t_data data;
	t_map	map;
	data.img.pos_y = 0;
	data.img.pos_x = 0;
	int rtn = 0;

	map.tab = NULL;
	if (ac != 2)
	{
		ft_printf("Error: invalid command. use ./so_long path/to/map.ber\n");
		return (-1);
	}
	if ((rtn = check_map(av[1], &map)))
		ft_printf("Error: invalid map.\n");
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, map.size.x * 32, map.size.y * 32, "so_long");
	mlx_key_hook(data.win_ptr, key_func, &data);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx_ptr, handle_no_input, 0);
	ft_printf("%d %d\n", map.start.x, map.start.y);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, put_img(&data), map.start.x * 32, map.start.y * 32);
	mlx_loop(data.mlx_ptr);
	mega_free(&data, &map);
	return (rtn);
}
