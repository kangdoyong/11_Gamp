#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// 난수란?
// 특정한 배열 순서, 규칙을 가지지 않는 연속적인 임의의 수를 의미

// c 에서는 rand() 함수를 이용하여 난수를 생성
// -> stdlib.h 필요

void main()
{
	// 난수 생성 시, 난수 생성에 사용되는 시드값이 고정되어 있기 때문에
	// 프로그램을 재실행해도 이전과 동일한 난수 수열이 출력됨
	// -> 해결방법 : 난수의 시드를 계속해서 변하는 값으로 사용

	// 난수 시드를 설정
	// -> 난수 시드 설정은 프로그램에서 한 번만 호출

	// GetTickCount() : 윈도우가 부팅할 때부터 지난 시간을 밀리초 단위로
	// 반환합니다. windows.h가 필요

	srand(GetTickCount64());

	for (int i = 0; i < 5; ++i)
	{
		// rand() % n
		// 0 ~ n개 사이의 값 중 한 개의 값을 뽑습니다.

		// 난수 시작 값 변경 시 + startNumber;
		printf("%d \n", rand() % 5 + 10);
	}
}