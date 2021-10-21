# === EXECUTABLES ===============
FT_NAME		=	FT_$(TESTER).exe

STL_NAME	=	STL_$(TESTER).exe

# === COMPILATION ===============
CXX			=	clang++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

# === FT SRCS / OBJS ============
FT_SRCS		=	$(wildcard FT_mains/$(TESTER).cpp)

FT_OBJS		=	$(FT_SRCS:.cpp=.o)

# === STL SRCS / OBJS ===========
STL_SRCS	=	$(wildcard STL_mains/$(TESTER).cpp)

STL_OBJS	=	$(STL_SRCS:.cpp=.o)

# === RULES =====================
all:			$(FT_NAME) $(STL_NAME)

$(FT_NAME):		$(FT_OBJS)
				$(CXX) $(CXXFLAGS) $(FT_OBJS) -o $(FT_NAME)

$(STL_NAME):	$(STL_OBJS)
				$(CXX) $(CXXFLAGS) $(STL_OBJS) -o $(STL_NAME)

diff:		re
			./$(FT_NAME) > FT.log
			./$(STL_NAME) > STL.log
			diff FT.log STL.log | cat

clean:
			rm -rf $(wildcard *.log *.diff)
			rm -rf $(FT_OBJS)
			rm -rf $(STL_OBJS)

fclean:		clean
			rm -rf $(FT_NAME)
			rm -rf $(STL_NAME)

re:			fclean all

.PHONY:		all clean fclean re
