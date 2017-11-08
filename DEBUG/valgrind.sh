valgrind --tool=helgrind ./lock
valgrind --tool=memcheck -v --leak-check=full ./badloop
