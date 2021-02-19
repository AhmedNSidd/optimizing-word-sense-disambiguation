run:
	./mybenchmark

unoptimized:
	g++ unoptimized_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o
	ar rcs wsd.a output.o
	g++ benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a


optimized:
	g++ optimized_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o
	ar rcs wsd.a output.o
	g++ benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a


	


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
