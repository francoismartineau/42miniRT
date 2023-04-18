SRC_FILES	=	exit.c \
				main.c \
				math/vecmath.c \
				parse/file.c \
				parse/file2.c \
				parse/file3.c \
				parse/ranges.c \
				parse/scene.c \
				parse/scene2.c \
				render/context.c \
				render/raycast.c \
				util/atod.c \
				util/get_next_line/get_next_line.c \
				util/get_next_line/get_next_line_utils.c \
				util/mem.c \
				util/str.c \
				util/vec3.c

SRC_DIR		=	src

OBJ_DIR=obj
OBJ:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=miniRT

CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic -Werror -Isrc
LDFLAGS=
LDLIBS=

all: $(NAME)

bonus: all

norm:
	norminette src/

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
#	@norminette $<
	$(CC) $(CCFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ)
	$(CC) $^ -o $(NAME) $(LDFLAGS) $(LDLIBS) 

.PHONY: clean fclean re all norm

-include $(OBJ:.o=.d)
