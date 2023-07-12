/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:30:52 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/12 09:08:16 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "./includes/so_long.h"
#include <stdio.h>

#define WIN_X 250
#define WIN_Y 250
#define R 100
#define G 100
#define B 255

int main()
{
    mlx_t   test;
    void    *mlx_ptr;
    t_img   image;
    int     local_endian;
    int a = 0x11223344;
    int bpp;
    int size;
    int endian;

    if (((unsigned char *)&a)[0] == 0x11)
        local_endian = 1;
    else
        local_endian = 0;

    mlx_ptr = mlx_init();
    test = (mlx_t) {mlx_ptr, mlx_new_window(mlx_ptr, WIN_X, WIN_Y, "So Long"), WIN_X, WIN_Y};
    if (!test.mlx_ptr || !test.mlx_window)
        return(1);
    image.win = test;
    int x = 0;
    int color;
    
    while (x++ < WIN_X)
    {
      int y = WIN_X;
      while (y--)
        {
	        color = (R<<16) + (G<<8) + B;
            printf("%d\n", color);
            mlx_pixel_put(test.mlx_ptr,test.mlx_window,x,y,color);
        }
    }
    // mlx_clear_window(test.mlx_ptr, test.mlx_window);
    // sleep(1);
    // void *new_img = mlx_new_image(test.mlx_ptr, 42, 42);

    // int y = WIN_Y;
    // while (y--)
    // {
    // x = 42;
    //   while (x--)
    //     {
	//         color = (R + 30 <<16) + (G + 130 <<8) + (B + 100);
    //         printf("new %d\n", color);
    //         mlx_pixel_put(test.mlx_ptr,test.mlx_window,x,y,color);
    //     }
    // }
    mlx_string_put(test.mlx_ptr, test.mlx_window, 42, 150, 0xFF44FF, "Test string");
    
    int xpm1_x;
    int xpm1_y;
    int bpp1, sl1, endian1;
    void *img1 = mlx_xpm_file_to_image(test.mlx_ptr, "open.xpm", &xpm1_x, &xpm1_y);
    printf("%d %d\n", xpm1_x, xpm1_y);
    char *data1 = mlx_get_data_addr(img1,&bpp1, &sl1, &endian1);
    mlx_put_image_to_window(test.mlx_ptr, test.mlx_window, img1, 0, 0);
    // int xpm2_x;
    // int xpm2_y;
    // int bpp2, sl2, endian2;
    // void *img2 = mlx_xpm_file_to_image(test.mlx_ptr, "idle2.xpm", &xpm2_x, &xpm2_y);
    // char *data2 = mlx_get_data_addr(img2,&bpp2, &sl2, &endian2);
    // mlx_put_image_to_window(test.mlx_ptr, test.mlx_window, img2, 0, 0);
    sleep(3);
    // int xpm2_x;
    // int xpm2_y;
    // int bpp2, sl2, endian2;
    // void *img2 = mlx_xpm_file_to_image(test.mlx_ptr, "open24.xpm", &xpm1_x, &xpm1_y);
    // char *data2 = mlx_get_data_addr(img2,&bpp2, &sl2, &endian2);
    // mlx_put_image_to_window(test.mlx_ptr, test.mlx_window, img2, 0, 0);
    // sleep(1);
    // mlx_loop(test.mlx_ptr);
    return(0);
}