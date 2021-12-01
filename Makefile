NAME		= test

SRCS		= ./main.cpp

# OBJS		= $(SRCS:.cpp=.o)

RM			= rm -rf
CC			= g++
# CFLAGS		= -std=c++98
CFLAGS		= -Wall -Wextra -Werror -std=c++98

# %.o: %.cpp
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME) : $(OBJS)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) main.cpp

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

#  make re; ./test  | > zz_std
# make re; ./test  | > zz_ft ; diff --suppress-common-lines zz_ft zz_std | > zzz_res