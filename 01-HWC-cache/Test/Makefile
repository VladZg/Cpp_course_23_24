TARGET 		= test
FLAGS  		=

OBJ_DIR = ../Object
SRC_DIR = ../Source

all: compile link clean

compile:
	@g++ -c $(TARGET).cpp $(FLAGS) -o $(OBJ_DIR)/$(TARGET).o

link:
	@g++ $(OBJ_DIR)/$(TARGET).o -o $(TARGET)

run:
	@./$(TARGET)

clean:
	@rm -f $(OBJ_DIR)/*.o
