##
## Makefile for  in /home/thomas/Documents/epitech/PSU_2016_nmobjdump
## 
## Made by thomas
## Login   <thomas@epitech.net>
## 
## Started on  Fri Feb 24 15:48:15 2017 thomas
## Last update Fri Feb 24 15:48:15 2017 thomas
##

NM_BIN = my_nm

COMMON_SRCS = fill_elf.c \
              util.c \
              print_header.c \
              print_sections.c \
              elf.c \
              my_revstr.c \
              my_strcat.c \
              my_int_to_str.c \
              static_lib.c \
              get_struct.c

NM_SRCS =   nm.c $(COMMON_SRCS)

NM_OBJS = $(NM_SRCS:.c=.o)

OBJDUMP_BIN = my_objdump

OBJDUMP_SRCS = objdump.c $(COMMON_SRCS)

OBJDUMP_OBJS = $(OBJDUMP_SRCS:.c=.o)

CFLAGS+= -g

all: nm objdump

nm:
	$(CC) -o $(NM_BIN) $(NM_SRCS)  $(CFLAGS)

objdump:
	$(CC) -o $(OBJDUMP_BIN) $(OBJDUMP_SRCS) $(CFLAGS)

re: fclean all

clean:
	$(RM) $(OBJDUMP_OBJS)
	$(RM) $(NM_OBJS)

fclean: clean
	$(RM) $(NM_BIN)
	$(RM) $(OBJDUMP_BIN)
