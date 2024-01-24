CC := gcc
CFLAGS := -w

.PHONY: all clean runner test

all: runner.out test_runner.out

runner.out: runner.c libdummy.so
	$(CC) $(CFLAGS) -o $@ $< -L. -ldummy -Wl,-rpath,.

test_runner.out: test_runner.c libdummy.so
	$(CC) $(CFLAGS) -o $@ $< -L. -ldummy -Wl,-rpath,.

libdummy.so: libdummy.c
	$(CC) $(CFLAGS) -shared -o $@ $<

runner: runner.out libdummy.so

test: test_runner.out libdummy.so
	./test_runner.out

clean:
	rm -f runner.out test_runner.out libdummy.so
