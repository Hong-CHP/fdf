/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:14:18 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/02 17:14:48 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void    draw_img(t_data *data)
{
    data->img = mlx_new_image(data->mlx, 1000, 800);
    data->add = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
    
}
