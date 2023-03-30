NAME 		= RPN

CFLAGS		= -std=c++98 -Wall -Wextra -Werror

SRC			= main.cpp

SRC			+= RPN.cpp

all : $(NAME)

$(NAME): $(SRC)
	@c++ $(CFLAGS) $(SRC) -o $(NAME)
	@echo "\033[92mExecution file Created\033[0m" 

clean:
	@rm -rf $(NAME)
	@echo "\033[91mExecution file deleted\033[0m"

fclean:
	@rm -rf $(NAME)
	@echo "\033[91mExecution file deleted\033[0m" 
	
re: fclean all
	
.PHONY: fclean clean re all 