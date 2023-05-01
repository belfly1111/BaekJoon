#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, day = 0;
bool isVisit[1000][1000] = {};
int box[1000][1000] = {};

// bfs에서 4방위를 쉽게 돌기위한 배열
int dx[4] = {1, 0, -1, 0};
int dy[4] = { 0, 1, 0, -1 };

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	queue<pair<int, int>> Q;

	cin >> M >> N;
	
	// 상자 내부의 모든 토마토가 익었는지 확인하는 변수. 전부 익었을 경우 42번째 줄로 이동해 종료한다.
	bool allTomatoRiped = true;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> box[i][j];

			if (box[i][j] == 1)
			{
				isVisit[i][j] = true;
				Q.push({i,j});
			}
			else if (box[i][j] == 0)
			{
				allTomatoRiped = false;
			}
		}
	}

	if (allTomatoRiped)
	{
		cout << 0;
		return 0;
	}

	// bfs 시작, 날짜를 세야한다.
	// 최단거리를 구하는 것도 아니며 각 토마토 별로 사방위를 순회하는 것이기 때문에, 큐를 두 개 만들어 bfs를 진행하였다.
	while (!Q.empty())
	{
		queue<pair<int,int>> curQ;
		
		while (!Q.empty())
		{
			pair<int, int> curPoint = Q.front();
			Q.pop();

			for (int i = 0; i < 4; i++)
			{
				int newX = curPoint.first + dx[i];
				int newY = curPoint.second + dy[i];

				if (newX < 0 || newX >= N) continue;
				if (newY < 0 || newY >= M) continue;

				if (box[newX][newY] == 0 && isVisit[newX][newY] == false)
				{
					curQ.push({ newX, newY });
					box[newX][newY] = 1;
					isVisit[newX][newY] = true;
				}
			}
		}

		Q = curQ;
		day++;
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (box[i][j] == 0)
			{
				cout << -1;
				return 0;
			}
		}
	}


	cout << day-1;
	return 0;
}
