NAME		= test

SRCS		= ./main.cpp

RM			= rm -rf
CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) main.cpp

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
