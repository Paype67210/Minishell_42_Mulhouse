NAME            =	minishell
PRINT_PREFIX    =	\033[1m\033[38;5;240m[\033[0m\033[38;5;250m\
                   		 $(NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

CC				=	@cc
CFLAGS          =	-Wall -Werror -Wextra -g3

SRC_DIR         =	srces/
OBJ_DIR         =	.obj/
LIBFT_LIB		=	libft/libft.a

SRC             =	main.c \
					utils.c \
					execution.c \
					checking.c \
					second_checking.c \
					if_command1.c \
					if_command2.c \
					if_sign1.c \
					if_sign2.c \
					if_dollar.c \
					if_other1.c \
					if_other2.c \
					ft_split_check.c \
					init.c \
					ft_error.c \
					ft_exit.c \
					ft_exec_echo.c \
					ft_exec_cd.c \
					ft_exec_pwd.c \
					ft_exec_unset.c \
					ft_exec_export.c \
					ft_exec_env.c \
					ft_exec_exit.c \
					ft_exec_execve.c \
					ft_exec_redi_ipt.c \
					ft_exec_here_doc.c \
					ft_exec_pipe.c \
					ft_exec_dbl_pipe.c \
					ft_exec_dbl_esp.c \
					ft_wildcards.c ft_wildcards_utils.c \
					ft_exec_prt.c \
					ft_exec_other.c \
					ft_sort_list.c \
					chainlist_to_dblpoint.c \
					ft_print_export.c \
					ft_signal.c ft_debug.c \
					utils2.c utils3.c utils4.c \

SRCES           =	$(addprefix $(SRC_DIR), $(SRC))
OBJ             =	$(SRC:.c=.o)
OBJS            =	$(addprefix $(OBJ_DIR), $(OBJ))

NUM_FILES		=	$(words $(SRCES))
BAR_LENGTH		=	$(shell echo "$$(($(NUM_FILES)*1))")

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@printf "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m["
	@for i in $(shell seq 1 $(BAR_LENGTH)); do \
		sleep 0.02; \
		printf "\033[38;5;40m▲▼"; \
	done
	@printf "\033[38;5;40m] \033[0m\n"
	@make -C libft/ all --no-print-directory
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME)
	@echo "$(PRINT_PREFIX)\033[0;32m Done \033[0;37m\n"

clean:
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@make -C libft/ clean --no-print-directory
	@rm -rf $(OBJS)
	@echo "$(PRINT_PREFIX)\033[0;32m Done \033[0;37m\n"

fclean: clean
	@make -C libft/ clean --no-print-directory
	@rm -rf $(NAME) $(OBJ_DIR)

re: fclean all

run: all clean
	./$(NAME)

.PHONY: all clean fclean re run