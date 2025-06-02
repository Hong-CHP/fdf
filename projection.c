/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:38:45 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/02 17:27:16 by hporta-c         ###   ########.fr       */
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
	new->zoom = ft_min((WIN_HEIGHT / h) / 2, (WIN_WIDTH / w) / 2);
	new->offset_x = (WIN_WIDTH - w * new->zoom) / 2;
	new->offset_y = (WIN_HEIGHT - h * new->zoom) / 2;
	point->screen_x = (point->x - point->y) * cos(new->radian);
	point->screen_x = point->screen_x * new->zoom + new->offset_x;
	point->screen_y = ((point->x + point->y) * sin(new->radian) - point->z);
	point->screen_y = point->screen_y * new->zoom + new->offset_y;
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
			// printf("screen x is %f and screen y is %f\n", map[row][col].screen_x, map[row][col].screen_y);
			col++;
		}
		row++;
	}
}