#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int board[10][10] = {};
int saveBoard[10][10] = {};

int N, M, safeZone = 0;
int spreadVirus();

queue<pair<int, int>> Q;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			saveBoard[i][j] = board[i][j];

			if (board[i][j] == 0) safeZone++;
			else if (board[i][j] == 2) Q.push({ i,j });
		}
	}

	// 브루트 포스를 사용해서 바이러스를 가장 잘 막는 경우를 뽑는다.
	// 64 * 63 * 62 * 64 = 15,998,976 정도 이기 때문에 충분히 가능하다.

	// 3중 반복문을 통해 모든 경우의 수를 구한다. 
	// 조합 중복은 고려하지 않는다.
	int answer = 0;
	for (int a = 0; a < N; a++) 
	{
		for (int b = 0; b < M; b++) 
		{
			if (board[a][b] != 0) continue;
			for (int c = 0; c < N; c++)
			{
				for (int d = 0; d < M; d++)
				{
					if (board[c][d] != 0) continue;
					else if (c == a && d == b) continue;

					for (int e = 0; e < N; e++)
					{
						for (int f = 0; f < M; f++)
						{
							if (board[e][f] != 0) continue;
							else if (e == a && f == b) continue;
							else if (e == c && f == d) continue;
						

							board[a][b] = 1;
							board[c][d] = 1;
							board[e][f] = 1;

							int safeZone = spreadVirus();
							if (answer < safeZone) answer = safeZone;

							// 보드 초기화
							for (int i = 0; i < N; i++) {
								for (int j = 0; j < M; j++) {
									board[i][j] = saveBoard[i][j];
								}
							}
						}
					}
				}
			}
		}
	}

	cout << answer;
	return 0;
}

// 바이러스가 전부퍼지고 남아있는 safeZone의 개수를 반환한다.
int spreadVirus() {
	int virusCount = 0;
	bool tempVisit[8][8] = {};

	queue<pair<int, int>> tempQ = Q;
	queue<pair<int, int>> curQ;

	// 바이러스가 한 번에 사방위씩만 퍼지니 그것을 고려한다.
	while (true)
	{
		while (!tempQ.empty())
		{
			pair<int, int> curVirus = tempQ.front();
			tempQ.pop();
			tempVisit[curVirus.first][curVirus.second] = true;

			for (int i = 0; i < 4; i++)
			{
				int newX = curVirus.first + dx[i];
				int newY = curVirus.second + dy[i];

				if (newX < 0 || newX >= N) continue;
				if (newY < 0 || newY >= M) continue;

				if (board[newX][newY] == 0 && tempVisit[newX][newY] == false)
				{
					curQ.push({ newX, newY });
					tempVisit[newX][newY] = true;
					board[newX][newY] = 2;
					virusCount++;
				}
			}
		}
		if (curQ.empty()) break;

		tempQ = curQ;
		curQ = {};
	}

	// 벽의 개수가 3개 고정이므로 그것도 고려해서 빼준다.
	return safeZone - virusCount - 3;
}