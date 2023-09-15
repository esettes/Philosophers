GREEN	= \033[0;32m
WHITE	= \033[0;37m
LGREEN	= \033[2;32m
LWHITE	= \033[2;37m
RESET	= \033[0m
GREY	= \033[1;30m

NAME	= philo

OS		=	$(shell uname -s)

SRCDIR	= ./src/
SRCNAMES	= $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC	= $(addprefix $(SRCDIR), $(SRCNAMES))
OBJDIR	= ./src/obj/
OBJS	= $(addprefix $(OBJDIR), $(SRCNAMES:.c=.o))

HEADERS	= -I include -I ./inc/

CC	= clang
CFLAGS	= -g3 -pthread # -Wall -Wextra -Werror #-fsanitize=address -Ofast -fno-omit-frame-pointer

ifeq ($(OS), Linux)
	VALGRIND = valgrind --tool=memcheck --leak-check=full --track-origins=yes -s
endif

all: obj  $(NAME)

obj:
	@mkdir -p $(OBJDIR)

obj_b:
	@mkdir -p $(OBJDIR_B)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@ $(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME):	$(OBJS)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "${LWHITE}$(NAME) ${LGREEN}✓$(RESET)"
	@echo "${GREY}Compilation ${GREEN}[OK]$(RESET)"

LD_DEBUG=all

n:
	@norminette ./src/*.c ./inc/*.h ./bonus/src/*.c ./bonus/inc/*.h

dbgfiles:
	@rm -rf *.dSYM
	@rm -rf *.DS_Store
	@echo "${LWHITE}Clean debug files... ${LGREEN}✓$(RESET)"

clean:	dbgfiles
	@echo "${LWHITE}Clean philo... ${LGREEN}✓$(RESET)"
	@rm -rf ${OBJDIR}*.o
	@rm -rf ${OBJDIR_B}*.o

fclean: dbgfiles
	@rm -rf $(NAME)
	@echo "${LWHITE}Clean philo... ${LGREEN}✓$(RESET)"
	@rm -rf ${OBJDIR}*.o
	@rm -rf ${OBJDIR_B}*.o
	@echo "${GREY}Clean all ${GREEN}[OK]$(RESET)"
	@echo "\n"

re: fclean all

.PHONY: all fclean clean re