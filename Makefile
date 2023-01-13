
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
whi=$ \033[1;37m
end=$ \033[0m

#-----------------------------------------SRC/INC-------------------------------#

PING_FILES	= main ping tool socket
INC_FILES	= ft_ping.h

#---------------------------------------PATH/FILES-------------------------------#

SRC_PATH = ./srcs/
INC_PATH = ./includes/
OBJ_PATH = ./obj/

SRC_FILES = $(PING_FILES:%=%.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

INC = $(addprefix $(INC_PATH), $(INC_FILES))
OBJ = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_FILES))

#------------------------------------------RULES--------------------------------#


all: $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c -I $(INC_PATH) $< -o $@
	@echo -e "Compilation of $(whi)$(notdir $<)$(grn_da) done.$(end)"

$(NAME): $(INC) $(OBJ_PATH) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I $(INC_PATH)
	@echo -e "$(grn_li)$(notdir $(NAME))$(grn_da) created.$(end)"

clean:
	@$(RM) -R $(OBJ_PATH)
	@echo -e "$(red_li)Objects files of $(notdir $(NAME))$(red_da) removed.$(end)"

fclean: clean
	@$(RM) -R $(NAME)
	@echo -e "$(red_li)$(notdir $(NAME))$(red_da) removed.$(end)"

re: fclean
	@make all -s

.PHONY: clean, fclean, all, re