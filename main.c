/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:57 by hporta-c          #+#    #+#             */
/*   Updated: 2025/05/30 11:03:13 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

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

void    ft_display_file(char *file)
{   
    int fd;
	t_point	**map;
	//malloc in func need to be free at last of program
	int	height;
	
	height = count_lines(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	map = recup_points_data(fd, height);
	free_map(map, height);
    close(fd);
}

int main(int argc, char *argv[])
{
    char    *file;
	
    if (argc != 2)
        return (1);
    file = argv[1];
    ft_display_file(file);
    return (0);
}