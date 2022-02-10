targets: 
	ar rcs libuthread.a queue.o context.o uthread.o preempt.o
obj= libuthread.a queue.o context.o uthread.o preempt.o
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -MMD
CFLAGS  += -g
PANDOC  := pandoc

ifneq ($(V),1)
Q = @
endif

all: $(targets)
deps := $(patsubst %.o, %.d, $(objs))
-include $(deps)
libuthread.a: $(objs)
	@echo "CC $@ "
	$(Q)$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	@echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "CLEAN"
	rm -f $(targets) $(objs)
	$(Q)rm -f $(targets) $(objs) $(deps)