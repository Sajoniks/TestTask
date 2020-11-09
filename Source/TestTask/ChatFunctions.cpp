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
 * Is not localized
 * @param InText Text to check
 * @out Sanitized text
 */
FText UChatFunctions::BasicProfanityFilter(const FText& InText)
{
	//Regex doesn't work
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
