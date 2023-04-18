SRC_FILES	=	main.c \
				render/context.c \
				render/raycast.c \
				util/vec3.c \
				util/mem.c \
				math/vecmath.c \
				exit.c

SRC_DIR		=	src

OBJ_DIR=obj
OBJ:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=miniRT

CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic -Werror -Isrc -Imlx/include
LDFLAGS=-Lmlx
LDLIBS=-lmlx42 -framework OpenGL -framework AppKit -framework IOKit -lglfw3

all: mlx $(NAME)

bonus: all

noerr: CCFLAGS:=$(subst -Werror,,$(CCFLAGS))
noerr: all

sanit: CCFLAGS+=-g -O0 -fsanitize=address
sanit: LDFLAGS+=-fsanitize=address
sanit: re

debug: CCFLAGS+=-g -O0
debug: re

rel: CCFLAGS+=-O2
rel: re

clean:
	@-rm -rf $(OBJ)

fclean: clean
	@-rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME)

.PHONY: clean fclean re all mlx

-include $(OBJ:.o=.d)
