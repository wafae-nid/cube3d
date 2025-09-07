# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/06 19:27:01 by wnid-hsa          #+#    #+#              #
#    Updated: 2025/09/07 02:56:19 by wnid-hsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC = cc
# CFLAGS = -Wall -Wextra -Werror 
# NAME = cub
# SRCS = get_next_line.c get_next_line_utils.c cleaning.c main.c \

# HDRS = cub3d.h
# OBJS = $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJS)
	
# %.o: %.c $(HDRS)
# 	$(CC) $(CFLAGS) -c $< -o $@
# 	ar -rc $(NAME) $@

# clean:
# 	rm -f $(OBJS)
# 	rm -f $(BONUS_OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub

SRCS = get_next_line.c get_next_line_utils.c cleaning.c main.c custom_func.c 
HDRS = cub3d.h
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
