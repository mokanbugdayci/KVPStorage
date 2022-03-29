
BUILD_INFORMATION += -DBUILD_TIME="\"$(shell date +"%d.%m.%Y-%H:%M:%S")\""
BUILD_INFORMATION += -DKERNEL_VERSION="\"$(shell uname -r)\""

# SYS_ARCH = $(shell arch)

# ifdef SYS_ARCH $("x86_64")

CXX			= g++
# CXX		= /mnt/workspace/buildroot-2022.02_first/output/host/usr/bin/arm-linux-g++
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
