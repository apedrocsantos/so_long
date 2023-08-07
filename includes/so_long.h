/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:28:42 by anda-cun          #+#    #+#             */
/*   Updated: 2023/08/07 09:42:40 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>

typedef struct s_point
{
	int				y;
	int				x;
}					t_point;

typedef struct s_map
{
	void			*addr;
	char			**tab;
	int				collectibles;
	int				exits;
	int				players;
	int				checked;
	int				fd;
	t_point			size;
	t_point			start;
	t_point			exit_pos;
}					t_map;

typedef struct s_img
{
	void			*img_ptr;
	void			*addr;
	int				h;
	int				w;
	int				bpp;
	int				endian;
	int				sl;
	struct s_img	*next;
}					t_img;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				move_count;
	int				size;
	int				anim_speed;
	int				anim_counter;
	t_img			player;
	t_img			player_left;
	t_img			player_right;
	t_img			wall;
	t_img			floor;
	t_img			collectible;
	t_img			exit;
	t_img			enemy;
	t_img			enemy_reg;
	t_img			enemy_inv;
	t_map			map;
}					t_data;

void				free_map(t_map *map);
int					check_ber(char *str);
int					check_map(t_map *map);
int					read_map(t_map *map);
int					get_map(t_map *map);
int					parse_map(t_map *map, int i, int j);
int					check_chars(t_map *map);
void				get_start_pos_and_exit(t_map *map);
int					flood_fill(char **tab, t_map *map, t_point cur);
void				mega_free(t_data *data);
int					game_init(t_data *data);
int					handle_no_input(void *data);
int					close_window(t_data *data, char *error, int rtn);
int					key_func(int key, t_data *data);
void				*put_img(t_data *data);
void				error_end_program(t_data *data, char *msg, int rtn);
int					close_success(t_data *data);
void				get_img(t_data *data, t_img *img, char *str);
void				init_imgs(t_data *data);
void				draw_rectangle(t_data *data);
int					check_victory(void *new_data);
int					animate_sprites(t_data *data);
int					get_sprites(t_data *data);
void				get_img(t_data *data, t_img *img, char *str);
void				move_player(t_data *data, int x, int y);

#endif
