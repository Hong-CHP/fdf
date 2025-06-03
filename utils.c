/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:39:44 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/03 17:17:04 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

int     get_color(int z)
{
    if (z < 0)
        return (0x0000FF);
    else if (z <= 20)
        return (0x00FF00);
    else if (z <= 50)
        return (0x00FFFF);
    else if (z <= 100)
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