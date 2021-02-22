AVERAGE_COUNT = 10

run:
	./mybenchmark

# average:
# 	@-combined_runtime=0; i=1; while [[ $$i -le ${AVERAGE_COUNT} ]] ; do \
# 		current_runtime=$$(./mybenchmark | grep -m 1 -E -o '[0-9]{5,}' | head -1); \
# 		((combined_runtime = combined_runtime + current_runtime)); \
# 		((i = i + 1)); \
# 	done; echo $$((combined_runtime / ${AVERAGE_COUNT}));


unoptimized:
	g++ -O0 unoptimized_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o
	ar rcs wsd.a output.o
	g++ -O0 benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a

optimized:
	g++ -O0 optimized_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o
	ar rcs wsd.a output.o
	g++ -O0 benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a
