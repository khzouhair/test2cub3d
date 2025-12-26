NAME := ./a.out

CC := cc

CFLAGS := -g -w -Wall -Wextra -Werror -Ofast -O3 -g -fsanitize=address

SRC := init_cub3d.c main.c parser_mocking.c dda.c update_data.c cleaning.c \
		./parsinggggg/parsing/get_next_line.c \
		./parsinggggg/parsing/atoi.c ./parsinggggg/parsing/ft_split.c \
		./parsinggggg/parsing/map.c  ./parsinggggg/parsing/parsing.c \
		./parsinggggg/parsing/get_next_line_utils.c \
		./parsinggggg/parsing/pars_map.c \
		./parsinggggg/parsing/tools.c \
		./parsinggggg/parsing/tools2.c \
		./parsinggggg/textures/textures.c ./parsinggggg/free.c
LIB_DIR := mlx
LIBRARY := -L$(LIB_DIR) -lmlx -lXext -lX11 -lm -lz
HEADER := cub3d.h

all: $(NAME)

$(NAME): $(LIB_DIR)/libmlx.a $(SRC) $(HEADER)
	$(CC) $(CFLAGS) $(SRC) $(LIBRARY) -o $(NAME)

$(LIB_DIR)/libmlx.a:
	@$(MAKE) -C $(LIB_DIR)

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf $(LIB_DIR)/*.o $(LIB_DIR)/libmlx.a

re: fclean all
