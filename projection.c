/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:38:45 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/05 17:16:30 by hporta-c         ###   ########.fr       */
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

void	fill_new_res_points(t_point *point, t_vue *new, t_data *data)
{	
	double	new_x;
	double	new_y;
	double	new_z;
	int	z_range;
	double	z_scale;

	z_range = new->z_max - new->z_min;
	z_scale = (data->width + data->height) * sin(new->radian) / (double)z_range * 0.2;
	new_z = point->z * z_scale;
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
	new.zoom = 0.9 * ft_min((WIN_W / data->width), (WIN_H / data->height)) / 2;
	find_z_max_min_val(data, &new);
	get_required_max_val(data, &new, &min_x, &max_x);
	find_distance_vertices(data, &new);
    row = 0;
	while (row < data->height)
	{
		col = 0;
		while (col < data->width)
		{
			fill_new_res_points(&(data->map[row][col]), &new, data);
			col++;
		}
		row++;
	}
	return (new);
}

// void	zoom_original_map(t_data *data, t_point *point, t_vue *new)
// {
// 	int	scale;
// 	double	z_scale;
// 	int	z_range;

// 	z_range = new->z_max - new->z_min;
// 	scale =  0.9 * ft_min((WIN_W / data->width), (WIN_H / data->height)) / 2;
// 	z_scale = (data->width + data->height) * sin(new->radian) / (double)z_range * 0.2;
// 	printf("z_scale is %f\n", (data->width + data->height) * sin(new->radian));
// 	point->res_x = point->x * scale;
// 	point->res_y = point->y * scale;
// 	point->res_z = point->z * point->z * z_scale;
// }

// void 	isometric_project_algo(t_point *point, t_vue *new)
// {
// 	double	new_x;
// 	double	new_y;
	
// 	new_x = (point->res_x - point->res_y) * cos(new->radian);
// 	new_y = (point->res_x + point->res_y) * sin(new->radian) - point->res_z;
// 	printf("x_iso, y_iso, z_iso are (%f, %f, %d)\n", new_x, new_y, point->res_z);
// 	new_x += new->offset_x;
// 	new_y += new->offset_y;
// 	point->res_x = (int)round(new_x);
// 	point->res_y = (int)round(new_y);
// }


// t_vue	isometric_project(t_data *data)
// {
// 	int	col;
// 	int	row;
// 	t_vue	new;
// 	double	min_x;
// 	double	max_x;

// 	min_x = INFINITY;
// 	max_x = -INFINITY;
// 	new.radian = deg_to_rad();
// 	find_z_max_min_val(data, &new);
// 	get_required_max_val(data, &new, &min_x, &max_x);
// 	find_distance_vertices(data, &new);
// 	row = 0;
// 	while (row < data->height)
// 	{
// 		col = 0;
// 		while (col < data->width)
// 		{
// 			printf("x_init, y_init, z_init are (%d, %d, %d)\n", data->map[row][col].x, data->map[row][col].y, data->map[row][col].z);
// 			zoom_original_map(data, &(data->map[row][col]), &new);
// 			printf("x_scale, y_scale, z_scale are (%d, %d, %d)\n", data->map[row][col].res_x, data->map[row][col].res_y, data->map[row][col].res_z);
// 			isometric_project_algo(&(data->map[row][col]), &new);
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (new);
// }