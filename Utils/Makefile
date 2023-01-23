NAME = pipex
AR	= ar -rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

BNS = error.c exec.c ft_split.c get_next_line_utils.c get_next_line.c here_doc.c \
		parse.c pipex_utils.c pipex_bonus.c
SRCS = error.c exec.c ft_split.c get_next_line_utils.c \
		parse.c pipex_utils.c pipex.c
OBJS = $(SRCS:.c=.o)
OBJSS= $(BNS:.c=.o)
AOBJS = *.o

all : ${NAME}

${NAME} : ${OBJS}
	@${CC} ${OBJS} -o ${NAME}

%.o : %.c pipex.h
	@${CC} ${CFLAGS} -c $< -o  $@ 

clean : 
	@${RM} ${AOBJS}

fclean : clean
	@${RM} ${NAME}

bonus : $(NAME) $(OBJSS)
	${CC} ${OBJSS} -o ${NAME}


re : fclean bonus

.PHONY : re clean fclean