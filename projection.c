/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:38:45 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/04 19:09:04 by hporta-c         ###   ########.fr       */
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

void	find_distance_vertices(t_data *data, t_vue *new)
{
	double	hor;
	t_point	b;
	t_point	d;

	b = data->map[0][data->width - 1];
	d = data->map[data->height - 1][data->width - 1];
	b.res_x = (b.x - b.y) * cos(new->radian) * new->zoom;
	b.res_y = ((b.x + b.y) * sin(new->radian) - b.z * 0.1) * new->zoom;
	d.res_x = (d.x - d.y) * cos(new->radian) * new->zoom;
	d.res_y = ((d.x + d.y) * sin(new->radian) - d.z * 0.1) * new->zoom;
	hor = sqrt((d.res_x - b.res_x) * (d.res_x - b.res_x) + (d.res_y - b.res_y) * (d.res_y - b.res_y));
	new->offset_y = (WIN_H - hor) / 2;
}

void	get_required_max_val(t_data *data, t_vue *new, double *min_x, double *max_x)
{
	int	col;
    int row;
	t_point	*p;
	
	row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			p = &(data->map[row][col]);
			p->res_x = (p->x - p->y) * cos(new->radian) * new->zoom;
			if (*min_x > p->res_x)
				*min_x = p->res_x;
			if (*max_x < p->res_x)
				*max_x = p->res_x;
			col++;
		}
		row++;
	}
	new->offset_x = (WIN_W - (*max_x - *min_x)) / 2 - *min_x;
}

void	fill_new_res_points(t_point *point, t_vue *new)
{	
	double	new_x;
	double	new_y;
	double	new_z;
	
	new_z = point->z * 0.1;
	new_x = (point->x - point->y) * cos(new->radian);
	new_x = new_x * new->zoom + new->offset_x;
	new_y = (point->x + point->y) * sin(new->radian) - new_z;
	new_y = new_y * new->zoom + new->offset_y;
	point->res_x = (int)round(new_x);
	point->res_y = (int)round(new_y);
}

t_vue    projection_3d_to_res(t_data *data)
{
    t_vue new;
	int	col;
    int row;
	double	min_x;
	double	max_x;

	min_x = INFINITY;
	max_x = -INFINITY;
    new.radian = deg_to_rad();
	find_z_max_min_val(data, &new);
	new.zoom = 0.9 * ft_min((WIN_W / data->width), (WIN_H / data->height)) / 2;
	get_required_max_val(data, &new, &min_x, &max_x);
	find_distance_vertices(data, &new);
    row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			fill_new_res_points(&(data->map[row][col]), &new);
			// printf("res x is %d and res y is %d and point z is %d\n", data->map[row][col].res_x, data->map[row][col].res_y, data->map[row][col].z);
			col++;
		}
		row++;
	}
	return (new);
}