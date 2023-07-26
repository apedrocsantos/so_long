/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:42:14 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/26 12:33:26 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

void	*put_img(t_data *data)
{
	data->img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/Player/idle/idle1.xpm", &data->img.w, &data->img.h);
	mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.sl,
			&data->img.endian);
	return (data->img.img_ptr);
}

int	key_func(int key, t_data *data)
{
	
	if (key == XK_Escape)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		return (0);
	}
	if ((key == XK_w || key == XK_Up) && data->map.tab[data->map.start.y-1][data->map.start.x] != '1')
		data->map.start.y--;
	else if ((key == XK_a || key == XK_Left) && data->map.tab[data->map.start.y][data->map.start.x-1] != '1')
		data->map.start.x--;
	else if ((key == XK_s || key == XK_Down) && data->map.tab[data->map.start.y+1][data->map.start.x] != '1')
		data->map.start.y++;
	else if ((key == XK_d || key == XK_Right) && data->map.tab[data->map.start.y][data->map.start.x+1] != '1')
		data->map.start.x++;
	// mlx_clear_window(data->mlx_ptr, data->win_ptr);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, put_img(data),
	// 		data->map.start.x * 32, data->map.start.y * 32);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	base_screen(void *new_data)
{
	// (void) new_data;
	t_data *data = new_data;
	t_img img;

	img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/Player/idle/idle1.xpm", &img.w, &img.h);
	mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.sl,
			&data->img.endian);
	return (0);
}

int game_init (t_data *data)
{
	int rtn;
	rtn = check_map(data->map.addr, &data->map);
	if (rtn)
		return (rtn);
	if (!(data->mlx_ptr = mlx_init()) || !(data->win_ptr = mlx_new_window(data->mlx_ptr, data->map.size.x * 32,
			data->map.size.y * 32, "so_long")))
				ft_printf("ERROR\n");
	return (rtn);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		rtn;
	int		j;

	rtn = 0;
	j = 0;
	data.map.addr = av[1];
	if (ac != 2)
	{
		ft_putstr_fd("Error: invalid command. Try ./so_long path/to/map.ber\n", 2);
		return (-1);
	}
	rtn = game_init(&data);
	if (rtn)
		return(rtn);
	while (data.map.tab[j])
		ft_printf("%s\n", data.map.tab[j++]);
	mlx_key_hook(data.win_ptr, key_func, &data);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx_ptr, &base_screen, 0);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, put_img(&data), data.map.start.x * 32, data.map.start.y * 32);
	mlx_loop(data.mlx_ptr);
	mega_free(&data);
	return (rtn);
}
