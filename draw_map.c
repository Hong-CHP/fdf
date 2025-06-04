/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:14:18 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/04 18:04:23 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= 1000 || y < 0 || y >= 800)
        return;

    dst = data->add + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void    high_slope(t_data *data, t_point s, t_point e, int color)
{
    int err;
    int dx;
    int dy;
    int sx;
    int sy;
    
    dx = ft_abs(e.res_x - s.res_x);
    dy = ft_abs(e.res_y - s.res_y);
    sx = (e.res_x - s.res_x > 0 ) ? 1 : -1;
    sy = (e.res_y - s.res_y > 0 ) ? 1 : -1;
    err = 0;
    while (s.res_y != e.res_y)
    {
        put_pixel(data, s.res_x, s.res_y, color);
        err += dx;
        if (2 * err >= dy)
        {
            s.res_x += sx;
            err -= dy;
        }
        s.res_y += sy;
    }
    put_pixel(data, s.res_x, s.res_y, color);
}

void    low_slope(t_data *data, t_point s, t_point e, int color)
{
    int err;
    int dx;
    int dy;
    int sx;
    int sy;

    dx = ft_abs(e.res_x - s.res_x);
    dy = ft_abs(e.res_y - s.res_y);
    sx = (e.res_x - s.res_x > 0 ) ? 1 : -1;
    sy = (e.res_y - s.res_y > 0 ) ? 1 : -1;
    err = 0;
    while (s.res_x != e.res_x) 
    {
        put_pixel(data, s.res_x, s.res_y, color);
        err += dy;
        if (2 * err >= dx)
        {
            s.res_y += sy;
            err -= dx;
        }
        s.res_x += sx;
    }
    put_pixel(data, s.res_x, s.res_y, color);
}

void    draw_line_bresenham(t_data *data, t_point *s, t_point *e)
{
    int color;
    
    color = get_color(s->z, &(data->new));
    if (ft_abs(e->res_y - s->res_y) == 0
        && ft_abs(e->res_x - s->res_x) == 0)
    {
        put_pixel(data, s->res_x, s->res_y, color);
        return ;
    }
    if(ft_abs(e->res_y - s->res_y) <= ft_abs(e->res_x - s->res_x))
        low_slope(data, *s, *e, color);
    else
        high_slope(data, *s, *e, color);
}

void    draw_map(t_data *data)
{
    int row;
    int col;
    
    // data->img = mlx_new_image(data->mlx, 1000, 800);
    // data->add = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
    row = 0;
    while (row < data->height)
    {
        col = 0;
        while (col < data->width)
        {
            if (col < data->width - 1)
                draw_line_bresenham(data, &(data->map[row][col]), &(data->map[row][col + 1]));
            if (row < data->height - 1)
                draw_line_bresenham(data, &(data->map[row][col]), &(data->map[row + 1][col]));
            col++;
        }
        row++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
