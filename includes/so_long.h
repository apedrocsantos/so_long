#ifndef SO_LONG_H

# define SO_LONG_H
# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500

// #define WINDOW_WIDTH 1920
// #define WINDOW_HEIGHT 1080 - 35 - 50

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>

# define MAP_ERRORS ((char const *[]){"", "No valid path in map.\n", "Invalid char.\n", "Invalid borders.\n", "Too many players, exits or not enough collectibles.\n", " Error reading map.\n ", "Map is not a rectangle.\n", "Invalid file.\n"})

typedef struct s_img
{
	void	*img_ptr;
	void 	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		sl;
}			t_img;

typedef struct s_point
{
	int		y;
	int		x;
}			t_point;

typedef struct s_map
{
	void	*addr;
	char	**tab;
	int		collectibles;
	int		exits;
	int		players;
	int		checked;
	t_point	size;
	t_point	start;
}			t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		move_count;
	t_img	player;
	t_img	wall;
	t_img	floor;
	t_img	collectible;
	t_img	exit;
	t_map	map;
}			t_data;

void		free_map(t_map *map);
int			check_ber(char *str);
int			check_map(char *str, t_map *map);
int	read_map(char *str, t_map *map);
int	get_map(char *str, t_map *map);
int	parse_map(t_map *map);
int	check_chars(t_map *map);
void	get_start_pos(t_map *map);
int	flood_fill(char **tab, t_map *map, t_point cur);
void	mega_free(t_data *data);
int game_init (t_data *data);
int	handle_no_input(void *data);
int	close_window(t_data *data);
int	key_func(int key, t_data *data);
void	*put_img(t_data *data);
int error_end_program(t_data *data, char *msg, int rtn);

#endif
