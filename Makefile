BUILD_DIR=build_makefile
SRC_DIR=src
HEADERS=src/*.h

CC=gcc
CFLAGS=-Wall -g       # options de compilations
LDFLAGS=              # options de l'éditions de liens

$(BUILD_DIR)/exe: $(BUILD_DIR)/main.o
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/exe