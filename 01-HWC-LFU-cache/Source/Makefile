TARGET 		= cache
FLAGS  		=

OBJ_DIR = Object
SRC_DIR = Source

all: make_directory compile link remove_directory

make_directory:
	@mkdir -p $(OBJ_DIR)

compile:
	@g++ -c -g $(SRC_DIR)/$(TARGET).cpp $(FLAGS) -o $(OBJ_DIR)/$(TARGET).o

link:
	@g++ $(OBJ_DIR)/*.o -o $(TARGET)

run:
	@./$(TARGET)

remove_directory:
	@rm -r $(OBJ_DIR)
