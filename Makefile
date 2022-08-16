
SRC_CLIENT += client.c
SRC_SERVER += server.c

SRC_CLIENT_BONUS += client_bonus.c
SRC_SERVER_BONUS += server_bonus.c

LIB_MINITALK = libminitalk.a

LIB_MINITALK_BONUS = libminitalk.a

INC = ./include/minitalk.h

EXEC_SERVER = server
EXEC_CLIENT = client

EXEC_SERVER_BONUS = server_bonus
EXEC_CLIENT_BONUS = client_bonus

OBJ_SERVER = ${SRC_SERVER:.c=.o}
OBJ_CLIENT= ${SRC_CLIENT:.c=.o}

OBJ_SERVER_BONUS = ${SRC_SERVER_BONUS:.c=.o}
OBJ_CLIENT_BONUS = ${SRC_CLIENT_BONUS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -g

all : $(EXEC_SERVER) $(EXEC_CLIENT) $(LIB_MINITALK)

$(EXEC_SERVER) : $(LIB_MINITALK)
	$(CC) $(CFLAGS) server.c $(LIB_MINITALK) -o $(EXEC_SERVER)

$(EXEC_CLIENT) : $(LIB_MINITALK)
	$(CC) $(CFLAGS) client.c $(LIB_MINITALK) -o $(EXEC_CLIENT)

$(LIB_MINITALK) :
	make -C ./printf
	cp -R ./printf/libftprintf.a .
	mv libftprintf.a $(LIB_MINITALK)
	gcc -c $(SRC_SERVER)
	gcc -c $(SRC_CLIENT)
	ar rcs $(LIB_MINITALK) $(OBJ_SERVER) $(OBJ_CLIENT) 

clean :
	make clean -C ./printf
	rm -rf $(LIB_MINITALK)
	rm -rf $(OBJ_SERVER)
	rm -rf $(OBJ_CLIENT)
	rm -rf $(OBJ_SERVER_BONUS)
	rm -rf $(OBJ_CLIENT_BONUS)

fclean : clean
	make fclean -C ./printf
	rm -rf $(EXEC_SERVER)
	rm -rf $(EXEC_CLIENT)
	rm -rf $(EXEC_SERVER_BONUS)
	rm -rf $(EXEC_CLIENT_BONUS)

re : fclean all 

bonus : $(LIB_MINITALK_BONUS) $(EXEC_SERVER_BONUS) $(EXEC_CLIENT_BONUS) 

$(EXEC_SERVER_BONUS) : $(LIB_MINITALK_BONUS)
	$(CC) $(CFLAGS) server_bonus.c $(LIB_MINITALK_BONUS) -o $(EXEC_SERVER_BONUS)

$(EXEC_CLIENT_BONUS) : $(LIB_MINITALK_BONUS)
	$(CC) $(CFLAGS) client_bonus.c $(LIB_MINITALK_BONUS) -o $(EXEC_CLIENT_BONUS)

$(LIB_MINITALK_BONUS) :
	make -C ./printf
	cp -R ./printf/libftprintf.a .
	mv libftprintf.a $(LIB_MINITALK_BONUS)
	gcc -c $(SRC_SERVER_BONUS)
	gcc -c $(SRC_CLIENT_BONUS)
	ar rcs $(LIB_MINITALK_BONUS) $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS) 


