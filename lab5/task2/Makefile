CC = g++
TARGET = allocator

PREF_SRC = ./src/
PREF_OBJ = .\obj\\

LOGGER_SRC = $(wildcard ./logger/*.cpp)
LOGGER_OBJ = $(patsubst ./logger/%.cpp, $(PREF_OBJ)%.o, $(LOGGER_SRC))
SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ) $(LOGGER_OBJ)
	$(CC) $(OBJ) $(LOGGER_OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) -c $< -o $@

$(PREF_OBJ)%.o : ./logger/%.cpp
	$(CC) -c $< -o $@

clean :
	del $(TARGET).exe $(PREF_OBJ)*.o