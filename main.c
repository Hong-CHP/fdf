/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:57 by hporta-c          #+#    #+#             */
/*   Updated: 2025/05/29 12:15:00 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

int	count_lines(char *file)
{
	char	*line;
	int		count;
	int		fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
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

void	fill_map(t_point *row, char **line_split, int y)
{
	int	i;
	
	i = 0;
	while (line_split[i])
	{
		row[i].x = i;
		row[i].y = y;
		row[i].z = ft_atoi(line_split[i]);
		i++;
	}
	free(line_split);
}

t_point	**recup_points_data(int fd, int height)
{
	int	y;
	t_point **map;
	char	*line;
	char	**line_split;
	
	map = (t_point **)malloc(height * sizeof(t_point *));
	if (!map)
		return ;
	y = 0;
	line = get_next_line(fd);
	while (line && y < height)
	{
		line_split = ft_split(line);
		map[y] = malloc(sizeof(t_point) * count_cols(line_split));
		if (!map[y])
			return (NULL);
		fill_map(map[y], line_split, y);
		free(line);
        line = get_next_line(fd);
		y++;
	}
	return (map);
}

void    ft_display_file(char *file)
{   
    int fd;
	t_point	**map;
	int	height;
	
	height = count_lines(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	map = recup_points_data(fd, height);
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