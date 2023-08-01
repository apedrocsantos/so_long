/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:31:39 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/01 20:09:01 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_sprites(t_data *data)
{
	data->player.next = &data->player2;
	data->player2.next = &data->player3;
	data->player3.next = &data->player4;
	data->player4.next = &data->player;
	return (0);
}

int	animate_sprites(t_data *data)
{
	// data->player = *(data->player.next);
	// ft_printf("%p\n", data->player);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player.img_ptr,
		data->map.start.x * data->size, data->map.start.y * data->size);
	return (0);
}
