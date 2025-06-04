/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:40:42 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/04 17:57:04 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void    ft_bzero(void *s, size_t n)
{
    size_t  i;
    char    *p;

    p = (char *)s;
    i = 0;
    while (i < n)
    {
        p[i] = '\0';
        i++;
    }
    return ;
}

void    draw_bgc(t_data *data)
{
    int x;
    int y;

    ft_bzero(data->add, data->height * data->width * (data->bpp / 8));
    y = 0;
    while (y < WIN_H)
    {
        x = 0;
        while (x < WIN_W)
        {
            put_pixel(data, x, y, BGC_COLOR);
            x++;
        }
        y++;
    }
}