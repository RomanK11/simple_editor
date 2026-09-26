CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = simple_editor

SRC = main.c funcs.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

PACKAGE = simple-editor
VERSION = 1.0.0
ARCH = amd64

package: $(TARGET)
	mkdir -p $(PACKAGE)/DEBIAN
	mkdir -p $(PACKAGE)/usr/bin
	cp $(TARGET) $(PACKAGE)/usr/bin/
	chmod 755 $(PACKAGE)/DEBIAN
	chmod 755 $(PACKAGE)/usr/bin
	printf 'Package: $(PACKAGE)\nVersion: $(VERSION)\nSection: editors\nPriority: optional\nArchitecture: $(ARCH)\nMaintainer: Roman\nDescription: Simple terminal text editor written in C\n' > $(PACKAGE)/DEBIAN/control
	chmod 644 $(PACKAGE)/DEBIAN/control
	dpkg-deb --build $(PACKAGE)