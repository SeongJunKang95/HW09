#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HW09NetBlueprintFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class HW09_API UHW09NetBlueprintFunctionLibary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FString GenerateSecretNumber();

	UFUNCTION(BlueprintCallable)
	static bool IsGuessNumberString(const FString& InNumberString);

	UFUNCTION(BlueprintCallable)
	static FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

};
