#!/bin/sh

gcc -O2 -Wall -W -Wextra -g -ggdb -o lj_dbus lj_dbus.c		\
	-DLJ_DBUS_CONSOLE_TEST					\
	$(pkg-config --cflags --libs dbus-1 dbus-glib-1)
