/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:40 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/04 18:14:05 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# include <math.h>

# define WIN_W 1000
# define WIN_H 800
# define BGC_COLOR 0x1A1A1D

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int res_x;
	int res_y;
}				t_point;

typedef struct s_vue
{
	double zoom;
	int offset_x;
	int offset_y;
	int	z_max;
	int	z_min;
	double radian;
}				t_vue;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*add;
	int		bpp;
	int		line_len;
	int		endian;
	t_point **map;
	int		height;
	int		width;
	t_vue	new;
}				t_data;

int		ft_atoi(const char *str);
int		ft_min(int a, int b);
int		ft_abs(int nb);
int     get_color(int z, t_vue *new);
char	**ft_split(char	const *s);
int		count_lines(char *file);
t_point	**recup_points_data(int fd, t_data *data);
void	find_z_max_min_val(t_data *data, t_vue *new);
t_vue    projection_3d_to_res(t_data *data);
void put_pixel(t_data *data, int x, int y, int color);
void    draw_bgc(t_data *data);
void    draw_map(t_data *data);
void    add_event_listener(t_data *img_data);
void	clean_all(t_data *data);

#endif