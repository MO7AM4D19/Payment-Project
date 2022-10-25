/*Auther: Mohamed Khalid*/
/*Date: 16/10/2022*/
#include "server.h"
#include "terminal.h"
#include "card.h"
#include "STD_TYPS.h"
#include <stdio.h>

ST_accountsDB_t accountsDB[255] = {{ 15000.00,RUNNING,"0361722444373622383" },{ 13000.00,RUNNING,"6262611783938736990" },{ 11000.00,RUNNING,"9039025529153147531" },{ 7000.00,BLOCKED,"5785464868997240940" },{ 3000.00,RUNNING,"2156010875673815628" }};
ST_transaction_t TransactionsDB[255] = { 0 };
uint8_t_ Top = 0;
EN_transStat_t ErrorState_G;

EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t* AccountData = NULL;
	ErrorState_G = APPROVED;
	if (isValidAccount(&(transData->cardHolderData),AccountData) != ACCOUNT_NOT_FOUND)
	{
		if (isBlockedAccount(AccountData) == BLOCKED_ACCOUNT)
		{
			ErrorState_G = DECLINED_STOLEN_CARD;
		}
		else
		{
			if (isAmountAvailable(&(transData->terminalData), AccountData) != SERVER_OK)
			{
				ErrorState_G = DECLINED_INSUFFECIENT_FUND;
			}
		}
	}
	else
	{
		ErrorState_G = FRAUD_CARD;
	}
	if (saveTransaction(transData) == SAVING_FAILED)
	{
		ErrorState_G = INTERNAL_SERVER_ERROR;
	}
	return ErrorState_G;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint8_t_ isEqual = 1;
	EN_serverError_t ErrorState = ACCOUNT_NOT_FOUND;
	for (int i = 0; i < 255; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			isEqual = 1;
			if (cardData->primaryAccountNumber[j] != accountsDB[i].primaryAccountNumber[j])
			{
				isEqual = 0;
				break;
			}
		}
		if (isEqual == 1)
		{
			accountRefrence = &accountsDB[i];
			ErrorState = SERVER_OK;
			break;
		}
	}
	return ErrorState;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t ErrorState = SERVER_OK;
	if (accountRefrence->state == BLOCKED)
	{
		ErrorState = BLOCKED_ACCOUNT;
	}
	return ErrorState;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t ErrorState = SERVER_OK;
	if (termData->transAmount > accountRefrence->balance)
	{
		ErrorState = LOW_BALANCE;
	}
	else
	{
		accountRefrence->balance -= termData->transAmount;
	}
	return ErrorState;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t ErrorState = SERVER_OK;
	if (Top < 255)
	{
		transData->transactionSequenceNumber = Top;
		transData->transState = ErrorState_G;
		TransactionsDB[Top] = *transData;
		Top++;
		listSavedTransactions();
	}
	else
	{
		ErrorState = SAVING_FAILED;
	}
	return ErrorState;

}

void listSavedTransactions(void)
{
	for (int i = 0; TransactionsDB[i].transactionSequenceNumber != 0; i++)
	{
		printf("#############################################\n");
		printf("transaction Sequence Number: %d\n", TransactionsDB[i].transactionSequenceNumber);
		printf("transaction Date: %s\n", TransactionsDB[i].terminalData.transactionDate);
		printf("transaction Amount: %d\n", TransactionsDB[i].terminalData.transAmount);
		printf("transaction state: %d\n", TransactionsDB[i].transState);
		printf("Terminal Max Amount: %d\n", TransactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", TransactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: %d\n", TransactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: %s\n", TransactionsDB->cardHolderData.cardExpirationDate);
		printf("#############################################\n\n");
	}
}
