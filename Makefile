build:
	cmake . -B build && cd build && ln compile_commands.json ../ && make

test: build
	cd build && ./tests/tests

clean:
	rm -rf build .cache compile_commands.json
