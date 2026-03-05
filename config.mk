# dwm version
VERSION   := 6.8

# compiler and linker
CC        := clang

# paths
PREFIX    := /usr/local
MANPREFIX := ${PREFIX}/share/man

# flags
# CPPFLAGS  := -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L
CPPFLAGS  += `pkg-config --cflags freetype2` -DVERSION=\"${VERSION}\"
CFLAGS    += -std=gnu23 -Wall -Os
# LDFLAGS   +=
LDLIBS    += -lX11 -lXinerama -lfontconfig -lXft
