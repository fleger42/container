MINE = ft_container

REAL = std_container

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

HEADER = -I ./include/

SRCS = main.cpp

MINE_OBJ = $(SRCS:cpp=o)

REAL_OBJ = std_main.o

all: $(MINE) $(REAL)

$(MINE): $(MINE_OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling program with my container..."
	@$(CXX) $(CXXFLAGS) ${HEADER} -o $(MINE) $(MINE_OBJ)
	@echo "\n\033[0mDone !"

$(REAL): $(REAL_OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling program with real container..."
	@$(CXX) $(CXXFLAGS) ${HEADER} -o $(REAL) std_main.o
	@echo "\n\033[0mDone !"

std_main.o:
	@printf "\033[0;33mGenerating std objects... %-33.33s\r" $@
	@${CXX} -D ACCESS=std ${CXXFLAGS} ${HEADER} -c main.cpp -o std_main.o
%.o: %.cpp
	@printf "\033[0;33mGenerating ft objects... %-33.33s\r" $@
	@${CXX} -D ACCESS=ft ${CXXFLAGS} ${HEADER} -c $< -o $@

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(MINE_OBJ) $(REAL_OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(MINE_OBJ) $(REAL_OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(MINE) $(REAL)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re test norm