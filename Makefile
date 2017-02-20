
NM_BIN = my_nm

NM_SRCS = objdump.c \
          fill_elf.c \
          util.c \
          print_header.c \
          print_sections.c \
          elf.c

NM_OBJS = $(NM_SRCS:.c=.o)

OBJDUMP_BIN = my_objdump

OBJDUMP_SRCS =  $(NM_SRCS)

OBJDUMP_OBJS = $(OBJDUMP_SRCS:.c=.o)

all: nm objdump

nm:
	$(CC) -o $(NM_BIN) $(NM_SRCS)

objdump:
	$(CC) -o $(OBJDUMP_BIN) $(OBJDUMP_SRCS)

re: fclean all

clean:
	$(RM) $(OBJDUMP_OBJS)
	$(RM) $(NM_OBJS)

fclean: clean
	$(RM) $(NM_BIN)
	$(RM) $(OBJDUMP_BIN)
