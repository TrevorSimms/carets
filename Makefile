CC = cc
CFLAGS = -g -Wall -I$(INCDIR) -lncurses

SRCDIR = src
OBJDIR = obj
INCDIR = inc

SRCS = $(wildcard $(SRCDIR)/*.c)
DEPS = $(wildcard $(INCDIR)/*.h)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

OUT = nrucres

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@	

clean:
	rm -f $(OUT) $(OBJS)
