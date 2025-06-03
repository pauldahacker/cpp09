BROWN =	\033[38;2;184;143;29m
ORANGE = \033[38;5;209m
BLUE = \033[38;5;18m
DEF_COLOR = \033[0;39m
GREEN =	\033[0;92m
GRAY = \033[38;5;8m

NAME = btc
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

HEADER = BitcoinExchange.hpp Data.hpp Utils.hpp

SRC = BitcoinExchange.cpp Data.cpp Utils.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@echo "$(BLUE)Flags		$(GRAY)$(FLAGS)$(DEF_COLOR)"
	@echo "$(GREEN)$(NAME) compiled succesfully!$(DEF_COLOR)"

%.o: %.cpp $(TEMPLATE) Makefile
	@echo "$(BROWN)Compiling	$(BLUE)→ $(ORANGE)$<$(DEF_COLOR)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(BROWN)Successfully removed objects!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BROWN)Successfully removed binaries!$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re