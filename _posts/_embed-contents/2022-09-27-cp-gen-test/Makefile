CPP=g++
FLAGS=-std=c++14
BUILD_FOLDER=build

build_cpp = $(CPP) $(FLAGS) $(1).cpp -o $(BUILD_FOLDER)/$(1)

all: \
	$(BUILD_FOLDER) \
	$(BUILD_FOLDER)/check-all-fragments \
	$(BUILD_FOLDER)/slow-solution-example

clean:
	rm -rf $(BUILD_FOLDER)

$(BUILD_FOLDER):
	mkdir -p $(BUILD_FOLDER)/
	
$(BUILD_FOLDER)/%: %.cpp
	$(call build_cpp,$(@F))
	
$(BUILD_FOLDER)/check-all-fragments: slow-solution-example.cpp *.fragment.cpp
	$(call build_cpp,$(@F))

