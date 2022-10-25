/* Auther: Mohamed Khalid Anis*/
/* Date: 14/10/2022*/

#include "card.h"
#include "STD_TYPS.h"
#include <stdio.h>
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState= OK_;
	uint8_t_ NameSize = 0;
	printf("Please Enter Your Name: ");
	gets(cardData->cardHolderName);
	NameSize = strlen(cardData->cardHolderName);
	if (cardData->cardHolderName == NULL || NameSize > 24 || NameSize < 20)
	{
		ErrorState = WRONG_NAME;
	}
	return ErrorState;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState = OK_;
	uint8_t_ DateSize = 0;
	printf("Please Enter The expiration Date of the Card: ");
	gets(cardData->cardExpirationDate);
	DateSize = strlen(cardData->cardExpirationDate);
	if (cardData->cardExpirationDate == NULL || DateSize != 5 || cardData->cardExpirationDate[2] != '/')
	{
		ErrorState = WRONG_EXP_DATE;
	}
	return ErrorState;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t ErrorState = OK_;
	uint8_t_ PANSize = 0;
	printf("Please Enter the PAN number: ");
	gets(cardData->primaryAccountNumber);
	PANSize = strlen(cardData->primaryAccountNumber);
	if (PANSize < 16 || PANSize > 19)
	{
		ErrorState = WRONG_PAN;
	}
}