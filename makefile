# Directorios
HOME	= .

SRC		= $(HOME)/src
INCLUDE = $(HOME)/include
LIB		= $(HOME)/lib
OBJ		= $(HOME)/obj
BIN		= $(HOME)/bin

# Listas de archivos
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))

# Metadatos
TITLE	= meteroids
AUTHOR  = JesusSalasEstevez
VERSION = 1.0.0


# Objetivo principal
all: begin $(BIN)/$(TITLE)

begin: $(OBJ) $(BIN)
	@echo "[  $(TITLE) - $(AUTHOR) - $(VERSION)  ]"

# Directorios temporales
$(OBJ):
	@mkdir $(OBJ)

$(BIN):
	@mkdir $(BIN)

# Regla general (excepto para main.cpp)
$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.h
	@echo "[+] Compilando $@..."
	@g++ -c $< -o $@ -I$(INCLUDE)

# Regla explícita para main.cpp
$(OBJ)/main.o: $(SRC)/main.cpp
	@echo "[+] Compilando $@..."
	@g++ -c $< -o $@ -I$(INCLUDE)

# Ejecutable
$(BIN)/$(TITLE): $(OBJECTS)
	@echo "[+] Creando ejecutable $(TITLE)..."
	@g++ -o $(BIN)/$(TITLE) $^ -L$(LIB) -lraylib


# Limpieza
.PHONY: clean
clean:
	@echo "[-] Limpiando..."
	@rm -rf $(OBJ) $(BIN)
