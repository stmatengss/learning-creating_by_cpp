#include <iostream>
#include <boost/coroutine/all.hpp>

void foo(boost::coroutines2::coroutine<void>::push_type & sink){
    std::cout << "a ";
    sink();
    std::cout << "b ";
    sink();
    std::cout << "c ";
}


int main(){
    boost::coroutines2::coroutine<void>::pull_type source(foo);
    std::cout << "1 ";
    source();
    std::cout << "2 ";
    source();
    std::cout << "3 ";
    getchar();
    return 0;
}
