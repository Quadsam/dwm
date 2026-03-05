# dwm version
VERSION = 6.8

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = `pkg-config --cflags freetype2`
LIBS = `pkg-config --libs x11 xinerama fontconfig xft`

# flags
CPPFLAGS += -D_DEFAULT_SOURCE -DVERSION=\"${VERSION}\"
CFLAGS   += -std=gnu23 -Wall -O2 ${INCS}
LDFLAGS  += ${LIBS}

# compiler and linker
CC = clang
