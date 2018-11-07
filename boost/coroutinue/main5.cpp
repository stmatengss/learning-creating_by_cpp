#include <iostream>
#include <boost/coroutine2/all.hpp>
#include <boost/coroutine2/detail/push_coroutine.hpp>
#include <boost/coroutine2/detail/pull_coroutine.hpp>

constexpr int N = 10;

// 方法一：中规中矩
void foo(boost::coroutines2::coroutine<int>::pull_type & sink){
    using coIter = boost::coroutines2::coroutine<int>::pull_type::iterator;
    for (coIter start = begin(sink); start != end(sink); ++start) {
        std::cout << "retrieve "<<*start << "\n";
    }
}
// 方法二：auto自动推导
void foo2(boost::coroutines2::coroutine<int>::pull_type & sink) {
    for (auto val : sink) {
        std::cout << "retrieve " << val << "\n";
    }
}
// 方法三：守旧
void foo3(boost::coroutines2::coroutine<int>::pull_type & sink) {
    for (int i = 0; i < N; i++) {
        std::cout << "retrieve " << sink.get() << "\n";
        sink();
    }
}

int main(){
    boost::coroutines2::coroutine<int>::push_type source(foo2);
    for (int i = 0; i < N; i++) {
        source(i);
    }
    return 0;
}
