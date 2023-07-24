#include <X11/keysym.h>
#include <stdlib.h>
#include <X11/X.h>
#include "includes/mlx.h"
#include <stdio.h>
#include "includes/so_long.h"
// #include "includes/so_long.h"

int	handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);

    return (0);
}

int	handle_no_event(void *data)
{
    (void)data;
    /* This function needs to exist, but it is useless for the moment */
    return (0);
}

int	main(void)
{
    t_data	data;
    void    *img;
    int		img_width;
    int 	img_height;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (10);
    data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "My first window!");
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (10);
    }

    /* Setup hooks */ 
    mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
    img = mlx_xpm_file_to_image(data.mlx_ptr, "open30.xpm", &img_width, &img_height);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, 50, 50);
    mlx_loop(data.mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}

