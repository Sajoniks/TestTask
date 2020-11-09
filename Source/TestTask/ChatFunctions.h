// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChatFunctions.generated.h"

/** Functions for chat messages formatting
 * 
 */
UCLASS()
class TESTTASK_API UChatFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Chat")
	static FString BasicProfanityFilter(const FString& InText);

	UFUNCTION(BlueprintCallable, Category = "Chat")
	static FString ProcessLinks(const FString& InText);
};
