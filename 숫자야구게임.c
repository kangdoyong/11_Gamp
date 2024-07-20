#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 1. ��ǻ�ʹ� �� 3���� �������ڸ� ����
//   - ������ ���� 3���� ���� �ߺ����� �ʽ��ϴ�.
//   - ������ ������ ���� 0~9
//   - �ߺ��� ���ڸ� �̾��� ���� ������ �ٽ� ����
// 2. �÷��̾�Դ� �� 10���� ��ȸ�� ����
// 3. �� ��ȸ���� 1���� ��ȸ�� �Ҹ��ϸ�,
//    3���� ���ڸ� �Է��� �� �ֽ��ϴ�.
//    �� ��, �Է��� ���ڰ� ��ǻ�Ͱ� ���� ������ 
//    �ڸ����� ������ �����ϸ� ��Ʈ����ũ
//    �ڸ����� �ٸ���, ������ ���� �ִٸ� ��
//    ������ ���� �ϳ��� ���ٸ� �ƿ�
//    ���� : 379, �Է� : 386, ��� : 1st
//                �Է� : 396, ��� : 1st 1ball
//                �Է� : 124, ��� : out
//                �Է� : 397, ��� : 1st 2ball
//                �Է� : 379, ��� : 3st        -> �¸�  
// 4. 10���� ��ȸ �ȿ� ��ǻ�Ͱ� ���� ���� 3����
//    �ڸ��� �� ������ ��� �����ϰ� ����ٸ� �¸�, �ƴ϶�� �й�

// ���ӿ��� ���Ǵ� �ִ� �ڸ����� ��Ÿ���� ���
// -> ������Ʈ �� ����ϰ� ���Ǵ� 3�̶�� ���ͷ� ���� �̸� ���ȭ�����ν�
//    ����, ������ ���濡 ���� �ڵ��� ������ �ʿ� ���Բ� ����
const int DIGITS = 6;

// �迭�� ���ҵ��� �ʱ�ȭ�ϴ� ���
void InitArray(int* arr);
// �������ڹ迭�� �����ϴ� ���
void GenerateRandNumber(int* arr);
// �÷��̾� �Է� ���̵� ��� ���
void PrintInputGuide(int life, int* arr);
// �÷��̾� �Է� ���
void Input(int* life, int* arr);
// ��� Ȯ�� ��, ��� ���
int CheckResult(int* randNumbers, int* inputNumbers);

void main()
{
	// ���� �õ� ����
	srand(GetTickCount64());

	// �÷��̾�� �־��� ��ȸ
	int life = 10;

	// ��ǻ�Ͱ� ���� �������ڸ� ������ ����
	int* randNumbers = (int*)calloc(DIGITS, sizeof(int));
	// �÷��̾ �Է��� ���ڸ� ������ ����
	int* inputNumbers = (int*)calloc(DIGITS, sizeof(int));

	// �迭 �ʱ�ȭ
	InitArray(randNumbers);
	InitArray(inputNumbers);

	// ���� ����
	GenerateRandNumber(randNumbers);

	// ���� ���� �ݺ� (life�� 0���� ũ�ٸ�)
	while (life > 0)
	{
		// �Է� ���̵�
		PrintInputGuide(life, randNumbers);
		// �Է�
		Input(&life, inputNumbers);
		// ��� Ȯ��
		if (CheckResult(randNumbers, inputNumbers))
		{
			// �� ������ ���Դٴ� ����, 3 ��Ʈ����ũ�� �ߴٴ� ��
			// ����, ���� ������ Ż��
			break;
		}
	}

	system("cls");
	printf(life > 0 ? "�¸�!" : "�й�!");

	// �����Ҵ��ߴ� ���� �޸� ����
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
		// 0���� 9 ������ ���� ����
		arr[i] = rand() % 10;

		// �ߺ� üũ
		for (int j = 0; j < i; ++j)
		{
			// ���� ���� ������ ������ ���� ������ ������ ��
			if (arr[i] == arr[j])
			{
				// �ߺ��ǹǷ� ���� ������ �ٽ� �ϵ���
				--i;
				// �ߺ��� ���� ã�����Ƿ�, �� �̻� Ȯ���� �ʿ� ����
				// ���� for���� Ż��
				break;
			}
		}
	}
}

void PrintInputGuide(int life, int* arr)
{
	system("cls");

	// �׽�Ʈ�ϱ� ���ϰ� ��ǻ�Ͱ� ���� ���� ���
	printf("��ǻ�Ͱ� ���� ���� : ");
	for (int i = 0; i < DIGITS; ++i)
		printf("%d", arr[i]);
	printf("\n");

	printf("���� ��ȸ : %d \n", life);
	printf("����Ǵ� �� %d �ڸ��� �Է����ּ���.\n", DIGITS);
}

void Input(int* life, int* arr)
{
	for (int i = 0; i < DIGITS; ++i)
	{
		scanf("%d", &arr[i]);

		if (arr[i] < 0 || arr[i] > 9)
		{
			printf("�߸��� �Է��Դϴ�.\n");
			--i;
		}
		else
		{
			for (int j = 0; j < i; ++j)
			{
				if (arr[i] == arr[j])
				{
					printf("�ߺ��� ���Դϴ�.\n");
					--i;
					break;
				}
			}
		}
	}

	// ��ȸ ����
	--(*life);
}

int CheckResult(int* randNumbers, int* inputNumbers)
{
	int strike = 0;
	int ball = 0;

	for (int i = 0; i < DIGITS; ++i)
	{
		// ��Ʈ����ũ Ȯ��
		if (randNumbers[i] == inputNumbers[i])
			++strike;
		// �ƴ� ���, �� Ȯ��
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
