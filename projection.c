/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:38:45 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/03 19:15:36 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double  deg_to_rad(void)
{
    double pi;
    double degree;
    double  radian;

    pi = 3.14159265;
    degree = 30.0;
    radian = degree * (pi / 180.0);
    return (radian);
}

void	fill_new_screen_points(t_point *point, t_vue *new, int h, int w)
{	
	double	new_x;
	double	new_y;
	double	new_z;
	
	new->zoom = ft_min((1000 / h) / 2, (800 / w) / 2);
	new->offset_x = (1000 - w * new->zoom) / 2;
	new->offset_y = (800 - h * new->zoom) / 2;
	new_x = (point->x - point->y) * cos(new->radian);
	new_x = new_x * new->zoom + new->offset_x;
	new_z = point->z * 0.2;
	new_y = ((point->x + point->y) * sin(new->radian) - new_z);
	new_y = new_y * new->zoom + new->offset_y;
	point->screen_x = (int)round(new_x);
	point->screen_y = (int)round(new_y);
	point->z = (int)round(new_z);
}

void    projection_3d_to_screen(t_point **map, int height, int width)
{
    t_vue new;
	int	col;
    int row;

    new.radian = deg_to_rad();
    row = 0;
	while (row < height)
	{
		col = 0;
		while (col < width)
		{
			fill_new_screen_points(&map[row][col], &new, height, width);
			printf("screen x is %d and screen y is %d and point z is %d\n", map[row][col].screen_x, map[row][col].screen_y, map[row][col].z);
			col++;
		}
		row++;
	}
}