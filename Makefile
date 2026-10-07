CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

SRC = src/fiber.c \
      src/scheduler.c \
      src/context.c \
      src/queue.c \
      src/job_control.c \
      src/address_space.c \
      src/memory_manager.c \
      src/page_replacement.c

OBJ = $(SRC:.c=.o)

LIB = fiberlib.a

all: fiber_demo round_robin priority synchronization job_control_demo address_space_demo memory_demo page_replacement_demo test_fiber

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

fiber_demo: $(LIB) examples/basic.o
	$(CC) $(CFLAGS) examples/basic.o $(LIB) -o fiber_demo

round_robin: $(LIB) examples/round_robin.o
	$(CC) $(CFLAGS) examples/round_robin.o $(LIB) -o round_robin

priority: $(LIB) examples/priority.o
	$(CC) $(CFLAGS) examples/priority.o $(LIB) -o priority

synchronization: $(LIB) examples/synchronization.o
	$(CC) $(CFLAGS) examples/synchronization.o $(LIB) -o synchronization

job_control_demo: $(LIB) examples/job_control_demo.o
	$(CC) $(CFLAGS) examples/job_control_demo.o $(LIB) -o job_control_demo

address_space_demo: $(LIB) examples/address_space_demo.o
	$(CC) $(CFLAGS) examples/address_space_demo.o $(LIB) -o address_space_demo

memory_demo: $(LIB) examples/memory_demo.o
	$(CC) $(CFLAGS) examples/memory_demo.o $(LIB) -o memory_demo

page_replacement_demo: $(LIB) examples/page_replacement_demo.o
	$(CC) $(CFLAGS) examples/page_replacement_demo.o $(LIB) -o page_replacement_demo

test_fiber: $(LIB) tests/test_fiber.o
	$(CC) $(CFLAGS) tests/test_fiber.o $(LIB) -o test_fiber

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

examples/%.o: examples/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) examples/*.o tests/*.o $(LIB) fiber_demo round_robin priority synchronization job_control_demo address_space_demo memory_demo page_replacement_demo test_fiber

run: all
	./round_robin
