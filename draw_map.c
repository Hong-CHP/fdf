/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:14:18 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/05 13:54:55 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return;
    dst = data->add + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

// int    get_palette(int s_color, int e_color, int step, int total)
// {
//     double percent;

//     percent = (total == 0) ? 0.0 : (double)step / (double)total;
//     return (ft_gradient(s_color, e_color, percent));
// }

void    high_slope(t_data *data, t_point s, t_point e, int color)
{
    int err;
    int dx;
    int dy;
    int sx;
    int sy;
    int i;
    double percent;
    
    dx = ft_abs(e.res_x - s.res_x);
    dy = ft_abs(e.res_y - s.res_y);
    sx = (e.res_x - s.res_x > 0 ) ? 1 : -1;
    sy = (e.res_y - s.res_y > 0 ) ? 1 : -1;
    err = 0;
    s.color = get_color(&s, &data->new);
    e.color = get_color(&e, &data->new);
    i = 0;
    while (s.res_y != e.res_y)
    {
        percent = (dy == 0) ? 0.0 : (double)i / (double)dy;
        color = ft_gradient(s.color, e.color, percent);
        // get_palette(s.color, e.color, i, dy);
        put_pixel(data, s.res_x, s.res_y, color);
        err += dx;
        if (2 * err >= dy)
        {
            s.res_x += sx;
            err -= dy;
        }
        s.res_y += sy;
        i++;
    }
    put_pixel(data, s.res_x, s.res_y, e.color);
}

void    low_slope(t_data *data, t_point s, t_point e, int color)
{
    int err;
    int dx;
    int dy;
    int sx;
    int sy;
    int i;
    double percent;
    
    dx = ft_abs(e.res_x - s.res_x);
    dy = ft_abs(e.res_y - s.res_y);
    sx = (e.res_x - s.res_x > 0 ) ? 1 : -1;
    sy = (e.res_y - s.res_y > 0 ) ? 1 : -1;
    err = 0;
    s.color = get_color(&s, &data->new);
    e.color = get_color(&e, &data->new);
    i = 0;
    while (s.res_x != e.res_x) 
    {
        percent = (dx == 0) ? 0.0 : (double)i / (double)dx;
        color = ft_gradient(s.color, e.color, percent);
        put_pixel(data, s.res_x, s.res_y, color);
        err += dy;
        if (2 * err >= dx)
        {
            s.res_y += sy;
            err -= dx;
        }
        s.res_x += sx;
        i++;
    }
    put_pixel(data, s.res_x, s.res_y, e.color);
}

void    draw_line_bresenham(t_data *data, t_point *s, t_point *e)
{
    int color;
    
    color = get_color(s, &(data->new));
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
