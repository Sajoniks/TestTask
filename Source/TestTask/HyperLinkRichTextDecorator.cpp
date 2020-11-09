// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperLinkRichTextDecorator.h"

#include "Framework/Text/SlateHyperlinkRun.h"
#include "Widgets/Input/SRichTextHyperlink.h"

FRichInlineHyperLinkDecorator::FRichInlineHyperLinkDecorator(URichTextBlock* InOwner,
	UHyperLinkRichTextDecorator* Decorator) :
	FRichTextDecorator(InOwner)
{
	Style = Decorator->Style;
	Delegate.BindLambda([=]()
	{
		Decorator->OnClick(StringLink);
	});
}

bool FRichInlineHyperLinkDecorator::Supports(const FTextRunParseResults& RunInfo, const FString& Text) const
{
	if (RunInfo.Name.Equals("link"))
	{
		const auto& Range = RunInfo.ContentRange;
		
		StringLink = Text.Mid(Range.BeginIndex, Range.EndIndex - Range.BeginIndex);
		return true;
	}

	return false;
}

TSharedPtr<SWidget> FRichInlineHyperLinkDecorator::CreateDecoratorWidget(const FTextRunInfo& RunInfo,
	const FTextBlockStyle& DefaultTextStyle) const
{	
	TSharedPtr<FSlateHyperlinkRun::FWidgetViewModel> Model = MakeShareable(new FSlateHyperlinkRun::FWidgetViewModel);
	TSharedPtr<SRichTextHyperlink> Link = SNew(SRichTextHyperlink, Model.ToSharedRef())
		.Text(FText::FromString(StringLink))
		.Style(&Style)
		.OnNavigate(Delegate);

	return Link;
	
}

TSharedPtr<ITextDecorator> UHyperLinkRichTextDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FRichInlineHyperLinkDecorator{
		InOwner,
		this
	});
}
