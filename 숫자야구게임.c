#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 1. 컴퓨터는 총 3개의 랜덤숫자를 뽑음
//   - 랜덤한 숫자 3개는 서로 중복되지 않습니다.
//   - 랜덤한 숫자의 범위 0~9
//   - 중복된 숫자를 뽑았을 때는 난수를 다시 생성
// 2. 플레이어에게는 총 10번의 기회가 있음
// 3. 각 기회마다 1번의 기회를 소모하며,
//    3개의 숫자를 입력할 수 있습니다.
//    이 때, 입력한 숫자가 컴퓨터가 뽑은 숫자의 
//    자리수와 값까지 동일하면 스트라이크
//    자리수는 다르나, 동일한 값이 있다면 볼
//    동일한 값이 하나도 없다면 아웃
//    난수 : 379, 입력 : 386, 결과 : 1st
//                입력 : 396, 결과 : 1st 1ball
//                입력 : 124, 결과 : out
//                입력 : 397, 결과 : 1st 2ball
//                입력 : 379, 결과 : 3st        -> 승리  
// 4. 10번의 기회 안에 컴퓨터가 뽑은 난수 3개의
//    자리수 및 값까지 모두 동일하게 맞춘다면 승리, 아니라면 패배

// 게임에서 사용되는 최대 자리수를 나타내는 상수
// -> 프로젝트 내 빈번하게 사용되는 3이라는 리터럴 값을 미리 상수화함으로써
//    이후, 데이터 변경에 따른 코드의 변경이 필요 없게끔 만듬
const int DIGITS = 6;

// 배열의 원소들을 초기화하는 기능
void InitArray(int* arr);
// 랜덤숫자배열을 생성하는 기능
void GenerateRandNumber(int* arr);
// 플레이어 입력 가이드 출력 기능
void PrintInputGuide(int life, int* arr);
// 플레이어 입력 기능
void Input(int* life, int* arr);
// 결과 확인 후, 출력 기능
int CheckResult(int* randNumbers, int* inputNumbers);

void main()
{
	// 랜덤 시드 설정
	srand(GetTickCount64());

	// 플레이어에게 주어진 기회
	int life = 10;

	// 컴퓨터가 뽑을 랜덤숫자를 저장할 공간
	int* randNumbers = (int*)calloc(DIGITS, sizeof(int));
	// 플레이어가 입력할 숫자를 저장할 공간
	int* inputNumbers = (int*)calloc(DIGITS, sizeof(int));

	// 배열 초기화
	InitArray(randNumbers);
	InitArray(inputNumbers);

	// 난수 생성
	GenerateRandNumber(randNumbers);

	// 게임 로직 반복 (life가 0보다 크다면)
	while (life > 0)
	{
		// 입력 가이드
		PrintInputGuide(life, randNumbers);
		// 입력
		Input(&life, inputNumbers);
		// 결과 확인
		if (CheckResult(randNumbers, inputNumbers))
		{
			// 이 안으로 들어왔다는 뜻은, 3 스트라이크를 했다는 뜻
			// 따라서, 게임 로직을 탈출
			break;
		}
	}

	system("cls");
	printf(life > 0 ? "승리!" : "패배!");

	// 동적할당했던 공간 메모리 해제
	free(randNumbers);
	randNumbers = NULL;
	free(inputNumbers);
	inputNumbers = NULL;
}

void InitArray(int* arr)
{
	for (int i = 0; i < DIGITS; ++i)
		arr[i] = -1;
}

void GenerateRandNumber(int* arr)
{
	for (int i = 0; i < DIGITS; ++i)
	{
		// 0부터 9 사이의 난수 생성
		arr[i] = rand() % 10;

		// 중복 체크
		for (int j = 0; j < i; ++j)
		{
			// 현재 뽑은 난수와 이전에 뽑은 난수가 같은지 비교
			if (arr[i] == arr[j])
			{
				// 중복되므로 난수 생성을 다시 하도록
				--i;
				// 중복된 수를 찾았으므로, 더 이상 확인할 필요 없이
				// 안쪽 for문을 탈출
				break;
			}
		}
	}
}

void PrintInputGuide(int life, int* arr)
{
	system("cls");

	// 테스트하기 편하게 컴퓨터가 뽑은 난수 출력
	printf("컴퓨터가 뽑은 숫자 : ");
	for (int i = 0; i < DIGITS; ++i)
		printf("%d", arr[i]);
	printf("\n");

	printf("남은 기회 : %d \n", life);
	printf("예상되는 수 %d 자리를 입력해주세요.\n", DIGITS);
}

void Input(int* life, int* arr)
{
	for (int i = 0; i < DIGITS; ++i)
	{
		scanf("%d", &arr[i]);

		if (arr[i] < 0 || arr[i] > 9)
		{
			printf("잘못된 입력입니다.\n");
			--i;
		}
		else
		{
			for (int j = 0; j < i; ++j)
			{
				if (arr[i] == arr[j])
				{
					printf("중복된 값입니다.\n");
					--i;
					break;
				}
			}
		}
	}

	// 기회 차감
	--(*life);
}

int CheckResult(int* randNumbers, int* inputNumbers)
{
	int strike = 0;
	int ball = 0;

	for (int i = 0; i < DIGITS; ++i)
	{
		// 스트라이크 확인
		if (randNumbers[i] == inputNumbers[i])
			++strike;
		// 아닐 경우, 볼 확인
		else
		{
			for (int j = 0; j < DIGITS; ++j)
			{
				if (randNumbers[i] == inputNumbers[j])
				{
					++ball;
					break;
				}
			}
		}
	}

	if (strike == 0 && ball == 0)
		printf("Out!");
	else
	{
		if (strike > 0)
			printf("%d Strike ", strike);
		if (ball > 0)
			printf("%d Ball ", ball);
	}
	printf("\n");

	Sleep(1000);

	return strike == DIGITS;
}
