NAME = philo_bonus
CC = gcc
CFLAGS = -g3 -Wall -Werror -Wextra -pthread -I inc
SRC_DIR = src/
OBJ_DIR = obj/
SRC = main_bonus.c init_bonus.c exit_bonus.c utils_bonus.c routine_bonus.c 
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

#Rules

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
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
