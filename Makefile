# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvisser <jvisser@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/02/22 13:27:36 by nvreeke        #+#    #+#                 #
#    Updated: 2019/05/23 20:03:19 by jvisser       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

BINARY = wolf3d
SRCS =	src/init.c \
		src/input.c \
		src/error.c \
		src/program_loops.c \
		\
		src/sounds.c \
		src/fps_meter.c \
		\
		src/load_game.c \
		src/save_game.c \
		src/game_state.c \
		src/player_interaction.c \
		\
		src/move.c \
		src/screen.c \
		\
		src/mouse.c \
		src/keyboard.c \
		\
		src/map.c \
		src/minimap.c \
		\
		src/player.c \
		src/interface.c \
		\
		src/sprites.c \
		src/textures.c \
		\
		src/raycast.c \
		src/print_sprites.c \
		src/print_raycast.c \
		src/calc_print_sprites.c \
		src/calc_print_raycast.c
HEADER = includes/bool.h \
		includes/error.h \
		includes/game_states.h \
		includes/keys.h \
		includes/map.h \
		includes/menu.h \
		includes/minimap.h \
		includes/mouse.h \
		includes/player.h \
		includes/program_loops.h \
		includes/raycast.h \
		includes/screen.h \
		includes/sound.h \
		includes/sprites.h \
		includes/textures.h \
		includes/ui.h \
		includes/xlm.h
OBJ = $(SRCS:%.c=%.o)
FLAGS = -L minilibx_macos/ -lmlx -framework OpenGL -framework AppKit -o $(BINARY)
ERRFLAGS = -Wall -Wextra -Werror -O3
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
