objs    := queue.o uthread.o preempt.o context.o
target: 
	ar rcs libuthread.a queue.o context.o uthread.o preempt.o

CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -MMD
CFLAGS  += -g
PANDOC  := pandoc

ifneq ($(V),1)
Q = @
endif

target: $(targets)
deps := $(patsubst %.o, %.d, $(objs))
-include $(deps)

%.a: $(objs)
	@echo "CC $@ "
	ar rcs %.a  $@ $^

%.o: %.c 
	@echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "CLEAN"
	rm -f $(targets) $(objs)
	$(Q)rm -f $(targets) $(objs) $(deps)