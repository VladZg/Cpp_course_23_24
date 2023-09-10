TARGET 		= cache
FLAGS  		=

OBJ_DIR = ../Object
SRC_DIR = ../Source

all: compile link clean

compile:
	@g++ -c -g $(TARGET).cpp $(FLAGS) -o $(OBJ_DIR)/$(TARGET).o

link:
	@g++ $(OBJ_DIR)/*.o -o $(TARGET)

run:
	@./$(TARGET)

clean:
	@rm -f $(OBJ_DIR)/*.o
