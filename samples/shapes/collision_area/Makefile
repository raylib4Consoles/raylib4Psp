BUILD_PRX = 1
TARGET = raylib
OBJS = main.o
INCDIR =
CFLAGS = -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS=   -lraylib -lpng -lz  -lglut -lGLU -lGL -lpspvfpu 

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = raylib shapes collision
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


