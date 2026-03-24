
CC = c++ -g3

FLAGS = -Wall -Werror -Wextra -MMD -std=c++98

NAME = PmergeMe

SRCS = main.cpp \
		PMergeMe.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

COLOR = \e[94m
RESET = \e[0m

all	: $(NAME)

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)
	@printf "$(COLOR)▗▄▄▄▖▗▖  ▗▖▄▀▀▚▖▄▄▄▄\n"
	@printf 	    "▐▌    ▝▚▞▘ █  ▐▌   █\n"
	@printf 	    "▐▛▀▀▘  ▐▌  █  ▐▌█▀▀▀\n"
	@printf 	    "▐▙▄▄▖▗▞▘▝▚▖▀▄▄▞▘█▄▄▄\n$(RESET)"

clean	:
	@rm -f $(OBJS) $(DEPS)
	@printf "> Ojects        ❌\n"

fclean	:	clean
	@rm -f $(NAME)
	@printf "> Executable    ❌\n"

re	:	fclean all

.PHONY: all clean fclean re

-include $(DEPS)

#---------- Test ----------

test : $(NAME)
	@echo "List size ?"; \
	read SIZE; \
	echo "List max value ?"; \
	read MAX; \
	echo "\n-------------------\n"; \
	./$(NAME) "$$(shuf -i 0-$$MAX -n $$SIZE | tr '\n' ' ')";