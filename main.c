/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:54:57 by hporta-c          #+#    #+#             */
/*   Updated: 2025/05/28 16:44:32 by hporta-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "fdf.h"

void    ft_display_file(char *file)
{   
    int fd;
	int buffer_size;
	char *line;
	
	buffer_size = 5;
    fd = open(file, O_RDONLY);
    line = get_next_line(fd, buffer_size);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd, buffer_size);
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    char    *file;
	t_point		**map;
	
    if (argc != 2)
        return (1);
    file = argv[1];
    ft_display_file(file);
    return (0);
}