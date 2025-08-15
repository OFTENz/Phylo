SRC = main.c \
		./Helpers/base.c \
		utils.c \
		./Helpers/check_args.c \
		initialization.c \
		tasks.c \
		./Helpers/base_.c \
		task_help.c \
		feast.c\
		monitor.c \
 
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
NAME = philo 

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME) 

%.o : %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
