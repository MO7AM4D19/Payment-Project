/* Auther: Mohamed Khalid Anis*/
/* Date: 14/10/2022*/

#include "card.h"
#include "STD_TYPS.h"
#include <stdio.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState= OK;
	uint8_t NameSize = 0;
	printf("Please Enter Your Name: ");
	scanf(" %s", cardData->cardHolderName);
	for (NameSize = 0; NameSize < 25; NameSize++)
	{
		if (cardData->cardHolderName[NameSize] == '\0')
		{
			break;
		}
	}
	if (NameSize == 0 || NameSize == 25 || NameSize < 20)
	{
		ErrorState = WRONG_NAME
	}
	return ErrorState;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState = OK;
	uint8_t DateSize = 0;
	printf("Please Enter The expiration Date of the Card: ");
	scanf(" %s", cardData->cardExpirationDate);
	for (DateSize = 0; DateSize < 6; DateSize++)
	{
		if (cardData->cardExpirationDate[DateSize] == '\0')
		{
			break;
		}
	}
	if (DateSize == 0 || DateSize == 6 || cardData->cardExpirationDate[2] != '/' || )
	{
		ErrorState = WRONG_EXP_DATE;
	}
	return ErrorState;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState = OK;
	uint8_t PANSize = 0;
	printf("Please Enter the PAN number: ");
	scanf(" %s", cardData->primaryAccountNumber);
	for (PANSize = 0; PANSize<19 ; PANSize++)
	{
		if (cardData->primaryAccountNumber[PANSize] == '\0')
		{
			break;
		}
		if (cardData->primaryAccountNumber[PANSize] < '0' || cardData->primaryAccountNumber[PANSize] > '9')
		{
			ErrorState = WRONG_PAN;
		}
	}
	if (PANSize == 0 || PANSize == 19)
	{
		ErrorState = WRONG_PAN;
	}
}