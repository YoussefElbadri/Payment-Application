/*
 * app.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Youssef Elbadri
 */
#include "application.h"

ST_cardData_t cardDataApp;
ST_terminalData_t termDataApp;
ST_transaction transDataApp;

void appStart(void){
	setMaxAmount(&termDataApp);
	uint8_t cardNameReturn = getCardHolderName(&cardDataApp);
	while (cardNameReturn != OK_CARD){
		printf("Not Valid Card Name\n");
		cardNameReturn = getCardHolderName(&cardDataApp);
	}

	uint8_t cardExpiryDateReturn = getCardExpiryDate(&cardDataApp);
	while (cardExpiryDateReturn != OK_CARD){
		printf("Not Valid Expiration Date in (mm/yy) format\n");
		cardExpiryDateReturn = getCardExpiryDate(&cardDataApp);
	}

	uint8_t cardPANReturn = getCardPAN(&cardDataApp);
	while(cardPANReturn != OK_CARD){
		printf("Not Valid PAN\n");
		cardPANReturn = getCardPAN(&cardDataApp);
	}

	uint8_t transactionDateReturn = getTransactionDate(&termDataApp);
	while(transactionDateReturn != OK_TERMINAL){
		printf("Not Valid Transaction Date in (dd/mm/yyyy) format\n");
		transactionDateReturn = getTransactionDate(&termDataApp);
	}


	uint8_t CardExpiredReturn = isCardExpired(cardDataApp, termDataApp);
	if (CardExpiredReturn != OK_TERMINAL){
		printf("Declined Expired Card");
	}

	else{
		uint8_t TransactionAmountReturn = getTransactionAmount(&termDataApp);
		while(TransactionAmountReturn != OK_TERMINAL){
			printf("Not Valid Amount\n");
			TransactionAmountReturn = getTransactionAmount(&termDataApp);
		}
		uint8_t BelowMaxAmountReturn = isBelowMaxAmount(&termDataApp);
		if (BelowMaxAmountReturn != OK_TERMINAL){
			printf("Declined Amount Exceeding Limit");
		}
		else{
			transDataApp.cardHolderData=cardDataApp;
			transDataApp.terminalData=termDataApp;
			uint8_t transactionReturn = recieveTransactionData(&transDataApp);
			if (transactionReturn == APPROVED){
				printf("Approved");
			}
			else if (transactionReturn == DECLINED_STOLEN_CARD){
				printf("Declined Invalid Account");
			}
			else if (transactionReturn == DECLINED_INSUFFECIENT_FUND){
				printf("Declined Insufficient Funds");
			}

		}
	}
}

int main(){
	appStart();
}

