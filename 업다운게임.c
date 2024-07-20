#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 업다운게임이란?
// 컴퓨터가 임의의 숫자를 뽑은 후,
// 유저가 주어진 기회동안 해당 숫자를 맞추는 게임

// 게임 조건
// 기회는 5번이 주어집니다 (기회가 0이라면 게임오버)
// 프로그램이 시작될 때, 컴퓨터가 처음 한 번 난수를 생성
// 난수는 1이상 100이하의 정수입니다.
// 플레이어가 각 기회마다, 컴퓨터가 뽑은 난수를 맞추기 위해
// 수를 입력하는데, 입력한 값이 난수보다 작다면 UP,
// 크다면 DOWN을 출력합니다.

// 기회 안에 숫자를 맞췄다면 플레이어의 승리
// 승리 or 게임오버 되었을 때, 남은 기회와 컴퓨터가 뽑은 난수를 출력

void main()
{
	// 주어진 기회
	int life = 5;

	// 컴퓨터가 뽑은 난수를 담을 변수
	int randNumber;

	// 랜덤 시드 설정
	srand(GetTickCount64());

	// 난수 생성
	randNumber = rand() % 100 + 1;

	// 플레이어의 기회가 전부 소진되지 않았다면
	// 게임로직을 반복
	while (life > 0)
	{
		// 현재 남은 기회
		printf("남은 기회 : %d \n", life);

		// 플레이어의 입력
		printf("난수를 입력해주세요.\n");
		int input;
		scanf("%d", &input);

		// 결과 확인 후, 출력
		if (input == randNumber)
		{
			printf("정답 !!! \n");
			break;
		}
		else if (input > randNumber)
		{
			printf("DOWN !!! \n");
		}
		else if (input < randNumber)
		{
			printf("UP !!! \n");
		}

		// 해당 라인으로 왔다는 것은, 플레이어가 정답을 못 맞췄다는 뜻
		// 따라서, 기회를 감소
		--life;

		// 1초 딜레이 후, 화면 지우기
		Sleep(1000);
		system("cls");
	}

	system("cls");

	if (life == 0)
	{
		printf("Game Over... \n");
	}
	else
	{
		printf("You Win !!! \n");
	}

	printf("남은 기회 : %d \n", life);
	printf("컴퓨터가 뽑은 난수 : %d \n", randNumber);
}