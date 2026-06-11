CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = Ajedrez

OBJS = Structs_y_Funciones.o \
       Pieza.o               \
       Peon.o                \
       Torre.o               \
       Caballo.o             \
       Alfil.o               \
       Rei.o                 \
       Dama.o                \
       Tablero.o             \
       main.o

# ── Targets principales ────────────────────────────────────────────────────────

.PHONY: all clean rebuild run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(TARGET)

rebuild: clean all

# ── Reglas de compilación ──────────────────────────────────────────────────────

Structs_y_Funciones.o: Structs_y_Funciones.cc Structs_y_Funciones.hh
	$(CXX) $(CXXFLAGS) -c $<

Pieza.o: Pieza.cc Pieza.hh Structs_y_Funciones.hh
	$(CXX) $(CXXFLAGS) -c $<

Peon.o: Peon.cc Peon.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

Torre.o: Torre.cc Torre.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

Caballo.o: Caballo.cc Caballo.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

Alfil.o: Alfil.cc Alfil.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

Rei.o: Rei.cc Rei.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

Dama.o: Dama.cc Dama.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

Tablero.o: Tablero.cc Tablero.hh Peon.hh Torre.hh Caballo.hh Alfil.hh Dama.hh Rei.hh Pieza.hh
	$(CXX) $(CXXFLAGS) -c $<

main.o: main.cc Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

# ── Limpieza ───────────────────────────────────────────────────────────────────

clean:
	rm -f $(TARGET) $(OBJS)