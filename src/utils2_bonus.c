/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:41:27 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/08 10:09:49 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_imgs(t_data *data)
{
	if (data->player_left.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->player_left.img_ptr);
	if (data->player_right.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->player_right.img_ptr);
	if (data->wall.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->wall.img_ptr);
	if (data->floor.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->floor.img_ptr);
	if (data->collectible.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->collectible.img_ptr);
	if (data->exit.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->exit.img_ptr);
	if (data->enemy_reg.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->enemy_reg.img_ptr);
	if (data->enemy_inv.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->enemy_inv.img_ptr);
}

int	close_window(t_data *data, char *error, int rtn)
{
	if (error)
		ft_putendl_fd(error, 2);
	free_map(&data->map);
	free_imgs(data);
	if (data->mlx_ptr != NULL && data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	ft_printf("Program closed.\n");
	exit(rtn);
}

void	move_player(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor.img_ptr,
		data->map.start.x * data->size, data->map.start.y * data->size);
	data->map.start.y += y;
	data->map.start.x += x;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr,
		data->map.start.x * data->size, data->map.start.y * data->size);
}
