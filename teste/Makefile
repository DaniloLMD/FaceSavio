APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic
MULTIPLE_FLAGS= "-Wl,--allow-multiple-definition"

APP = faceSavio

all: _src clean_apps _apps

_src: \
		$(OBJ)/Interface.o \
		$(OBJ)/homeSignals.o \
		$(OBJ)/loginSignals.o \
		$(OBJ)/Post.o \
		$(OBJ)/GerenciadorNotificacoes.o \
		$(OBJ)/Usuario.o 

clean_apps:
	rm -rf $(BIN)/*

_apps: $(BIN)/$(APP)
	$(BIN)/$(APP)

clean:
	rm $(OBJ)/*

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	g++ -c $< -I $(INCLUDE) -o $@ $(GTK_FLAGS) $(MULTIPLE_FLAGS)

$(BIN)/%: $(APPS)/%.cpp
	g++ $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(GTK_FLAGS) $(MULTIPLE_FLAGS)