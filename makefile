NAME=solution

SRCS= Sources/*.cpp

OBJECTS= *.o

INCLUDES=Headers

INPUT_FILES=Input

all: $(NAME) clean

$(NAME): $(SRCS) $(INCLUDES)/*.h
	@g++ -std=c++11 -I$(INCLUDES) -c $(SRCS) -Wall -Wextra
	@g++ -std=c++11 $(OBJECTS) -o $(NAME) -pthread

test: $(NAME)
	./$(NAME) $(INPUT_FILES)/G1_notFully_notWeakly.txt
	./$(NAME) $(INPUT_FILES)/G2_notFully_Weakly.txt
	./$(NAME) $(INPUT_FILES)/G3_fully_weakly.txt
	./$(NAME) $(INPUT_FILES)/G7_notFully_notWeakly.txt


clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
