/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:57 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/03 17:53:40 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"
#include "mlx.h"

void	free_map(t_point **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void    ft_display_file(char *file, t_data *img_data)
{   
    int fd;
	t_point	**map;
	//malloc in func need to be free at last of program
	int	height;
	int	width;
	
	height = count_lines(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	map = recup_points_data(fd, height, &width);
	projection_3d_to_screen(map, height, width);
	draw_map(img_data, map, height, width);
	free_map(map, height);
    close(fd);
}

int main(int argc, char *argv[])
{
    char    *file;
	t_data	*img_data;

    if (argc != 2)
        return (1);
    file = argv[1];
	img_data = malloc(sizeof(t_data));
	if (!img_data)
		return (1);
	img_data->mlx = mlx_init();
    if (!img_data->mlx)
        return (1);
    img_data->win = mlx_new_window(img_data->mlx, 1000, 800, "fdf");
    if (!img_data->win)
	{
		mlx_destroy_display(img_data->mlx);
		free(img_data->mlx);
		free(img_data);
        return (1);
	}
	ft_display_file(file, img_data);
    mlx_loop(img_data->mlx);
	mlx_destroy_window(img_data->mlx, img_data->win);
    mlx_destroy_display(img_data->mlx);
    free(img_data->mlx);
	free(img_data);
    return (0);
}
