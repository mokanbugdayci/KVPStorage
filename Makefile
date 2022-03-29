
BUILD_INFORMATION += -DBUILD_TIME="\"$(shell date +"%d.%m.%Y-%H:%M:%S")\""
BUILD_INFORMATION += -DKERNEL_VERSION="\"$(shell uname -r)\""

SYS_ARCH = $(shell arch)

# $(shell echo $(SYS_ARCH))

ifeq ($(SYS_ARCH),x86_64)
	CXX = g++
else
	CXX = arm-linux-g++
endif

CXXFLAGS 	= -fdiagnostics-color=always -std=c++11 -O0 -g -pthread -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CXXFLAGS	+= $(BUILD_INFORMATION)
BIN_DIR  	= ./bin
BIN			= $(BIN_DIR)/KVPStorage
SRC_DIR 	= ./src
SRC			= $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)


$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

.PHONY: clean
clean:
	rm -f $(BIN)
