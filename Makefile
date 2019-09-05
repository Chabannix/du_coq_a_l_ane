BUILD_DIR=build_makefile

CC=gcc
CFLAGS=-Wall -g       # options de compilations
LDFLAGS=              # options de l'éditions de liens

$(BUILD_DIR)/exe: $(BUILD_DIR)/main.o
	mkdir -p $(@D)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/main.o: main.c
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/exe