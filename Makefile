run_v2:
	./output_v2

run_v1:
	./output_v1

dependencies:
	brew tap nlohmann/json
	brew install nlohmann-json
	brew install libomp
	@echo "If the above command didn't work, please figure out how to install it on your system: https://github.com/nlohmann/json. You might need to run sudo apt-get install nlohmann-json3-dev if you're working on linux "

install_benchmark:
	git clone https://github.com/google/benchmark.git
	git clone https://github.com/google/googletest.git benchmark/googletest
	cd benchmark
	cmake -E make_directory "build"
	cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
	cmake --build "build" --config Release

unoptimized_v2:
	g++ unoptimized_wsd_v2.cpp -I/usr/local/Cellar/nlohmann-json/3.9.1_1/include -std=c++11 -o output_v2

optimized_v2:
	g++ -Xpreprocessor -fopenmp optimized_wsd_v2.cpp -lomp -I/usr/local/Cellar/nlohmann-json/3.9.1_1/include -std=c++11 -o output_v2

unoptimized_v1:
	g++ unoptimized_wsd_v1.cpp -I/usr/local/Cellar/nlohmann-json/3.9.1_1/include -std=c++11 -o output_v1

optimized_v1:
	g++ optimized_wsd_v1.cpp -I/usr/local/Cellar/nlohmann-json/3.9.1_1/include -std=c++11 -o output_v1
