/*Auther: Mohamed Khalid */
/*Date: 17/10/2022*/

#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"
#include <stdio.h>
void main()
{
	appStart();
}

void appStart(void)
{
	while (1)
	{
		ST_cardData_t Card;
		ST_terminalData_t Terminal;
		ST_transaction_t Transaction;
		ST_accountsDB_t* Account;
		//setMaxAmount(&Terminal);
		getCardHolderName(&Card);
		getCardExpiryDate(&Card);
		getCardPAN(&Card);
		getTransactionDate(&Terminal);
		if (isValidCardPAN(&Card) == WRONG_PAN)
		{
			printf("The Transaction is declined, Wrong PAN");
			continue;
		}
		if (isCardExpired(Card, Terminal) == EXPIRED_CARD)
		{
			printf("The transaction is declined, The card is expired");
			continue;
		}
		getTransactionAmount(&Terminal);
		if (isBelowMaxAmount(&Terminal) == EXCEED_MAX_AMOUNT)
		{
			printf("The transaction is declined, Exceeded The max amount");
				continue;
		}
		recieveTransactionData(&Transaction);
		if (isValidAccount(&Card, Account) == ACCOUNT_NOT_FOUND)
		{
			printf("The transaction is declined, The Account couldn't be found");
			continue;
		}
		if (isBlockedAccount(Account) == BLOCKED_ACCOUNT)
		{
			printf("The transaction is declined, The account is blocked");
			continue;
		}
		if (isAmountAvailable(&Terminal,Account) == LOW_BALANCE)
		{
			printf("The transaction is declined, Low balance");
			continue;
		}
		saveTransaction(&Transaction);
	}
}