/*Auther: Mohamed Khalid Anis*/
/*Date: 15/10/2022*/
#include "terminal.h"
#include "stdio.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorState = OK;
	printf("please enter The current Date: ");
	scanf(" %s", termData->transactionDate);
	if (termData->transactionDate[10] != '\0' || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
	{
		ErrorState = WRONG_DATE;
	}
	return ErrorState;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	EN_cardError_t ErrorState = OK;
	uint8_t TerminalYear, CardYear,TerminalMonth,CardMonth;
	TerminalYear = termData.transactionDate[6]*1000 + termData.transactionDate[7] * 100 + termData.transactionDate[8] * 10 + termData.transactionDate[9];
	CardYear = cardData.cardExpirationDate[3] * 10 + cardData.cardExpirationDate[4] + 2000;
	if (TerminalYear > CardYear)
	{
		ErrorState = EXPIRED_CARD;
	}
	else if(TerminalYear == CardYear)
	{
		TerminalMonth = termData.transactionDate[3] * 10 + termData.transactionDate[4];
		CardMonth = cardData.cardExpirationDate[0] * 10 + cardData.cardExpirationDate[1];
		if (TerminalMonth > CardMonth)
		{
			ErrorState = EXPIRED_CARD;
		}
	}
	return ErrorState;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	EN_terminalError_t ErrorState = OK;
	uint8_t LuhnSum = 0, Temp;
	for (int i = 19; i >= 0; i -= 2)
	{
		Temp = cardData->primaryAccountNumber[i] * 2;
		if (Temp > 9)
		{
			LuhnSum += (Temp % 10) + 1;
		}
		LuhnSum += Temp;
	}
	if (LuhnSum % 10 != 0)
	{
		ErrorState = WRONG_PAN;
	}
	return ErrorState;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorState = OK;
	printf("Please Enter The amount you want to get: ");
	scanf(" %d", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		ErrorState = INVALID_AMOUNT;
	}
	return ErrorState;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorState = OK;
	if (termData->maxTransAmount < termData->transAmount)
	{
		ErrorState = EXCEED_MAX_AMOUNT;
	}
	return ErrorState;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t ErrorState = OK;
	termData->maxTransAmount = 10000;
	if (termData->maxTransAmount < 0)
	{
		ErrorState = INVALID_MAX_AMOUNT;
	}
	return ErrorState;
}