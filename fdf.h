/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:40 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/02 11:36:26 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	double screen_x;
	double screen_y;
}				t_point;

typedef struct s_vue
{
	int zoom;
	int offset_x;
	int offset_y;
	double radian;
}				t_vue;

int		ft_atoi(const char *str);
int		ft_min(int a, int b);
char	**ft_split(char	const *s);
int		count_lines(char *file);
t_point	**recup_points_data(int fd, int height, int *width);
void    projection_3d_to_screen(t_point **map, int height, int width);


#endif