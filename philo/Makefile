NAME = philo
CC = gcc
CFLAGS = -g3 -Wall -Werror -Wextra -pthread -I inc $(SANITIZE)
SRC_DIR = src/
OBJ_DIR = obj/
SRC = main.c init.c exit.c utils.c routine.c threads.c
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

SANITIZE = 
#memory leaks and buffer overflows:		make SANITIZE="-fsanitize=address"
#race conditions and deadlocks:			make SANITIZE="-fsanitize=thread"

#Rules

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "Philosophers compiled successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed!"

re: fclean all
	@echo "Recompiled everithing!"

.PHONY: all clean fclean re
