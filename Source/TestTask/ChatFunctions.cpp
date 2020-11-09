// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatFunctions.h"

//Array of bad words
//Can be updated from server, if needed
static TArray<FString> BadWords = {
	"gay",
	"shit",
	"suck",
	"dick",
	"asshole",
};

/**
 * Simple profanity filter
 * Works only on words from the array above
 * Does not work with plurals
 * @param InText Text to check
 * @out Sanitized text
 */
FString UChatFunctions::BasicProfanityFilter(const FString& InText)
{
	if (!InText.IsEmpty())
	{
	//Beginning of the pattern
		FString Pattern = TEXT(R"((?i)\b()");

		FString Message = InText;

		for (auto&& w : BadWords)
		{
			Pattern.Append(w).Append("|");
		}

		//Remove unnecessary '|'
		Pattern = Pattern.LeftChop(1);
		Pattern.Append(R"()\b)");

		FRegexPattern RegexPattern(Pattern);
		FRegexMatcher Matcher(RegexPattern, Message);
		
		//To keep matcher's offset in sync
		int32 Offset = 0;

		while(Matcher.FindNext())
		{
			int32 Begin = Matcher.GetMatchBeginning()-Offset;
			int32 End = Matcher.GetMatchEnding() - Offset;
			int32 Len = End - Begin;
			Message.RemoveAt(Begin, Len);

			//3 - number of '*'
			Message.InsertAt(Begin, "***");
			Offset += Len - 3;
		}

		return Message;
		
	}

	return InText;
}

/**
* Function that wraps links in message with <link> tag
* Tag is processed in rich text block with hyperlink decorator
* @param InText Text to format
* @out Formatted text
*/
FString UChatFunctions::ProcessLinks(const FString& InText)
{
	if (!InText.IsEmpty())
	{
		FString Message = InText;
		
		//Match links such as
		// http://www.example.com
		// https://www.example.com
		// www.example.com
		FRegexPattern Pattern(TEXT(R"((?:http[s]?:\/\/)?www\.[a-z]+\.[a-z]+)"));
		FRegexMatcher Matcher(Pattern, Message);
		
		//To keep matcher's offset in sync 
		int32 MatchCount = 0;
		
		while(Matcher.FindNext())
		{
			int32 Begin = Matcher.GetMatchBeginning();
			int32 End = Matcher.GetMatchEnding();

			MatchCount++;
			
			//6 - chars in "<link>"
			//3 - chars in "</>
			Message.InsertAt(Begin+6*(MatchCount-1) + 3*(MatchCount-1), "<link>");
			Message.InsertAt(End+6*MatchCount + 3*(MatchCount-1), R"(</>)");
		}

		return Message;
	}

	return InText;
}
