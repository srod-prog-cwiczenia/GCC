CC=g++
CFLAGS = # tutaj mozna dodawac flagi kompilatora
LIBS = -lncurses # tutaj mozna dodawać biblioteki
#### trzeba uporzadkowac opcje, bo te powyzej sa specyficzne dla tego
#### pliku a te ponizej stadardowe dla Makefile uzytego dla C++
CXX = g++
CXXFLAGS = -Wall -std=c++17 $(DEBUG)
CPPFLAGS += # pre-processor flags, for include paths etc.

BIN     := .
OBJ     := .
SRC     := .
SRCS    := $(wildcard $(SRC)/*.cpp)
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))
EXE     := $(BIN)/glownyPlik

all: main

clean:
	rm -f *.o glownyPlik
.c.o:
	$(CC) -std=c++17 -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJS)
	$(CC) -std=c++17 $(OBJS) $(LIBS) -o glownyPlik
