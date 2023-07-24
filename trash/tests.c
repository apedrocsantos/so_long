/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 09:12:48 by anda-cun          #+#    #+#             */
/*   Updated: 2023/07/12 22:30:54 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_int.h"
#include <stdio.h>

typedef struct s_struct
{
    void *mlx;
    void *window;
    void *img1;
    char *addr;
    int bpp;
    int sl;
    int endian;
} t_struct;

#define WIDTH 500
#define HEIGHT 500
#define T 255
#define R 255
#define G 255
#define B 0

void	my_mlx_pixel_put(t_struct *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->sl + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int key_func(int key, void *p)
{
    printf("Key: %d\n", key);
    if (key == 65307)
        exit(0);
}

int close_window(t_struct *window)
{
    printf("Here\n");
    mlx_destroy_window(window->mlx, window->window);
    exit(0);
}

int main()
{
    t_struct window;
    
    window.mlx = mlx_init();
    if (!window.mlx)
        perror("Error");
    window.window = mlx_new_window(window.mlx, WIDTH, HEIGHT, "My window");
    if (!window.window)
        perror("Error");
    mlx_hook(window.window, 17, 0, close_window, &window);
    window.img1 = mlx_new_image(window.mlx, WIDTH, HEIGHT);
    window.addr = mlx_get_data_addr(window.img1, &window.bpp, &window.sl, &window.endian);
    int offset = (HEIGHT * window.sl + WIDTH * (window.bpp / 8));
    printf("ll: %d\n", offset);
    int x = WIDTH;
    int y;
    int color;
    while (x--)
    {
        y = HEIGHT;
        while (y--)
        {
            color = (T << 24) + (R << 16) + (G << 8) + B;
            mlx_pixel_put(window.mlx, window.window, x/2, y/2, color);
        }
    }
    mlx_put_image_to_window(window.mlx, window.window, window.img1, WIDTH, HEIGHT);
    sleep(2);
    x = WIDTH;
    while (x--)
    {
        y = HEIGHT;
        while (y--)
        {
            color = ((T - 100) << 24) + (R - 200 << 16) + (G << 8) + B;
            mlx_pixel_put(window.mlx, window.window, x, y, color);
        }
    }
    sleep(2);
    mlx_key_hook(window.window, key_func, 0);
    mlx_loop(window.mlx);
}