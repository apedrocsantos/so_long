/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:31:39 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/08 10:09:00 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_left(t_data *data, int i, int j)
{
	if (data->map.tab[j][i - 1] == '0' || data->map.tab[j][i - 1] == 'P')
	{
		data->map.tab[j][i] = '0';
		data->map.tab[j][i - 1] = 'L';
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor.img_ptr, i * data->size, j * data->size);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->enemy.img_ptr, (i - 1) * data->size, j * data->size);
		return (0);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy.img_ptr, i
		* data->size, j * data->size);
	data->map.tab[j][i] = 'R';
	return (1);
}

int	check_right(t_data *data, int i, int j)
{
	if (data->map.tab[j][i + 1] == '0' || data->map.tab[j][i + 1] == 'P')
	{
		data->map.tab[j][i] = '0';
		data->map.tab[j][i + 1] = 'R';
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->floor.img_ptr, i * data->size, j * data->size);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->enemy.img_ptr, (i + 1) * data->size, j * data->size);
		return (0);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy.img_ptr, i
		* data->size, j * data->size);
	data->map.tab[j][i] = 'L';
	return (1);
}

void	draw_enemy(t_data *data, int j, int i)
{
	while (data->map.tab[j] && data->map.tab[j][i++])
	{
		if (data->map.tab[j][i] == 'L' || data->map.tab[j][i] == 'R')
		{
			if (data->map.tab[j][i] == 'L')
			{
				if (!check_left(data, i, j))
					i--;
			}
			else
			{
				if (!check_right(data, i, j))
					i++;
			}
			check_victory(data);
		}
		if (!data->map.tab[j][i + 1])
		{
			j++;
			i = 0;
		}
	}
}

int	animate_sprites(t_data *data)
{
	data->anim_counter++;
	if (data->anim_counter == data->anim_speed / 2
		|| data->anim_counter == data->anim_speed)
	{
		if (data->anim_counter == data->anim_speed / 2)
			data->enemy = data->enemy_inv;
		if (data->anim_counter == data->anim_speed)
		{
			data->enemy = data->enemy_reg;
			data->anim_counter = 0;
		}
		draw_enemy(data, 0, 0);
	}
	return (0);
}
