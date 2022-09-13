/*
 * card.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Youssef Elbadri
 */

#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	printf("Enter the Card Holder Name: ");
	fflush(stdout);
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName)<20 || strlen(cardData->cardHolderName)>24)
	{
		return WRONG_NAME;
	}
	else
	{
		return OK_CARD;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
	printf("Enter the Card Expiry Date: ");
	fflush(stdout);
	gets(cardData->cardExpirationDate);
	if (strlen(cardData->cardExpirationDate) != 5 ||
		cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		return OK_CARD;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	printf("Enter the card's Primary Account Number: ");
	fflush(stdout);
	gets(cardData->primaryAccountNumber);
	if(strlen(cardData->primaryAccountNumber) < 16 ||
    	strlen(cardData->primaryAccountNumber) > 19){

		return WRONG_PAN;
	}
	else
	{
		return OK_CARD;
	}
}
