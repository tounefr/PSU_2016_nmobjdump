
NM_BIN = my_nm

NM_SRCS =   nm.c \
            fill_elf.c \
            util.c \
            print_header.c \
            print_sections.c \
            elf.c

NM_OBJS = $(NM_SRCS:.c=.o)

OBJDUMP_BIN = my_objdump

OBJDUMP_SRCS =  objdump.c \
                fill_elf.c \
                util.c \
                print_header.c \
                print_sections.c \
                elf.c

OBJDUMP_OBJS = $(OBJDUMP_SRCS:.c=.o)

CFLAGS+= -I ./my -L ./my -lmy

all: nm objdump

nm:
	make -C ./my
	$(CC) -o $(NM_BIN) $(NM_SRCS)  $(CFLAGS)

objdump:
	make -C ./my
	$(CC) -o $(OBJDUMP_BIN) $(OBJDUMP_SRCS) $(CFLAGS)

re: fclean all

clean:
	make -C ./my clean
	$(RM) $(OBJDUMP_OBJS)
	$(RM) $(NM_OBJS)

fclean: clean
	make -C ./my fclean
	$(RM) $(NM_BIN)
	$(RM) $(OBJDUMP_BIN)
