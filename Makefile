run:
	./mybenchmark

dependencies:
	brew tap nlohmann/json
	brew install nlohmann-json

install_benchmark:
	git clone https://github.com/google/benchmark.git
	git clone https://github.com/google/googletest.git benchmark/googletest
	cd benchmark
	cmake -E make_directory "build"
	cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
	cmake --build "build" --config Release

unoptimized:
	g++ -O0 unoptimized_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o
	ar rcs wsd.a output.o
	g++ -O0 benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a

optimized:
	g++ -O0 optimized_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o
	ar rcs wsd.a output.o
	g++ -O0 benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a
