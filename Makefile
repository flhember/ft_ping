
NAME = ft_ping
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

#-----------------------------------------SRC/INC-------------------------------#

PING_FILES	= main ping
INC_FILES	= ft_ping.h
LIB_BIN		= libft.a

#---------------------------------------PATH/FILES-------------------------------#

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/
LIB_PATH = ./libft/

SRC_FILES = $(PING_FILES:%=%.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

LIB_SRC = $(addprefix $(LIB_PATH), $(SRC_PATH))
OBJ_LIB = $(LIB_SRC:.c=.o)
LIB_INC = $(addprefix $(LIB_PATH), $(INC_PATH))

INC = $(addprefix $(INC_PATH), $(INC_FILES))
OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))
LIB = $(addprefix $(LIB_PATH), $(LIB_BIN))

#------------------------------------------RULES--------------------------------#


all: $(NAME)

lib: $(LIB)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c -I $(INC_PATH) -I $(LIB) $< -o $@
	@echo -e "Compilation of $(whi)$(notdir $<)$(grn_da) done.$(end)"

$(LIB):
	@make -sC $(LIB_PATH)

$(NAME): $(INC) $(LIB) $(OBJ_PATH) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -I $(INC_PATH)
	@echo -e "$(grn_li)$(notdir $(NAME))$(grn_da) created.$(end)"

clean:
	@$(RM) -R $(OBJ_PATH)
	@make clean -sC $(LIB_PATH)
	@echo -e "$(red_li)Objects files of $(notdir $(NAME))$(red_da) removed.$(end)"

fclean: clean
	@$(RM) -R $(NAME)
	@make fclean -sC $(LIB_PATH)
	@echo -e "$(red_li)$(notdir $(NAME))$(red_da) removed.$(end)"

re: fclean
	@make all -s

.PHONY: clean, fclean, all, re, lib
