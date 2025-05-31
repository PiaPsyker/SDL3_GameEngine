CFLAGS = -std=c++17
#-O2
LDFLAGS = -w -lSDL3 -lSDL3_image -lSDL3_ttf -Iinclude -Lsrc

#WARNFLAGS = -Wall -Weffc++ -pedantic  \
	-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
	-Wcast-qual -Wconversion \
	-Wdisabled-optimization \
	-Werror -Wfloat-equal -Wformat=2 \
	-Wformat-nonliteral -Wformat-security  \
	-Wformat-y2k \
	-Wimplicit  -Wimport  -Winit-self  -Winline \
	-Winvalid-pch   \
	-Wlong-long \
	-Wmissing-field-initializers -Wmissing-format-attribute   \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked  -Wpadded -Wpointer-arith \
	-Wredundant-decls \
	-Wshadow -Wstack-protector \
	-Wstrict-aliasing=2 -Wswitch-default \
	-Wswitch-enum \
	-Wunreachable-code -Wunused \
	-Wunused-parameter \
	-Wvariadic-macros \
	-Wwrite-strings

# -g $(CFLAGS)
# mkdir ./build/testMap

build/test: src/main.cpp
	cp -r ./resources ./build/
	g++ -std=c++17 -g -o build/test \
	src/*.cpp \
	src/map/*.cpp \
	src/entities/*.cpp \
	src/noise/*.cpp \
	src/generator/*.cpp \
	$(LDFLAGS) $(WARNFLAGS)

.PHONY: test clean

debug: build/test
	gdb -ex run ./build/test

test: build/test
	./build/test

clean:
	rm -rf ./build/resources
	rm -rf ./build/test
	rm -rf ./build/currentMap.bin
	