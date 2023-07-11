#ifndef SO_LONG_H
#define SO_LONG_H

typedef struct mlx
{
    void    *mlx_ptr;
    void    *mlx_window;
    int     width;
    int     height;
} mlx_t;

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


#endif