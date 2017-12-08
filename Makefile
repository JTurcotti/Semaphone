CFLAGS:=-Wall -Werror
DEBUG:=false
OUTPUT:=control

ifeq ($(DEBUG),true)
	CFLAGS:=$(CFLAGS) -g
endif

all: $(OUTPUT)

$(OUTPUT): control.o semaphore.o
	gcc -o $@ $^

control.o: control.c semaphore.h
	gcc $(CFLAGS) -c $<

semaphore.o: semaphore.c semaphore.h
	gcc $(CFLAGS) -c $<

clean:
	rm -f *~ .*.swp *.exe *.o $(OUTPUT)

run: all
	./$(OUTPUT)
