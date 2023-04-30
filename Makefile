SRC_FILES	=	exit.c \
				main.c \
				math/clamp.c \
				math/mat3.c \
				math/vecmath.c \
				parse/data_types.c \
				parse/file.c \
				parse/obj.c \
				parse/obj2.c \
				parse/ranges.c \
				parse/ranges2.c \
				render/context.c \
				render/raycast.c \
				render/shading.c \
				render/render.c \
				util/atod.c \
				util/get_next_line/get_next_line.c \
				util/get_next_line/get_next_line_utils.c \
				util/intoa.c \
				util/mem.c \
				util/str.c \
				util/vec3.c \
				debug/debug.c \
				debug/alloc.c \

SRC_DIR		=	src

OBJ_DIR=obj
OBJ:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=miniRT

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -Isrc -Imlx/include -Ofast
LDFLAGS=-Lmlx
LDLIBS=-lmlx42 -framework OpenGL -framework AppKit -framework IOKit -lglfw3

all: mlx $(NAME)

bonus: all

mlx:
	@$(MAKE) -C mlx

noerr: CFLAGS:=$(subst -Werror,,$(CFLAGS))
noerr: all

sanit: CFLAGS+=-g -O0 -fsanitize=address
sanit: LDFLAGS+=-fsanitize=address
sanit: re

debug: CFLAGS+=-g -O0 -DDEBUG
debug: re

rel: CFLAGS+=-O2
rel: re

clean:
	@-rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d

fclean: clean
	@-rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME)

.PHONY: clean fclean re all mlx

-include $(OBJ:.o=.d)
