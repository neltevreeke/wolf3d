# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvisser <jvisser@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/22 13:27:36 by nvreeke        #+#    #+#                 #
#    Updated: 2019/04/16 13:27:36 by jvisser       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

BINARY = wolf3d
SRCS =	src/init.c \
		src/fps_meter.c \
		src/event_handlers.c \
		src/input.c \
		src/error.c \
		src/raycast.c
HEADER = src/wolf3d.h
OBJ = $(SRCS:%.c=%.o)
FLAGS = -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit -o $(BINARY)
ERRFLAGS = -Wall -Wextra -Werror
GCC = gcc
LIBS = ./libft/libft.a

all: $(BINARY)

%.o: %.c $(HEADER)
	@echo "\033[1;32m 🛠️  Building $@ from $< file \033[0m"
	@gcc $(ERRFLAGS) -c -o $@ $<

$(BINARY): $(OBJ)
	@echo "Compiling..."
	@make -C minilibx_macos re > /dev/null
	@make -C libft
	@$(GCC) $(SRCS) $(INC) -I/usr/X11/includes $(FLAGS) $(ERRFLAGS) $(LIBS)
	@echo "Done"

clean:
	@echo "Removing object files"
	@make -C minilibx_macos clean > /dev/null
	@make -C libft clean
	@rm -rf $(OBJ)
	@echo "Done"

fclean: clean
	@echo "Removing binary and extraneous directories"
	@make -C libft fclean
	@rm -rf .vscode
	@rm -rf minilibx_macos/.vscode
	@rm -rf $(BINARY)
	@echo "Done"

re: fclean all
