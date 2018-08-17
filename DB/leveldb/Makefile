
all: sample

sample: sample.cpp
	g++ -o $@ $<  -lleveldb -lpthread -lsnappy # -ltcmalloc_minimal

clean:
	rm -f sample
