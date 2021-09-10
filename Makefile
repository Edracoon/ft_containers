# === EXECUTABLES ===============
FT_NAME		=	ft_containers.exe

STL_NAME	=	stl_containers.exe

# === COMPILATION ===============
CXX			=	clang++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

# === FT SRCS / OBJS ============
FT_SRCS		=	$(wildcard FT_srcs/*.cpp)

FT_OBJS		=	$(FT_SRCS:.cpp=.o)

# === STL SRCS / OBJS ===========
STL_SRCS	=	$(wildcard STL_srcs/*.cpp)

STL_OBJS	=	$(STL_SRCS:.cpp=.o)

# === RULES =====================
all:			$(FT_NAME) $(STL_NAME)

$(FT_NAME):		$(FT_OBJS)
				$(CXX) $(CXXFLAGS) $(FT_OBJS) -o $(FT_NAME)

$(STL_NAME):	$(STL_OBJS)
				$(CXX) $(CXXFLAGS) $(STL_OBJS) -o $(STL_NAME)

clean:
			rm -rf $(FT_OBJS)
			rm -rf $(STL_OBJS)

fclean:		clean
			rm -rf $(FT_NAME)
			rm -rf $(STL_NAME)

re:			fclean all

.PHONY:		all clean fclean re
