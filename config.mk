# dwm version
VERSION = 6.8

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = `pkg-config --cflags-only-I freetype2`
LIBS = `pkg-config --libs x11 xinerama fontconfig xft`

# flags
CPPFLAGS += -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DXINERAMA -DVERSION=\"${VERSION}\"
CFLAGS   += -g -std=c99 -pedantic -Wall -Wno-deprecated-declarations -O0 ${INCS} ${CPPFLAGS}
LDFLAGS  += ${LIBS}

# compiler and linker
CC = gcc
