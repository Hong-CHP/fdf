# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hporta-c <hporta-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/28 14:53:49 by hporta-c          #+#    #+#              #
#    Updated: 2025/06/05 09:32:05 by hporta-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L. -lmlx -lXext -lX11 -lm
INCLUDES = -I.

SRCS = get_next_line.c get_next_line_utils.c ft_split.c projection.c \
		recup_pos_fill_map.c utils.c main.c draw_map.c ev_listener.c \
		mlx_utils.c colors.c
OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean all re