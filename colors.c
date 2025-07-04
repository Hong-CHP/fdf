/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:30:54 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/05 14:13:21 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

int	get_r(int h_color)
{
	return ((h_color >> 16) & 0xFF);
}

int	get_g(int h_color)
{
	return ((h_color >> 8) & 0xFF);
}

int	get_b(int h_color)
{
	return (h_color & 0xFF);
}

int	ft_gradient(int s_color, int e_color, double percent)
{
	int a;
	int	r;
	int	g;
	int	b;

	r = (int)round((1 - percent) * get_r(s_color) + percent * get_r(e_color));
	g = (int)round((1 - percent) * get_g(s_color) + percent * get_g(e_color));
	b = (int)round((1 - percent) * get_b(s_color) + percent * get_b(e_color));
	a = e_color & (0xFF << 24);
	return (a << 24 | r << 16 | g << 8 | b);
}

int     get_color(t_point *point, t_vue *new)
{
	double	percent;
	double	threshold;
	
	if (point->color)
        return (point->color);
	threshold = new->z_max - new->z_min;
	if (threshold == 0)
		return (0x432371);
	percent = (double)((point->z - new->z_min)) / threshold;
    if (percent <= 0.2)
        return (0x0000FF);
    else if (percent <= 0.4)
        return (0x00FF00);
    else if (percent <= 0.6)
        return (0x00FFFF);
    else if (percent <= 0.8)
        return (0xFFFF00);   
    else
        return (0xFFFFFF);
}

int	parse_color(char *str)
{
	int	res;
	int	value;
	int	i;
	
	res = 0;
	i = 0;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = str[i] - 'A' + 10;
		else
			break;
		res = res * 16 + value;
		i++;
	}
	return (res);
}

void	if_color(t_point *point, char *str)
{
	int	i;
	char	*s_color;
	
	if (!str)
		return ;
    point->color = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			s_color = &str[i + 1];
			point->color = parse_color(s_color);
		}
		i++;
	}
}