#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int board[51][51] = {};
int saveBoard[51][51] = {};

int N, M, spareVirusSpace = 0, emptyRoom = 0;
int min_second = 999999;

int spreadVirus();

bool isVirusCanAroundRoom = true;

pair<int, int> virusArray[10] = {};
queue<pair<int, int>> Q;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// 17141 과 비슷한 문제이다. 그러나 바이러스의 상태가 비활성화이든 활성화이든 상관없이 연구소의 모든 빈칸을 채우는 최소 시간을 구하는 것이다.

int main()
{
	cin >> N >> M;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	queue<pair<int, int>> virusPoint;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> board[i][j];
			saveBoard[i][j] = board[i][j];

			// 비어 있는 방 개수를 셈. 비활성화되어 있는 바이러스를 제외한 완벽한 빈 칸의 개수만 셈.
			if (board[i][j] == 0) emptyRoom++;

			// 활성화 바이러스가 생길 수 있는 좌표를 저장한다. 
			if (board[i][j] == 2)
			{
				virusPoint.push({ i,j });
				board[i][j] = 2;
				saveBoard[i][j] = 2;
				spareVirusSpace++;
			}
		}
	}

	// 비어있는 칸이 없을 경우 바로 함수를 종료한다.
	if (emptyRoom == 0) {
		cout << 0;
		return 0;
	}

	// 바이러스의 좌표를 virusPoint -> virusArray로 저장함.
	int i = 0;
	while (!virusPoint.empty()) {
		virusArray[i] = virusPoint.front();
		virusPoint.pop();
		i++;
	}

	// 바이러스를 놓을 수 있는 모든 경우의 수를 계산하여 가장 적은 일 수를 출력한다.
	// spreadVirus()함수 내부에서 일 수를 계산하여 비교한다. 이 때, 리턴 값이 '-1'인 경우 방 전체를 다 못채우는것으로 간주한다. 
	// 이 때, 조합을 사용해 -> next_permutation 바이러스 좌표 조합의 수를 구해 브루트포스를 사용한다.

	vector<int> v;
	vector<int> temp;

	// 바이러스가 생길 수 있는 공간의 수만큼 순서대로 넣기
	for (int i = 0; i < spareVirusSpace; i++) v.push_back(i + 1);

	// 바이러스를 놓을 수 있는 최대 개수만큼 1을 넣기
	for (int i = 0; i < M; i++) temp.push_back(1);

	// 나머지를 0으로 채우기
	for (int i = 0; i < spareVirusSpace - M; i++) temp.push_back(0);

	// 오름차순으로 정렬
	sort(temp.begin(), temp.end());


	do
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] == 1)
			{
				int x = virusArray[v[i] - 1].first;
				int y = virusArray[v[i] - 1].second;

				board[x][y] = 2;
				Q.push({ x,y });
			}
		}

		// 바이러스가 완전히 퍼지는 것을 계산하는 함수시작
		int days = spreadVirus();

		if (days != -1) isVirusCanAroundRoom = false;
		if (days < min_second && days != -1) min_second = days;

		// 보드 초기화
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j] = saveBoard[i][j];
			}
		}
		Q = {};

	} while (next_permutation(temp.begin(), temp.end()));



	if (isVirusCanAroundRoom)
	{
		cout << -1;
	}
	else
	{
		cout << min_second;
	}
	return 0;
}

// 바이러스가 방 전체에 퍼지는 초를 계산하는 함수
// 또한 방 전체의 빈공간의 수를 미리 세둔 (변수 : emptyRoom)을 이용해 바이러스가 방전체를 다 돌 수 있는지 판별함.
int spreadVirus() {
	int secondCount = 0;
	int emptyRoomCount = 0;
	bool tempVisit[50][50] = {};


	queue<pair<int, int>> tempQ = Q;
	queue<pair<int, int>> curQ;

	

	// 바이러스가 1초 단위로 퍼지는 것을 고려한다.
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
				if (newY < 0 || newY >= N) continue;

				// 일반적인 빈 공간을 만났을 때 emptyRoomCount 변수를 증가시킨다.
				if (board[newX][newY] == 0 && tempVisit[newX][newY] == false)
				{
					curQ.push({ newX, newY });
					tempVisit[newX][newY] = true;
					board[newX][newY] = 2;
					emptyRoomCount++;
				}

				// 비활성화 상태인 바이러스를 만났을 때 활성화 상태로만 바꿔주고, 빈 방이 아니므로 emptyRoomCount 변수를 증가시키지 않는다.
				if (board[newX][newY] == 2 && tempVisit[newX][newY] == false)
				{
					curQ.push({ newX, newY });
					tempVisit[newX][newY] = true;
				}
			}
		}
		secondCount++;

		// 이 조건문을 넣어주는 이유는, 바이러스의 상태가 활성화든 비활성화든 빈 방만 없으면 조건을 만족하기 때문에 넣은 것이다.
		if (emptyRoomCount == emptyRoom) break;
		if (curQ.empty()) break;

		tempQ = curQ;
		curQ = {};
	}

	// 바이러스가 모든 빈 방을 다 돌았을 경우 반복을 즉시 중지한다.
	if (emptyRoomCount != emptyRoom)
	{
		return -1;
	}

	// 바이러스가 방 전체에 퍼졌을 경우 방을 돈 시간(secondCount)을 리턴
	return secondCount;
}