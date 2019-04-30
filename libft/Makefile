# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvisser <jvisser@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/12 12:07:57 by jvisser        #+#    #+#                 #
#    Updated: 2019/04/30 18:27:31 by jvisser       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -O3
HEADER = libft.h ft_printf/ft_printf.h
C_FILES =	ft_memalloc.c\
			ft_memdel.c\
			ft_bzero.c\
			ft_memset.c\
			ft_memcpy.c\
			ft_memccpy.c\
			ft_memmove.c\
			\
			ft_memchr.c\
			ft_memcmp.c\
			\
			ft_wclen.c\
			ft_strlen.c\
			ft_strlench.c\
			ft_wstrbytes.c\
			ft_wordcount.c\
			\
			get_next_line.c\
			ft_strnew.c\
			ft_strclr.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_wstrdup.c\
			ft_strcpy.c\
			ft_strncpy.c\
			ft_strcat.c\
			ft_strncat.c\
			ft_strlcat.c\
			ft_strtrim.c\
			ft_strsplit.c\
			ft_strjoin.c\
			ft_strsub.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_formatwchar.c\
			\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strchri.c\
			ft_strstr.c\
			ft_strnstr.c\
			ft_strcmp.c\
			ft_strncmp.c\
			ft_strequ.c\
			ft_strnequ.c\
			\
			ft_toupper.c\
			ft_tolower.c\
			\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isblank.c\
			ft_iscntrl.c\
			ft_isdigit.c\
			ft_isgraph.c\
			ft_islower.c\
			ft_isprint.c\
			ft_ispunct.c\
			ft_isspace.c\
			ft_isupper.c\
			ft_isxdigit.c\
			\
			ft_atoi.c\
			ft_itoa.c\
			ft_itoa_base.c\
			ft_lltoa.c\
			ft_ulltoa_base.c\
			ft_cap_lftoa.c\
			ft_cap_lftoa2.c\
			\
			ft_putchar.c\
			ft_putchar_fd.c\
			ft_putwchar.c\
			ft_putcharn.c\
			ft_putstr.c\
			ft_putstrn.c\
			ft_putstrch.c\
			ft_putstr_fd.c\
			ft_putendl.c\
			ft_putendl_fd.c\
			ft_putnbr.c\
			ft_putnbr_fd.c\
			\
			ft_lstnew.c\
			ft_lstadd.c\
			ft_lstaddend.c\
			ft_lstnadd.c\
			ft_lstdel.c\
			ft_lstdelone.c\
			ft_lstmap.c\
			ft_lstiter.c\
			\
			ft_abs.c\
			ft_labs.c\
			ft_factorial.c\
			ft_sqrt.c\
			ft_cubed.c\
			ft_powerof.c\
			\
			ft_printf/ft_printf.c\
			ft_printf/parse.c\
			ft_printf/parse_utils.c\
			ft_printf/utils.c\
			ft_printf/print.c\
			ft_printf/print_num.c\
			ft_printf/is_utf8.c\
			ft_printf/is_utf8_3b.c\
			ft_printf/is_utf8_4b.c\
			ft_printf/print_txt.c\
			ft_printf/print_base.c\
			ft_printf/print_decimal.c\
			ft_printf/print_wide.c\
			ft_printf/print_utils.c\
			ft_printf/print_utils2.c\
			ft_printf/validate.c\
			ft_printf/colors.c\
			ft_printf/cast.c
O_FILES =	$(C_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	@echo "\033[1;32m 🛠️  Building $@ from $< file \033[0m"
	@gcc $(FLAGS) -c -o $@ $<

$(NAME): $(O_FILES)
	@echo "\033[1;32m 🛠️  Building library from objects \033[0m"
	@ar rcs $(NAME) $(O_FILES)

clean:
ifeq (,$(wildcard $(O_FILES)))
	@echo "\033[1;31m 🗑️  No objects to clean \033[0m"
else
	@echo "\033[1;31m 🗑️  Cleaning library objects \033[0m"
	@/bin/rm -f $(O_FILES)
endif

fclean: clean
ifeq (,$(wildcard $(NAME)))
	@echo "\033[1;31m 🗑️  No library to clean \033[0m"
else
	@echo "\033[1;31m 🗑️  Cleaning libft.a file \033[0m"
	@/bin/rm -f $(NAME)
endif

re: fclean all
