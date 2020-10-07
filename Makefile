##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

NAME		=	plazza

NAME_TEST	=	test

DIRBONUS	=	bonus/

DIR 		=	src/

DIRPIZZA	=	src/pizza/

SRC	=			$(DIRPIZZA)Regina.cpp				\
				$(DIRPIZZA)Pizza.cpp				\
				$(DIRPIZZA)Margarita.cpp			\
				$(DIRPIZZA)Fantasia.cpp				\
				$(DIRPIZZA)Americana.cpp			\
				$(DIRPIZZA)$(DIRBONUS)Neptune.cpp	\
				$(DIR)$(DIRBONUS)Server.cpp			\
				$(DIR)$(DIRBONUS)PlazzaServer.cpp	\
				$(DIR)Enums.cpp						\
				$(DIR)Order.cpp						\
				$(DIR)Ingredients.cpp				\
				$(DIR)plazza.cpp					\
				$(DIR)Receptionist.cpp				\
				$(DIR)Kitchen.cpp					\
				$(DIR)Cook.cpp						\
				$(DIR)Thread.cpp					\
				$(DIR)Socket.cpp					\
				$(DIR)main.cpp						\
				$(DIR)IPC.cpp

SRC_TEST	=	$(DIR)main.cpp						\

CPPFLAGS	+=	-I./include -I./class -I./include/pizza -I./include/pizza/bonus -I./include/bonus

SCOTT		+=	-Weffc++

BASIC		+=	 -Wall -Wextra -Werror

PORTABILITY	+=	-pedantic

THREAD		+=	-pthread

LDFLAGS		+=	-lcriterion

SPEED		+=	-O3

SIZE		+=	-Os -s

DEBUG		=	-DDEBUG

#LATER		+=	-Wfloat-equal -Woverloaded-virtual -Wconversion -Wdouble-promotion -Wold-style-cast -Wcast-align -Wcast-qual -Wpointer-arith

CXXFLAGS	+=	-std=gnu++17 $(SCOTT) $(BASIC) $(PORTABILITY) $(THREAD) -g3

TEST		+=	$(LDFLAGS)

OBJ			=	$(SRC:.cpp=.o)

OBJ_TEST	=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

debug:	$(SRC)
	g++ -o $(NAME) $(SRC) $(CXXFLAGS) $(DEBUG) $(CPPFLAGS)

clean:
	rm -rf $(OBJ)
	rm -rf *.txt

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
	#ipcrm --all=msg

.PHONY:	fclean all clean re debug
