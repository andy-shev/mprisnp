#!/bin/sh
gcc -O2 -Wall -W -Wextra -g -ggdb -o lj_dbus main_dbus.c `pkg-config --cflags --libs dbus-1 dbus-glib-1`
