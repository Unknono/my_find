CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla

COVGCNO=*.gcno
COVGCDA=*.gcda
COVGNRL=coverage/ report.css coverage.info

SRCS=
OBJS=$(SRCS:.c=.o)
TGT=my_find

$(TGT): $(OBJS)
	$(CC) $(CFLAGS) -o $(TGT) $^

debug: CFLAGS += -g -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TGT) $^

# UNITARY TESTSUITE ONLY
# check: CFLAGS += --coverage -fPIC
# check: LDLIBS += -lgcov
# check: LDFLAGS += --coverage

check: tests/testsuite.sh $(TGT)
	./tests/testsuite.sh

.PHONY: clean

clean:
	$(RM) $(TGT) debug $(OBJS) $(COVGCNO) $(COVGCDA) $(COVGNRL)
