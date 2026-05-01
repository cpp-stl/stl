build: clean
	cmake . -B build && cd build && ln compile_commands.json ../ && make

test: build
	cd build && ./tests/tests

memtest: build
	cd build &&  valgrind --leak-check=yes ./tests/tests -s

clean:
	rm -rf build .cache compile_commands.json