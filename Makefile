# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/16 14:55:48 by rjaakonm          #+#    #+#              #
#    Updated: 2020/05/29 22:36:48 by rjaakonm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Use 42 configured Ubuntu on VirtualBox from image https://cdn.42.fr/english-version.ova
# or on fresh Ubuntu configure with:

# sudo apt update
# sudo apt-get upgrade
# sudo apt install build-essential
# sudo apt install git
# sudo apt-get install xorg openbox
# sudo apt-get install libxext-dev

# git clone https://github.com/42Paris/minilibx-linux.git
# go to minilibx folder and run ./configure and test binary to see it works
# while in minilibx folder:
# sudo cp libmlx.a /usr/local/lib
# sudo cp mlx.h /usr/local/include
# sudo mkdir /usr/local/man/man3
# sudo cp man/man3/mlx*.1 /usr/local/man/man3

NAME = RTv1

SRCS =	srcs/create_vector.c \
		srcs/direction_vectors.c \
		srcs/dot_cross_vectors.c \
		srcs/double_sqr.c \
		srcs/nb_vector_operators.c \
		srcs/normalize_vector.c \
		srcs/two_vector_operators.c \
		srcs/vector_length.c \
		srcs/vector_sqr.c \
		srcs/vector_sqrt.c \
		srcs/draw.c \
		srcs/intersections.c \
		srcs/rays.c \
		srcs/shape_plane.c \
		srcs/shape_sphere.c \
		srcs/shape_cylinder.c \
		srcs/shape_cone.c \
		srcs/camera.c \
		srcs/mouse.c \
		srcs/utilities.c \
		srcs/utilities_2.c \
		srcs/read_scene.c \
		srcs/color.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

INCL = -I incl/ -I libft/libft/incl/ -I libft/printf/incl/

# Works on configured Ubuntu and MacOS
# chooses LIB automatically based on system
# Choose different c files on Linux to get different mlx_hooks and controls
# Xevents and event masks found on X11 x.h, like here https://code.woboq.org/qt5/include/X11/X.h.html
UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux) # On Linux
		SYSTEMBASEDSOURCE = srcs/main_linux.c srcs/keyboard_linux.c
        LIB = -L libft -lft -lmlx -lm -lXext -lX11 -pthread
    endif
    ifeq ($(UNAME_S),Darwin) # On MacOS
		SYSTEMBASEDSOURCE = srcs/main.c srcs/keyboard.c
        LIB = -L libft -lft -lmlx -framework OpenGL -framework AppKit
    endif

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): libftmake
	@echo "Using $(UNAME_S) Library"
	gcc $(FLAGS) $(INCL) $(SRCS) $(SYSTEMBASEDSOURCE) $(LIB) -o $(NAME) -O2


libftmake:
	@make -C libft

clean:
#	@rm -f $(notdir $(OBJS))
#	@rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

run:
	gcc $(FLAGS) $(INCL) $(SRCS) $(SYSTEMBASEDSOURCE) $(LIB) -o $(NAME) -O2
	./$(NAME) scene_1
