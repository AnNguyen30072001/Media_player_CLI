CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS = -ltag -lSDL2 -lSDL2_mixer -pthread -lavformat
SRC_DIR = .
FFMPEG_DIR = /usr/include/ffmpeg
BUILD_DIR = build
TARGET = my_media_player

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*/*.cpp)
# Header files
INCS = $(wildcard $(SRC_DIR)/*.h $(SRC_DIR)/*/*/*.h)
# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Include directories
INC_DIRS = -I$(SRC_DIR) -I$(SRC_DIR)/Controller/inc -I$(SRC_DIR)/Model/inc -I$(SRC_DIR)/View/inc -I$(FFMPEG_DIR)

# Run
run: build
	./$(TARGET)

# Compile
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean
