#include <iostream>
#include <algorithm>
using namespace std;

long long int n;
long long int money;

int coinChart[15] = {};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> money;

	for (int i = 0; i < n; i++) cin >> coinChart[i];


	long long int myBoughtCoin = 0;
	for (int i = 0; ; i++)
	{
		// 마지막 날 전원 매도
		if (i == n - 1)
		{
			money = money + coinChart[i] * myBoughtCoin;
			break;
		}

		// 코인을 매수하지 않았을 때 (살 기회를 노릴 때)
		if (money >= coinChart[i])
		{
			if (coinChart[i] < coinChart[i + 1])
			{
				myBoughtCoin = money / coinChart[i];
				money = money - myBoughtCoin * coinChart[i];
			}
		}

		
		// 코인을 매수했을 때 (팔 기회를 노릴 때)
		else 
		{
			if(coinChart[i] > coinChart[i + 1] && myBoughtCoin > 0)
			{
				money = money + coinChart[i] * myBoughtCoin;
				myBoughtCoin = 0;
			}
		}
	}

	cout << money;
	return 0;
}