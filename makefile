CC	:=	gcc
CFLAGS	:=	-std=c11 -Wall -Wpedantic -Wextra -Werror -O3 -march=native
TARGET	:=	main	
OBJS	:=	main.o graph.o

.PHONY:	all clean run

all: $(TARGET) run

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

%.o: %.c graph.h
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
