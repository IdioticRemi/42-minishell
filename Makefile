# Program name
NAME	= minishell

# Directories

INC_DIR	= inc/
SRC_DIR	= src/
OBJ_DIR	= obj/
SUBDIRS = $(addprefix $(OBJ_DIR), $(shell find -mindepth 1 -type d -path "./src/*" | cut -c 7-))

# Sources
__SRCS	= $(shell find -type f -path "./src/*.c" | cut -c 7-)

SRCS	= $(addprefix $(SRC_DIR), $(__SRCS))
OBJS	= $(addprefix $(OBJ_DIR), $(__SRCS:.c=.o))

# Compile
CC		= clang

CFLAGS	= -Wall -Werror -Wextra -O3 -g3 -fsanitize=address
INCLUDE	= -I $(INC_DIR)
LIBS	= -lreadline

# Color

FG_MAGE	= \033[0;35m
FG_CYAN	= \033[0;36m
FG_WHIT	= \033[0;37m
FG_GREE	= \033[0;32m

# Rules
all: log $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)/$(NAME).h
	@mkdir -p $(OBJ_DIR) $(SUBDIRS)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "."

$(NAME): $(OBJS)
	@printf " [$(words $(OBJS))]\n"
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME) $(LIBS)
	@printf "$(FG_WHIT)[ MINISHELL ] $(FG_GREE)Built '$(NAME)'.$(FG_WHIT)\n"

log:
	@printf "$(FG_WHIT)[ MINISHELL ] $(FG_CYAN)Starting build process.$(FG_WHIT)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(FG_WHIT)[ MINISHELL ] $(FG_MAGE)Build objects cleaned.$(FG_WHIT)\n"

fclean:
	@rm -rf $(NAME) $(OBJ_DIR)
	@printf "$(FG_WHIT)[ MINISHELL ] $(FG_MAGE)Program files cleaned.$(FG_WHIT)\n"

norm:
	@norminette $(SRC_DIR) $(INC_DIR)

re: fclean all