#include <boost/coroutine/coroutine.hpp>

int main()
{
	using   Coroutine_t = boost::coroutines::symmetric_coroutine<int>;

	Coroutine_t::call_type coro_recv(
		[&](Coroutine_t::yield_type& yield) {
		//loop for recv
		for (;;)
		{
			std::cout << yield.get() << " recv" << endl;
			yield(); //give up time  slice and jump back to starting context
		}
	});

	Coroutine_t::call_type coro_send(
		[&](Coroutine_t::yield_type& yield) {
		//loop for send
		for (;;)
		{
			yield.get();
			std::cout << yield.get() << " send" << endl;
			yield(); 
		}
	});


	while (true)
	{
		coro_recv(1); //recv

		coro_send(1); // send

	}

	system("pause");

	return 0;
}

