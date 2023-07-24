#ifndef SO_LONG_H

#define SO_LONG_H
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

// #define WINDOW_WIDTH 1920
// #define WINDOW_HEIGHT 1080 - 35 - 50


#include "libft.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		sl;
	int		pos_y;
	int		pos_x;
}		t_img;

typedef struct s_data
{
	void *mlx_ptr;
	void *win_ptr;
	t_img img;
}	t_data;

typedef struct s_point
{
	int y;
	int x;
} t_point;

typedef struct s_map
{
	char **tab;
	int collectibles;
	int exits;
	int players;
	t_point size;
	t_point start;
}	t_map;

void	free_map(t_map *map);
int	check_ber(char *str);
int check_map(char *str, t_map *map);

#endif