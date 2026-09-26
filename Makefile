CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

COVGCNO=src/*.gcno
COVGCDA=src/*.gcda
COVGNRL=coverage/ report.css coverage.info

SRCS=src/my_find.c src/args.c src/structs.c src/error.c src/display_files.c
OBJS=$(SRCS:.c=.o)
TGT=my_find

.PHONY: $(TGT) debug check clean

$(TGT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TGT)

debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TGT) $^

check: CFLAGS += --coverage -fPIC
check: LDLIBS += -lgcov
check: LDFLAGS += --coverage
check: tests/testsuite.sh $(TGT)
	cd tests/ && ./testsuite.sh && cd ..

clean:
	$(RM) $(TGT) debug $(OBJS) $(COVGCNO) $(COVGCDA) $(COVGNRL)
