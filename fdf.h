/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:40 by hporta-c          #+#    #+#             */
/*   Updated: 2025/05/30 09:41:24 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int color;
}				t_point;

int		ft_atoi(const char *str);
char	**ft_split(char	const *s);
int		count_lines(char *file);
t_point	**recup_points_data(int fd, int height);


#endif