#include <iostream>
#include <random>
#include <vector>

// shuffle - random swap
// 5장의 카드가 배열로 있습니다. {1,2,3,4,5}
// 골고루 섞어 봅시다.


int main()
{
	/*srand(time(nullptr));

	for (int i = 0; i < 10; i++)
	{
		std::cout << rand() << std::endl;
	}*/

	std::random_device rd;
	std::mt19937 rand(rd());

	for (int i = 0; i < 10; i++)
	{
		std::cout << rand() % 5 << " ";
	}std::cout << std::endl;

	//균등분포
	std::uniform_int_distribution<> dist(0, 4);
	for (int i = 0; i < 10;i++)
	{
		std::cout << dist(rand) << " ";
	}

	////////////////////////////////////////////////
	std::vector<int> deck{ 1,2,3,4,5,6,7,8,9,10 };

	//for (int i = 0;i < deck.size(); ++i)
	//{
	//	int i1 = dist(rand);
	//	int i2 = dist(rand);
	//	std::swap(deck[i1], deck[i2]);
	//}std::cout << std::endl;

	std::shuffle(deck.begin(), deck.end(), rand);

	for (auto e : deck)
	{
		std::cout << e << " ";
	}std::cout << std::endl;
}

