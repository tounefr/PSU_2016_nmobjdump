
NM_BIN = my_nm

NM_SRCS =   nm.c \
            fill_elf.c \
            util.c \
            print_header.c \
            print_sections.c \
            elf.c \
            my_revstr.c \
            my_strcat.c \
            my_int_to_str.c

NM_OBJS = $(NM_SRCS:.c=.o)

OBJDUMP_BIN = my_objdump

OBJDUMP_SRCS =  objdump.c \
                fill_elf.c \
                util.c \
                print_header.c \
                print_sections.c \
                elf.c \
                my_revstr.c \
                my_strcat.c \
                my_int_to_str.c

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
