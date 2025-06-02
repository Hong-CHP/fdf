/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_pos_fill_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:35:54 by hporta-c          #+#    #+#             */
/*   Updated: 2025/06/02 10:09:19 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

void    free_split(char **str_split)
{
    int i;
    
    i = 0;
    while(str_split[i])
    {
        free(str_split[i]);
        i++;
    }
    free(str_split);
    str_split = NULL;
}

int	count_lines(char *file)
{
	char	*line;
	int		count;
	int		fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
    while (line)
    {
		count++;
        free(line);
        line = get_next_line(fd);
    }
	close(fd);
	return (count);
}

int	count_cols(char **line_split)
{
	int	count;

	count = 0;
	while (line_split[count])
		count++;
	return (count);
}

void	fill_map(t_point **map, char **line_split, int y, int *width)
{
	int i;
    
    map[y] = malloc(sizeof(t_point) * *width);
	if (!map[y])
		return ;
	i = 0;
	while (i < *width)
	{
		map[y][i].x = i;
		map[y][i].y = y;
		map[y][i].z = ft_atoi(line_split[i]);
		i++;
	}
}

t_point	**recup_points_data(int fd, int height, int *width)
{
	int	y;
	t_point **map;
	char	*line;
	char	**line_split;

	map = (t_point **)malloc(height * sizeof(t_point *));
	if (!map)
		return (NULL);
	y = 0;
	line = get_next_line(fd);
	while (line && y < height)
	{
		line_split = ft_split(line);
        *width = count_cols(line_split);
		fill_map(map, line_split, y, width);
        free_split(line_split);
		free(line);
        line = get_next_line(fd);
		y++;
	}
    // for (int j = 0; j < y; j++)
	// {
	// 	for (int i = 0; i < width; i++)
	// 		printf("(%d,%d,%d) ", map[j][i].x, map[j][i].y, map[j][i].z);
	// 	printf("\n");
	// }
	return (map);
}
