/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:39:44 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/04 14:57:46 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

void	find_z_max_min_val(t_data *data, t_vue *new)
{
	int	i;
	int	j;
	int	min;
	int	max;

	min = data->map[0][1].z;
	max = data->map[0][1].z;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (min > data->map[i][j].z)
				min = data->map[i][j].z;
			if (max < data->map[i][j].z)
				max = data->map[i][j].z;
			j++;
		}
		i++;
	}
	new->z_max = max;
	new->z_min = min;
}

int     get_color(int z, t_vue *new)
{
	double	percent;
	double	threshold;

	threshold = new->z_max - new->z_min;
	if (threshold == 0)
		return (0x432371);
	percent = (double)((z - new->z_min)) / threshold;
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

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	flag;

	nb = 0;
	flag = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10;
		nb = nb + (*str - '0');
		str++;
	}
	return (nb * flag);
}