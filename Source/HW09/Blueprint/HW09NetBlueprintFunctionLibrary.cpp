#include "Blueprint/HW09NetBlueprintFunctionLibrary.h"

// 서로 다른 3자리 숫자를 랜덤하게 생성하는 함수
FString UHW09NetBlueprintFunctionLibary::GenerateSecretNumber()
{   
	// 1~9 까지의 숫자를 배열에 추가
	TArray<int32> Numbers; 
	for (int32 i = 1; i <= 9; ++i)
	{
		Numbers.Add(i);
	}
	// 난수 초기화 (현재 시간 기반)
	FMath::RandInit(FDateTime::Now().GetTicks());
	// 배열에서 0이 아닌 숫자만 유지
	Numbers = Numbers.FilterByPredicate([](int32 Num) { return Num > 0; });
	
	FString Result;
	// 3개의 서로 다른 숫자를 선택하여 문자열로 생성
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);// 선택된 숫자는 배열에서 제거 (중복 방지)
	}

	return Result;
}
// 입력된 숫자가 게임 규칙에 맞는지 확인하는 함수
bool UHW09NetBlueprintFunctionLibary::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {
		// 입력된 숫자의 길이가 3이 아니면 유효하지 않음
		if (InNumberString.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		// 입력된 숫자가 1~9 범위에 있고 중복이 없는지 확인
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}
		// 중복된 숫자가 있으면 유효하지 않음
		if (bIsUnique == false)
		{
			break;
		}
		// 모든 조건을 통과하면 유효한 숫자로 인정
		bCanPlay = true;

	} while (false);

	return bCanPlay;
}

FString UHW09NetBlueprintFunctionLibary::JudgeResult(const FString& InSecretNumberString,
	const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	// 입력한 숫자를 정답과 비교하여 스트라이크, 볼, 아웃을 판정하는 함수
	for (int32 i = 0; i < 3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			// 숫자와 위치가 모두 같으면 스트라이크
			StrikeCount++;
		}
		else
		{
			// 위치는 다르지만 정답 숫자에 포함되어 있으면 볼
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	// 스트라이크와 볼이 모두 없는 경우 "OUT" 반환
	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	// 스트라이크, 볼 결과를 문자열로 반환
	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}
