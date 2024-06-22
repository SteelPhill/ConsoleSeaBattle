#pragma once

#include <iostream>
using namespace std;


template <typename TValue>
bool TryReadValue(
	TValue* result,
	istream& input,
	const streamsize ignoreCountOnError = 1,
	const int ignoreDelimiterOnError = EOF)
{
	while (true)
	{
		input >> *result;

		if (!input.fail())
			return true;

		if (input.eof())
			return false;

		input.clear();
		input.ignore(ignoreCountOnError, ignoreDelimiterOnError);
	}
}

template <typename TValue>
bool TryReadValue(
	TValue* result,
	istream& input,
	ostream& output,
	const string& inputMessage,
	const string& errorMessage,
	const streamsize ignoreCountOnError = 1,
	const int ignoreDelimiterOnError = EOF)
{
	while (true)
	{
		if (!inputMessage.empty())
			output << inputMessage;

		input >> *result;

		if (!input.fail())
			return true;

		if (input.eof())
			return false;

		input.clear();
		input.ignore(ignoreCountOnError, ignoreDelimiterOnError);

		if (!errorMessage.empty())
			output << errorMessage;
	}
}

template <typename TValue>
TValue CinValue(
	const string& inputMessage = "",
	const string& errorMessage = "Ошибка ввода!\r\n",
	const streamsize ignoreCountOnError = numeric_limits<streamsize>::max(),
	const int ignoreDelimiterOnError = '\n')
{
	TValue value;
	TryReadValue<TValue>(
		&value,
		cin,
		cout,
		inputMessage,
		errorMessage,
		ignoreCountOnError,
		ignoreDelimiterOnError);

	return value;
}

template <typename TValue>
bool TryReadValueInRange(
	TValue* result,
	istream& input,
	const TValue startRange,
	const TValue endRange,
	const streamsize ignoreCountOnError = 1,
	const int ignoreDelimiterOnError = EOF)
{
	while (true)
	{
		bool inputResult =
			TryReadValue<TValue>(
				result,
				input,
				ignoreCountOnError,
				ignoreDelimiterOnError);

		if (inputResult && *result >= startRange && *result <= endRange)
			return true;
	}
}

template <typename TValue>
bool TryReadValueInRange(
	TValue* result,
	istream& input,
	ostream& output,
	const TValue startRange,
	const TValue endRange,
	const string& inputMessage,
	const string& errorMessage,
	const streamsize ignoreCountOnError = 1,
	const int ignoreDelimiterOnError = EOF)
{
	while (true)
	{
		bool inputResult =
			TryReadValue<TValue>(
				result,
				input,
				output,
				inputMessage,
				errorMessage,
				ignoreCountOnError,
				ignoreDelimiterOnError);

		if (inputResult && *result >= startRange && *result <= endRange)
			return true;

		if (!errorMessage.empty())
			output << errorMessage;
	}
}

template <typename TValue>
TValue CinValueInRange(
	const TValue startRange,
	const TValue endRange,
	const string& inputMessage = "",
	const string& errorMessage = "Ошибка ввода!\r\n",
	const streamsize ignoreCountOnError = numeric_limits<streamsize>::max(),
	const int ignoreDelimiterOnError = '\n')
{
	TValue value;
	TryReadValueInRange<TValue>(
		&value,
		cin,
		cout,
		startRange,
		endRange,
		inputMessage,
		errorMessage,
		ignoreCountOnError,
		ignoreDelimiterOnError);

	return value;
}