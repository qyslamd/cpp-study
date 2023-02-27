#include "test.h"

int n = 0;


void count100()
{
	for (int i = 0; i < 100; i++) {
		n++;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Vayne::test()
{
	using namespace std;

	std::thread threads[10];
	for (auto& th : threads) {
		th = std::thread(count100);
	}

	for (auto& th : threads) {
		if (th.joinable()) {
			th.join();
		}
	}

	std::cout << n << "\n";
}