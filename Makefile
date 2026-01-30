# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/myshell

# Source files
SOURCES = $(SRCDIR)/main.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Default target
.PHONY: all
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $(TARGET)"

# Compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Run the program
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
	@echo "Cleaned build artifacts"

# Rebuild from scratch
.PHONY: rebuild
rebuild: clean all

# Help message
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make all      - Build the program (default)"
	@echo "  make run      - Build and run the program"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this help message"