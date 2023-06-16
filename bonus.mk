SRC_FILES	=	exit.c \
				bonus/main.c \
				math/clamp.c \
				math/mat3.c \
				math/vecmath.c \
				parse/data_types.c \
				parse/file.c \
				parse/obj.c \
				parse/obj2.c \
				parse/ranges.c \
				parse/ranges2.c \
				bonus/render/context.c \
				render/raycast.c \
				bonus/render/shading.c \
				bonus/render/render.c \
				bonus/render/bounce.c \
				bonus/render/thread.c \
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

OBJ_DIR=dobj
OBJ:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=miniRT

CC=gcc
CFLAGS=-Wall -Wpedantic -Werror -Isrc/bonus -Isrc -Imlx/include -O2
LDFLAGS=-Lmlx -O2
LDLIBS=-lmlx42 -framework OpenGL -framework AppKit -framework IOKit -lglfw3

all: mlx $(NAME)

mlx:
	@$(MAKE) -sC mlx

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
