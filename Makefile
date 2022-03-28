
BUILD_INFORMATION += -DBUILD_TIME="\"$(shell date +"%d.%m.%Y-%H:%M:%S")\""
BUILD_INFORMATION += -DKERNEL_VERSION="\"$(shell uname -r)\""
BUILD_INFORMATION += -DG++_VERSION="\"$(shell g++ --version | awk 'NR==1{print}' | tr -d '\(\)' | tr ' ' '_')\""

CXX		= g++
CXXFLAGS 	= -fdiagnostics-color=always -std=c++11 -O0 -g -pthread -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CXXFLAGS	+= $(BUILD_INFORMATION)
TARGET_DIR  = ./bin
TARGET	= $(TARGET_DIR)/KVPStorage
SRC_DIR 	= ./src
SRC		= $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
