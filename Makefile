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

Structs_y_Funciones.o: Code/Structs_y_Funciones.cc Header/Structs_y_Funciones.hh
	$(CXX) $(CXXFLAGS) -c $<

Pieza.o: Code/Pieza.cc Header/Pieza.hh Header/Structs_y_Funciones.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Peon.o: Code/Peon.cc Header/Peon.hh Header/Pieza.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Torre.o: Code/Torre.cc Header/Torre.hh Header/Pieza.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Caballo.o: Code/Caballo.cc Header/Caballo.hh Header/Pieza.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Alfil.o: Code/Alfil.cc Header/Alfil.hh Header/Pieza.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Rei.o: Code/Rei.cc Header/Rei.hh Header/Pieza.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Dama.o: Code/Dama.cc Header/Dama.hh Header/Pieza.hh Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

Tablero.o: Code/Tablero.cc Header/Tablero.hh Header/Peon.hh Header/Torre.hh Header/Caballo.hh Header/Alfil.hh Header/Dama.hh Header/Rei.hh Header/Pieza.hh Header/Structs_y_Funciones.hh
	$(CXX) $(CXXFLAGS) -c $<

main.o: Code/main.cc Header/Tablero.hh
	$(CXX) $(CXXFLAGS) -c $<

# ── Limpieza ───────────────────────────────────────────────────────────────────

clean:
	rm -f $(TARGET) $(OBJS)