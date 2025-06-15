# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2
BINARY = supertdl
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

# Targets
all: $(BINARY)

$(BINARY): src/supertdl.c
	$(CC) $(CFLAGS) -o $(BINARY) src/supertdl.c

install: $(BINARY)
	@echo "Installing binary to $(BINDIR)..."
	install -m 755 $(BINARY) $(BINDIR)/

	@echo "Installing man page to $(MANDIR)..."
	install -d $(MANDIR)
	install -m 644 man/$(BINARY).1 $(MANDIR)/

	@echo "Updating man database..."
	mandb -q

uninstall:
	@echo "Removing binary from $(BINDIR)..."
	rm -f $(BINDIR)/$(BINARY)

	@echo "Removing man page from $(MANDIR)..."
	rm -f $(MANDIR)/$(BINARY).1

	@echo "Updating man database..."
	mandb -q

clean:
	rm -f $(BINARY)

.PHONY: all install uninstall clean
