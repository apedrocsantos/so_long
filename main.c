/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:30:52 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/07 17:57:59 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "./includes/so_long.h"
#include <stdio.h>

int main()
{
    mlx_t   test;
    void    *mlx_ptr;
    int     width = 500;
    int     height = 500;

    mlx_ptr = mlx_init();
    test = (mlx_t) {mlx_ptr, mlx_new_window(mlx_ptr, width, height, "title"), width, height};
    if (!test.mlx_ptr || !test.mlx_window)
        return(1);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 250, 250, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 251, 251, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 252, 252, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 253, 253, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 254, 254, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 255, 255, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 256, 256, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 257, 257, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 258, 258, 55);
    mlx_pixel_put(test.mlx_ptr, test.mlx_window, 259, 259, 55);
    mlx_loop(test.mlx_ptr);
    return(0);
}