# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flhember <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 18:09:39 by flhember          #+#    #+#              #
#    Updated: 2022/11/17 15:52:18 by flhember         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
#-------------------------------------COLOR VARIABLE----------------------------#

red_li=$ \033[1;31m
red_da=$ \033[0;31m
grn_li=$ \033[1;32m
grn_da=$ \033[0;32m
yel=$ \033[1;33m
blu=$ \033[1;34m
mag=$ \033[1;35m
cyn=$ \033[1;36m
whi=$ \033[1;37m
end=$ \033[0m

#-------------------------------SRC/INC--------------------------------------------

LIBFT=  ft_strlen ft_strcpy ft_strdup ft_strncpy ft_strcat ft_strncat ft_strlcat  		\
		ft_putchar ft_putstr ft_strchr ft_strrchr ft_strstr ft_strnstr ft_strcmp  		\
		ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint 		\
		ft_toupper ft_tolower ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove  		\
		ft_memchr ft_memcmp ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr   		\
		ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ ft_swap  		\
 		ft_strsub ft_strjoin ft_strtrim ft_putendl ft_putnbr ft_putnbr_fd ft_itoa 		\
 		ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_strsplit ft_lstnew ft_lstdel  		\
 		get_next_line ft_lstdelone ft_lstadd ft_lstiter ft_lstmap ft_print_list   		\
		ft_str_is_lowercase ft_str_is_uppercase ft_strjoinfree ft_get_fd 		\
		ft_free_tab_char ft_count_c ft_is_c ft_strisalpha ft_strnalpha	\
		ft_strnlen ft_strncut

INC		= libft.h
SRC_FILES	= $(LIBFT:%=%.c)

#-------------------------PATH/OBJ/DEP---------------------------------------------

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
INC_PATH = ./includes/

INC_FILES = $(addprefix $(INC_PATH), $(INC))
OBJ_FILES = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))
DEPS=$(OBJ_FILES:%.o=%.d)

#---------------------------RULE----------------------------------------------------

.PHONY: all, clean, fclean, re

all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_FILES): $(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c -I $(INC_PATH) $< -o $@
	@echo "Compilation of $(whi)$(notdir $<)$(grn_da) done.$(end)"

$(NAME): $(INC_FILES) $(OBJ_PATH) $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "$(grn_li)$(notdir $(NAME))$(grn_da) done.$(end)"

clean:
	@$(RM) -R $(OBJ_PATH) $(DEPS)
	@echo "$(red_li)Objects files of $(notdir $(NAME))$(red_da) removed.$(end)"

fclean: clean
	@$(RM) -R $(NAME)
	@echo "$(red_li)$(notdir $(NAME))$(red_da) removed.$(end)"

re: fclean
	@make all
