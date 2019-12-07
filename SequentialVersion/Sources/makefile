NAME=pgx

SRCS= *.cpp

OBJECTS= *.o

INCLUDES=../Headers

all: $(NAME) clean

$(NAME): $(SRCS) ../Headers/*.h
	@g++ -std=c++11 -I$(INCLUDES) -c $(SRCS)
	@g++ -std=c++11 *.o -o solution

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
