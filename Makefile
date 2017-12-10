CFLAGS:=-Wall -Werror
DEBUG:=false
CONTROL_OUTPUT:=control
CLIENT_OUTPUT:=client

ifeq ($(DEBUG),true)
	CFLAGS:=$(CFLAGS) -g
endif

all: $(CONTROL_OUTPUT) $(CLIENT_OUTPUT)

$(CONTROL_OUTPUT): control.o semaphore.o memory.o file.o
	gcc -o $@ $^

$(CLIENT_OUTPUT): client.o semaphore.o memory.o file.o
	gcc -o $@ $^	

client.o: client.c libraries.h semaphore.h memory.h file.h
	gcc $(CFLAGS) -c $<	

control.o: control.c libraries.h semaphore.h memory.h file.h
	gcc $(CFLAGS) -c $<

semaphore.o: semaphore.c libraries.h semaphore.h memory.h file.h
	gcc $(CFLAGS) -c $<
memory.o: memory.c libraries.h semaphore.h memory.h file.h
	gcc $(CFLAGS) -c $<
file.o: file.c libraries.h semaphore.h memory.h file.h
	gcc $(CFLAGS) -c $<


clean:
	rm -f *~ .*.swp *.exe *.o *.txt *.gch $(OUTPUT)

run: all
	./$(OUTPUT)
