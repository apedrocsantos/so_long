/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:27:34 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/08 10:32:58 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	close_success(t_data *data)
{
	close_window(data, NULL, 0);
	return (0);
}

int	check_victory(void *new_data)
{
	t_data	*data;

	data = new_data;
	if (!data->map.collectibles)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->exit.img_ptr, data->map.exit_pos.x * data->size,
			data->map.exit_pos.y * data->size);
	}
	if (data->map.tab[data->map.start.y][data->map.start.x] == 'L' ||
		data->map.tab[data->map.start.y][data->map.start.x] == 'R')
	{
		ft_printf("You lost!\n");
		close_window(data, NULL, 0);
	}
	if (data->map.tab[data->map.start.y][data->map.start.x] == 'E'
		&& !data->map.collectibles)
	{
		ft_printf("OMG YOU WON!\n");
		close_window(data, NULL, 0);
	}
	return (0);
}

void	get_img(t_data *data, t_img *img, char *str)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, str, &img->w, &img->h);
	if (!img->img_ptr)
		close_window(data, "Error\nError loading images.", 13);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->sl,
			&img->endian);
	if (!img->addr)
		close_window(data, "Error\nError loading images.", 12);
}

void	init_imgs(t_data *data)
{
	data->player.img_ptr = NULL;
	data->player_left.img_ptr = NULL;
	data->player_right.img_ptr = NULL;
	data->wall.img_ptr = NULL;
	data->floor.img_ptr = NULL;
	data->collectible.img_ptr = NULL;
	data->exit.img_ptr = NULL;
	data->enemy.img_ptr = NULL;
	data->enemy_reg.img_ptr = NULL;
	data->enemy_inv.img_ptr = NULL;
	get_img(data, &data->player_left, "./assets/player_left.xpm");
	get_img(data, &data->player_right, "./assets/player_right.xpm");
	data->player = data->player_right;
	get_img(data, &data->wall, "./assets/wall.xpm");
	get_img(data, &data->floor, "./assets/floor.xpm");
	get_img(data, &data->collectible, "./assets/collectible.xpm");
	get_img(data, &data->exit, "./assets/exit.xpm");
	get_img(data, &data->enemy_reg, "./assets/enemy.xpm");
	get_img(data, &data->enemy_inv, "./assets/enemy_invert.xpm");
	data->enemy = data->enemy_reg;
	data->size = data->player.h;
}

void	draw_rectangle(t_data *data)
{
	int	j;
	int	i;

	j = data->map.size.y * data->size - 1;
	i = data->map.size.x * data->size;
	while (++j < (data->map.size.y + 1) * data->size)
	{
		i = -1;
		while (++i < data->map.size.x * data->size)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x000000);
	}
}
