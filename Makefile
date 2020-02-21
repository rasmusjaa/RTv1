# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/16 14:55:48 by rjaakonm          #+#    #+#              #
#    Updated: 2020/02/21 18:13:01 by rjaakonm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRCS =	srcs/main.c \
		srcs/create_vector.c \
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
		srcs/keyboard.c \
		srcs/mouse.c \
		srcs/utilities.c \
		srcs/read_scene.c \
		srcs/color.c

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

LIB = -L libft -lft -lmlx -framework OpenGL -framework AppKit
# -L ./minilibx/

INCL = -I incl/ -I libft/libft/incl/ -I libft/printf/incl/

.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): libftmake
	gcc $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)

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
	gcc $(FLAGS) $(INCL) $(SRCS) $(LIB) -o $(NAME)
	./$(NAME) scene_1
