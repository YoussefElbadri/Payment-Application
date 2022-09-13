/*
 * card.h
 *
 *  Created on: Aug 16, 2022
 *      Author: Youssef Elbadri
 */

#ifndef CARD_CARD_H_
#define CARD_CARD_H_

#include "../STD_TYPES.h"
#include <string.h>
#include <stdio.h>

typedef enum EN_cardError_t
{
OK_CARD, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* CARD_CARD_H_ */
