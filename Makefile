LIB_INCLUDE = include
PATH_PREFIX = test

NAME = test.out

PATH_OBJ = $(PATH_PREFIX)/obj
PATH_SRC = $(PATH_PREFIX)/src

SRC_BASENAME =	priority_queue.c \
				vector.c

SRC = $(addprefix $(PATH_SRC)/, $(SRC_BASENAME))
OBJ = $(addprefix $(PATH_OBJ)/, $(SRC_BASENAME:.c=.o))
DEP = $(addprefix $(PATH_OBJ)/, $(SRC_BASENAME:.c=.d))

ECHO = /bin/echo -e
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(LIB_INCLUDE) -g3 -ggdb -std=c2x
LDFLAGS = -lcriterion

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@$(ECHO) "\e[1;38;5;182m >> Compiling "$<"...\e[0m"
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -MMD $< -o $@

-include $(DEP)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	@rm -f $(OBJ) $(DEP)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re