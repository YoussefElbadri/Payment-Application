/*
 * terminal.c
 *
 *  Created on: Aug 15, 2022
 *      Author: Youssef Elbadri
 */
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
	printf("Enter the transaction date: ");
	fflush(stdout);
	gets(termData->transactionDate);

	if (strlen(termData->transactionDate) != 10 ||
		termData->transactionDate[2] != '/' ||
		termData->transactionDate[5] != '/')
		{
			return WRONG_DATE;
		}
	else
	{
		return OK_TERMINAL;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
	/* Checking the large year element (02/"2"2)*/
	if(cardData.cardExpirationDate[3] > termData.transactionDate[8]){
		return OK_TERMINAL;
	}
	else if(cardData.cardExpirationDate[3] == termData.transactionDate[8]){
		/* Checking the small year element (02/2"2")*/
		if(cardData.cardExpirationDate[4] > termData.transactionDate[9]){
			return OK_TERMINAL;
		}
		else if(cardData.cardExpirationDate[4] == termData.transactionDate[9]){
			/* Checking the large month element(0"2"/22)*/
			if(cardData.cardExpirationDate[0] > termData.transactionDate[3]){
				return OK_TERMINAL;
			}
			else if(cardData.cardExpirationDate[0] == termData.transactionDate[3]){
				/* Checking the small month element ("0"2/22)*/
				if(cardData.cardExpirationDate[1] > termData.transactionDate[4]){
					return OK_TERMINAL;
				}
				else {
					return EXPIRED_CARD;
				}
			}
			else{
				return EXPIRED_CARD;
			}
		}
		else{
			return EXPIRED_CARD;
		}
	}
	else{
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	printf("Enter the transaction amount: ");
	fflush(stdout);
	scanf("%f", &termData->transAmount);
	if((termData->transAmount) <= 0.0){
		return INVALID_AMOUNT;
	}
	else{
		return OK_TERMINAL;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
	termData->maxTransAmount = MAX_TRANSCATION_AMOUNT;
	if((termData->maxTransAmount) <= 0.0){
		return INVALID_MAX_AMOUNT;
	}
	else{
		return OK_TERMINAL;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	if((termData->transAmount) > (termData->maxTransAmount)){
			return EXCEED_MAX_AMOUNT;
		}
		else{
			return OK_TERMINAL;
		}
}
