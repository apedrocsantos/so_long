#ifndef SO_LONG_H
#define SO_LONG_H

typedef struct mlx
{
    void    *mlx_ptr;
    void    *mlx_window;
    int     width;
    int     height;
} mlx_t;

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

typedef struct s_img
{
	mlx_t	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;

void	free_map(t_map *map);
int	check_ber(char *str);

#endif