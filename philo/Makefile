.PHONY: all clean fclean re

NAME = philo

$(NAME): all

all:
	gcc -Wall -Werror -Wextra -pthread ft_philosophers.c ft_philosopher_initialize.c ft_input_check.c ft_run_philosophers.c ft_run_philosophers_utils.c -o $(NAME)

clean:
	@if [ -f "$(NAME)" ]; then\
		rm $(NAME);\
		printf "rm $(NAME)\n";\
	else\
		printf "$(NAME) Doesn't Exist so It Cannot Be Removed\n";\
	fi


fclean: clean

re: clean all	
