objects = test_boost.cpp

calc: $(objects)
	g++ -std=c++11  -o calc $(objects)
	if [ -f "test.txt" ]; then
		echo '123' > test.txt
	else
		touch test.txt
		echo '123' > test.txt
	fi

clean:
	rm calc
