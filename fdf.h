/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:40 by hporta-c          #+#    #+#             */
/*   Updated: 2025/05/28 16:53:13 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct s_list
{
	t_point point;
	struct s_list *next;
}				t_list;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int color;
}				t_point;

#endif