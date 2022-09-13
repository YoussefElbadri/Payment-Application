/*
 * server.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Youssef Elbadri
 */
#include "server.h"

uint8_t currentAccDB = 0; //Buffering for the current account in processing
uint8_t sequenceNum = 0;

								/*MACRO==255*/
ST_accountsDB_t Arr_accountsDB[DB_MAX] = {
		{5000.0,"7089584563046508"},
		{10500.0,"4015106500293657731"},
		{397773.5,"7439178033376315779"},
		{462405.0,"9500855875135187768"},
		{171145.5,"6680402072820840756"},
		{99305.0,"9973175871990705689"},
		{123252.25,"9877377942721921178"},
		{53450.0,"8070191815795858879"},
		{135502.0,"1190997856658956047"},
		{309412.25,"4476158928824803966"},
};

ST_transaction Arr_transactionsDB[DB_MAX] = {0};

EN_serverError_t isValidAccount(ST_cardData_t *cardData){
	uint8_t PANFlag = 1;
	/* Implementing the account does not exit condition */
	for (int i=0; i <= DB_MAX && PANFlag != 0 ; ++i){
		if (strcmp(Arr_accountsDB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0){
			PANFlag = 0;
			currentAccDB = i;
		}
	}
	if (PANFlag == 0){
		return OK_SERVER;
	}
	else{
		return DECLINED_STOLEN_CARD;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
	if (termData->transAmount <= Arr_accountsDB[currentAccDB].balance){
		return OK_SERVER;
	}
	else{
		return LOW_BALANCE;
	}
}

EN_transStat_t recieveTransactionData(ST_transaction *transData){
	uint8_t validAccountReturn = isValidAccount(&transData->cardHolderData);
	if (validAccountReturn == OK_SERVER){
		uint8_t amountAvailableReturn = isAmountAvailable(&transData->terminalData);
		if (amountAvailableReturn == OK_SERVER){
			Arr_accountsDB[currentAccDB].balance -= transData->terminalData.transAmount;
			transData->transState = APPROVED;
			return APPROVED;
		}
		else if (amountAvailableReturn == LOW_BALANCE){
			transData->transState = DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else if (validAccountReturn == DECLINED_STOLEN_CARD){
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	uint8_t saveTransactionReturn = saveTransaction(&transData);
	sequenceNum++;
	if (saveTransactionReturn == SAVING_FAILED){
		return INTERNAL_SERVER_ERROR;
	}
}

EN_serverError_t saveTransaction(ST_transaction *transData){
	if(sequenceNum > 255){
		return SAVING_FAILED;
	}
	else{
		transData->transactionSequenceNumber=sequenceNum;
		Arr_transactionsDB[sequenceNum] = *transData;
		return OK_SERVER;
	}
}
