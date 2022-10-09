CPP=g++
FLAGS=-std=c++14
BUILD_FOLDER=build

build_cpp = $(CPP) $(FLAGS) $(1).cpp -o $(BUILD_FOLDER)/$(1)

all: \
	$(BUILD_FOLDER) \
	$(BUILD_FOLDER)/check-all-fragments \
	$(BUILD_FOLDER)/slow-solution \
	$(BUILD_FOLDER)/fast-solution \
	$(BUILD_FOLDER)/template-1-gen-and-check

clean:
	rm -rf $(BUILD_FOLDER)
	rm *.inp
	rm *.out

$(BUILD_FOLDER):
	mkdir -p $(BUILD_FOLDER)/
	
$(BUILD_FOLDER)/%: %.cpp
	$(call build_cpp,$(@F))
	
$(BUILD_FOLDER)/check-all-fragments: check-all-fragments.cpp *.fragment.cpp
	$(call build_cpp,$(@F))
	
run-template-1-gen-and-check: $(BUILD_FOLDER)/template-1-gen-and-check $(BUILD_FOLDER)/slow-solution $(BUILD_FOLDER)/fast-solution
	cd build && ./template-1-gen-and-check

