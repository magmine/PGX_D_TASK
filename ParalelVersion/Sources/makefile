NAME=solution

SRCS= *.cpp

OBJECTS= *.o

INCLUDES=../Headers

all: $(NAME) clean

$(NAME): $(SRCS) ../Headers/*.h
	@g++ -std=c++11 -I$(INCLUDES) -c $(SRCS)
	@g++ -std=c++11 *.o -o $(NAME) -pthread

test: $(NAME)
	./$(NAME) G1_notFully_notWeakly.txt
	./$(NAME) G2_notFully_Weakly.txt
	./$(NAME) G3_fully_weakly.txt
	./$(NAME) G7_notFully_notWeakly.txt


clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
