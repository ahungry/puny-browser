# Puny Browser - The weakest browser around!
# Copyright (C) 2015 Matthew Carter <m@ahungry.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Find the libs looking for name.pc

CC = gcc
CFLAGS = -c -Wall -std=c99
LIBS = gtk+-3.0 webkit2gtk-4.0
CFLAGS += `pkg-config --cflags $(LIBS)` -D_XOPEN_SOURCE=500
LDFLAGS += `pkg-config --libs $(LIBS)` -lX11 -lXext

all: main

main: main.o
	$(CC) main.o $(LDFLAGS) -o puny-browser

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *o puny-browser
