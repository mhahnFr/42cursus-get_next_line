# The name of the library to create.
NAME	=	gnl.a

# The source files needed for the library.
SRC		=	get_next_line.c \
			get_next_line_utils.c

# The flags to compile the files with.
CFLAGS	=	-Wall -Werror -Wextra

# A macro to get the object files for the corresponding source files.
OBJ		=	$(patsubst %.c,%.o,$(SRC))

# Compiles the whole library.
all: $(NAME)

# Creates the library.
$(NAME): $(OBJ)
	$(AR) -rs $(NAME) $(OBJ)

# Compiles each source file individually.
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Removes all object files.
.phony: clean
clean:
	- $(RM) $(OBJ)

# Removes all files created by this makefile.
.phony: fclean
fclean: clean
	- $(RM) $(NAME)

# Removes everything created by this makefile and recompiles the library.
re: fclean all