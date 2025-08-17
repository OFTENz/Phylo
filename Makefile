SRC = main.c \
		./Helpers/base.c \
		./Helpers/Helpers.c \
		./Helpers/check_args.c \
		./Helpers/initialization.c \
		./Helpers/base_.c \
		./Helpers/task_help.c \
		./Helpers/activities.c \
		./Helpers/feast.c\
		monitor.c \
 
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
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
