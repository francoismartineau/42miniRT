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
				util/vec3.c

SRC_DIR		=	src

OBJ_DIR=obj
OBJ:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=miniRT

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror  -Isrc -Imlx/include -Ofast -mfpmath=sse -msse3 -ffast-math -flto
LDFLAGS=-Lmlx -Wall -Ofast -flto -ffast-math -mfpmath=sse -msse3
LDLIBS=-lmlx42 -framework OpenGL -framework AppKit -framework IOKit -L/Users/francoma/homebrew/lib -lglfw

all: mlx $(NAME)

mlx/libmlx42.a:
	$(MAKE) -sC mlx

mlx: mlx/libmlx42.a

noerr: CFLAGS:=$(subst -Werror,,$(CFLAGS))
noerr: all

linux: LDLIBS:=-lmlx42 -ldl -lglfw -pthread -lm
linux: CFLAGS:=-Isrc -Imlx/include
linux: CFLAGS+= -g -Og -DDEBUG
linux: all

sanit: CFLAGS+=-g -Og -fsanitize=address
sanit: LDFLAGS+=-fsanitize=address
sanit: re

debug: CFLAGS+=-g -Og -DDEBUG
debug: re

rel: CFLAGS+=-O2
rel: re

clean:
	@-find $(OBJ_DIR) -type f -name '*.o' -delete
	@-find $(OBJ_DIR) -type f -name '*.d' -delete

fclean: clean
	@-rm -f $(NAME)
	@-rm -r $(OBJ_DIR)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $(NAME) $(LDLIBS)

.PHONY: clean fclean re all mlx

-include $(OBJ:.o=.d)
