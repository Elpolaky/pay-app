#include"Application.h"
uint8_t another_process(void);
uint8_t c=1;

void main()
{
    while (c==1)
    {
        ST_cardData_t card_data;
        ST_terminalData_t terminal_data;

        uint8_t status=WRONG_NAME;

        /***********************************************************/
        while(status==WRONG_NAME)
        {
            status=getCardHolderName(card_data.cardHolderName);
            printf("invalid name\n");
        }
        if(status==CARD_OK)
        {
            system("cls");
        }

        /***************************************************************/
        status=WRONG_EXP_DATE;
        while(status==WRONG_EXP_DATE)
        {
            status=getCardExpiryDate(card_data.cardExpirationDate);
        }
        if(status==CARD_OK)
        {
            system("cls");
        }

        /***************************************************************/
        status=WRONG_PAN;
        while(status==WRONG_PAN)
        {
            status=getCardPAN(card_data.primaryAccountNumber);
        }
        if(status==CARD_OK)
        {
            system("cls");
        }

        /*****************************************************************/
        status=WRONG_DATE;
        while(status==WRONG_DATE)
        {
            printf("Please enter transaction date:\n");
            status=getTransactionDate(&terminal_data);
        }
        if(status==TERMINAL_OK)
        {
            system("cls");
        }
        /********************************************************************/
        status=isCardExpired(&card_data,&terminal_data);
        if(status==EXPIRED_CARD)
        {
            printf("Declined\n");
            printf("Expired Card");
            //break;
        }
        else
        {
            system("cls");
        }
        /*********************************************************************/
        status=INVALID_AMOUNT;
        printf("Please enter transaction amount");
        while(status==INVALID_AMOUNT)
        {
            status=getTransactionAmount(&terminal_data);
        }

        if(status==TERMINAL_OK)
        {
            status=isBelowMaxAmount(&terminal_data);
            if(status==EXCEED_MAX_AMOUNT)
            {
                printf("Declined Amount\n");
                printf("Exceeding Amount");
            }
            else
            {
                //system("cls");
            }
        }
        /***********************************************************************/
        //update transaction data

        ST_transaction_t *p_transaction_data;
        ST_transaction_t  transaction_data;


        p_transaction_data=&transaction_data;

        strcpy( transaction_data.cardHolderData.cardExpirationDate,card_data.cardExpirationDate);
        //   printf("%s \n",card_data.cardExpirationDate);
        //   printf("%s \n",transaction_data.cardHolderData.cardExpirationDate);

        strcpy(transaction_data.terminalData.transactionDate, terminal_data.transactionDate);
        strcpy(transaction_data.cardHolderData.cardHolderName, card_data.cardHolderName);
         //strcpy(card_data.primaryAccountNumber,"222222222222222222"); for testing

        for (int i=0; i<18; i++)
        {
            transaction_data.cardHolderData.primaryAccountNumber[i]=card_data.primaryAccountNumber[i];
        }



        transaction_data.terminalData.maxTransAmount = terminal_data.maxTransAmount;
        transaction_data.terminalData.transAmount = terminal_data.transAmount;


        //check account status
//

        _isValidAccount= isValidAccount(&card_data,p_account);
        // printf("22222222222222");
        printf("%d",_isValidAccount);
        _isBlockedAccount= isBlockedAccount(p_account);
        // printf("333333333333333333");
        printf("\nblocked :%d\n",_isBlockedAccount);
        _isAmountAvailable= isAmountAvailable(&terminal_data,p_account);
        //  printf("44444444444444");

        // Actions to take according to status
        status=recieveTransactionData(&transaction_data);
        if(status==FRAUD_CARD) printf("Fraud Card process failed");
        else if(status==DECLINED_STOLEN_CARD) printf("Blocked card process failed");
        else if(status==INTERNAL_SERVER_ERROR) printf("process failed");
        else if(status==DECLINED_INSUFFECIENT_FUND) printf("There is no enough Fund process failed");
        else
        {

        }
        saveTransaction(p_transaction_data);

        printf("Do you want to make another process?\n press 1 for yes or 2 for No:");
        c=another_process();
    }
}
// Function declaration to continue another process
uint8_t another_process(void)
{
    uint8_t anotherprocess=0;
    scanf("%d",&another_process);
    if (anotherprocess==2) return 0;
    if (anotherprocess==1) return 1;
    else printf("\nWrong choice please Enter 1 for yes or 2 for No: ");
    another_process();
}
