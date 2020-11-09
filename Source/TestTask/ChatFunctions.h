// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChatFunctions.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API UChatFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Chat")
	static FText BasicProfanityFilter(const FText& InText);

	UFUNCTION(BlueprintCallable, Category = "Chat")
	static FText ProcessLinks(const FText& InText);
};
