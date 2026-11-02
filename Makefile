.PHONY: all test clean editor client common server build

# Opciones para el CMake
EXTRA_GENERATE ?=
EXTRA_COMPILE ?= -j$(shell nproc)

# Estos son las partidas
HOST ?= localhost
PORT ?= 8080

# Essto es para compilar por primera vez o si cambio algo en algun cmakelist
compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

#Aca compilo para cuando cambio codigo
build:
	cmake --build build/ $(EXTRA_COMPILE)

build-client:
	cmake --build build/ --target taller_client $(EXTRA_COMPILE)

build-server:
	cmake --build build/ --target taller_server $(EXTRA_COMPILE)

# Compila y muestra solo las líneas con error
errors:
	cmake --build build/ $(EXTRA_COMPILE) 2>&1 | grep -E "error|Error" | head -40 || true


run-tests: compile-debug
	./build/taller_tests

run-server: build-server
	./build/taller_server $(PORT)

run-client: build-client
	./build/taller_client $(HOST) $(PORT)

all: clean run-tests

clean:
	rm -Rf build/
