SRC = philo.c \
		utils.c \
		check_args.c \
		initialization.c \
		more_task.c \
		philo_task.c \
		eat.c monitor.c \
		creat_philosopher.c \
		 init_mutex.c  \
		  philosopher_routine.c
 
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
