/* Auther: Mohamed Khalid Anis*/
/* Date: 14/10/2022*/

#ifndef CARD_H
#define CARD_H

#include "STD_TYPS.h"
typedef struct ST_cardData_t
{
	uint8_t_ cardHolderName[25];
	uint8_t_ primaryAccountNumber[20];
	uint8_t_ cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK_, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif