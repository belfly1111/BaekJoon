#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

char board[101][101] = {};

int normal_people = 0;
int color_weakness_people = 0;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N; cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
		}
	}
	
	// 일반인 눈에 보이는 구역 bfs 시작
	queue<pair<int, int>> Q;
	bool visit[101][101] = {};
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] == false)
			{
				char cur_color = board[i][j];
				Q.push({ i,j });
				visit[i][j] = true;

				while (!Q.empty())
				{
					pair<int, int> curPoint = Q.front();
					Q.pop();

					for (int i = 0; i < 4; i++)
					{
						int newX = curPoint.first + dx[i];
						int newY = curPoint.second + dy[i];

						if (newX < 0 || newX > N) continue;
						if (newY <0 || newY > N) continue;

						if (board[newX][newY] == cur_color && visit[newX][newY] == false)
						{
							Q.push({ newX, newY });
							visit[newX][newY] = true;
						}
					}
				}
				normal_people++;
			}
		}
	}

	// 기존에 사용했었던 visit 배열초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) visit[i][j] = {};
	}

	// 적록색약인 눈에 보이는 구역 bfs 시작
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (visit[i][j] == false)
			{
				char cur_color = board[i][j];
				Q.push({ i,j });
				visit[i][j] = true;

				while (!Q.empty())
				{
					pair<int, int> curPoint = Q.front();
					Q.pop();

					for (int i = 0; i < 4; i++)
					{
						int newX = curPoint.first + dx[i];
						int newY = curPoint.second + dy[i];

						if (newX < 0 || newX > N) continue;
						if (newY < 0 || newY > N) continue;

						// RED or Green 일 때
						if (cur_color == 'R' || cur_color == 'G')
						{
							if (board[newX][newY] == 'R' || board[newX][newY] == 'G')
							{
								if (visit[newX][newY] == false)
								{
									Q.push({ newX, newY });
									visit[newX][newY] = true;
								}
							}
						}

						// Blue 일 때
						else
						{
							if (board[newX][newY] == cur_color && visit[newX][newY] == false)
							{
								Q.push({ newX, newY });
								visit[newX][newY] = true;
							}
						}
					}
				}
				color_weakness_people++;
			}
		}
	}

	cout << normal_people << ' ' << color_weakness_people;
	return 0;
}