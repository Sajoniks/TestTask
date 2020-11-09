// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatFunctions.h"

//Array of bad words
//Can be updated from server, if needed
static TArray<FString> BadWords = {
	"gay"
	"shit"
	"suck"
	"dick"
	"asshole"
};

/**
 * Simple profanity filter
 * Works only on words from the array above
 * Does not work with plurals
 * @param InText Text to check
 * @out Sanitized text
 */
FText UChatFunctions::BasicProfanityFilter(const FText& InText)
{
	if (!InText.ShouldGatherForLocalization())
	{//Regex doesn't work
	//PHP matcher works fine

	//Beginning of the pattern
		FString Pattern = "(?i)\b(";

		for (auto&& w : BadWords)
		{
			Pattern.Append(w).Append("|");
		}

		//Remove unnecessary '|'
		Pattern = Pattern.LeftChop(1);
		Pattern.Append(")\b");

		FRegexPattern RegexPattern(Pattern);
		FRegexMatcher Matcher(RegexPattern, InText.ToString()); //No matches there

		return FText::FromString("");
	}

	return FText::FromString("");
}

FText UChatFunctions::ProcessLinks(const FText& InText)
{
	if (!InText.ShouldGatherForLocalization())
	{
		FString Message = InText.ToString();

		FRegexPattern Pattern(TEXT(R"((?:http[s]?:\/\/)?www\.[a-z]+\.[a-z]+)"));
		FRegexMatcher Matcher(Pattern, Message);

		int32 MatchCount = 0;
		
		while(Matcher.FindNext())
		{
			int32 Begin = Matcher.GetMatchBeginning();
			int32 End = Matcher.GetMatchEnding();

			MatchCount++;

			Message.InsertAt(Begin+6*(MatchCount-1) + 3*(MatchCount-1), "<link>");
			Message.InsertAt(End+6*MatchCount + 3*(MatchCount-1), R"(</>)");
		}

		return FText::FromString(Message);
	}

	return FText::FromString("");
}
