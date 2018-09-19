OUTPUT=blowfish

CC=gcc
CC_OPT=-std=c99

.PHONY: all
all: $(OUTPUT)

$(OUTPUT): $(OUTPUT)_test.c $(OUTPUT).c $(OUTPUT).h
	$(CC) -o $(OUTPUT) $(CC_OPT) $(OUTPUT)_test.c $(OUTPUT).c $(OUTPUT).h

.PHONY: clean
clean:
	rm $(OUTPUT)
