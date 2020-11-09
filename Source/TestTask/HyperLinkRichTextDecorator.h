// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "HyperLinkRichTextDecorator.generated.h"

class FRichInlineHyperLinkDecorator : public FRichTextDecorator
{
	
public:
	FRichInlineHyperLinkDecorator(URichTextBlock* InOwner, class UHyperLinkRichTextDecorator* Decorator);

	//This decorator handles "link" tag
	bool Supports(const FTextRunParseResults& RunInfo, const FString& Text) const override;

	TSharedPtr<SWidget> CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& DefaultTextStyle) const override;

	//Using UE4 link style
	FHyperlinkStyle Style;

	//Delegate which called on link click
	FSimpleDelegate Delegate;

	//Link
	mutable FString StringLink;
};


UCLASS()
class TESTTASK_API UHyperLinkRichTextDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()

public:

	UHyperLinkRichTextDecorator(const FObjectInitializer& ObjectInitializer):
	URichTextBlockDecorator(ObjectInitializer) {}
	
	TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;


	UPROPERTY(EditAnywhere, Category = "Appearence")
		FHyperlinkStyle Style;

	UFUNCTION(BlueprintImplementableEvent, Category="Action")
		void OnClick(const FString& Link);

};
