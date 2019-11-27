
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testReverseList2.c
EXERCISE_FILE = reverseList2.c
COMMON = list.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testReverseList2

testReverseList2: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testReverseList2 $(SRC_FILES)

