#include"Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t*cardData)
{
    uint8_t size;

    printf("please Enter your name: ");
    gets(cardData->cardHolderName);
    fflush(stdin);

    if(strlen(cardData->cardHolderName)<21)                                    //the condition is less than 21 because this function take into considration the null charecter
    {
        return WRONG_NAME;
    }
    else if(strlen(cardData->cardHolderName)>20 && strlen(cardData->cardHolderName)<=24 )
    {
        return CARD_OK;
    }

    if(strlen(cardData->cardHolderName)>24)                          //
    {
        return WRONG_NAME;
    }
}

/*********************************************************************************************************************************************************/

EN_cardError_t getCardExpiryDate(ST_cardData_t*cardData)
{
    int month1, year1;
    printf("please Enter your expiration date in this format MM/YY: ");
    fflush(stdin);

    scanf(" %s", cardData->cardExpirationDate);
    fflush(stdin);

    sscanf(cardData->cardExpirationDate, "%2d/%2d", &month1, &year1);

    if(strlen(cardData->cardExpirationDate)>5 || strlen(cardData->cardExpirationDate)<5)
    {
        return WRONG_EXP_DATE;
    }
    else
    {
        if(month1 < 1 || month1 > 12 || year1 < 0)                                                      //the first charecter in the month form MM/YY 05/25
        {
            return WRONG_EXP_DATE;
        }

        return CARD_OK;
    }

}

/************************************************************************************************************************************************************/

EN_cardError_t getCardPAN(ST_cardData_t*cardData)
{
    printf("please Enter your PAN: ");
    gets(cardData->primaryAccountNumber);
    fflush(stdin);

    if(strlen(cardData->primaryAccountNumber)>19 || strlen(cardData->primaryAccountNumber)<16)
    {
        return WRONG_PAN;
    }
    else
    {
        return CARD_OK;
    }


}

/************************************************************************************************************************************************************/

void getCardHolderNameTst(void)
{
    ST_cardData_t name;
    uint8_t status=WRONG_NAME;

    while(status==WRONG_NAME)
    {
        status=getCardHolderName(name.cardHolderName);
        printf("invalid name\n");

    }

    if(status==CARD_OK)
    {
        system("cls");
        getCardExpiryDateTest();

    }
}


/****************************************************************************************************************************************************************/

void getCardExpiryDateTest(void)
{
    ST_cardData_t name;
    uint8_t status=WRONG_EXP_DATE;

    while(status==WRONG_EXP_DATE)
    {
        status=getCardExpiryDate(name.cardExpirationDate);
        printf("invalid expiry date\n");

    }

    if(status==CARD_OK)
    {
        system("cls");
        getCardPANTest();

    }
}


/**************************************************************************************************************************************************************/

void getCardPANTest(void)
{
    ST_cardData_t name;
    uint8_t status=WRONG_PAN;

    while(status==WRONG_PAN)
    {
        status=getCardPAN(name.primaryAccountNumber);
        printf("invalid PAN\n");

    }

    if(status==CARD_OK)
    {
        system("cls");

    }
}

/******************************************************************************************************************************************************************/

void CardModuleTest(void)
{
    getCardHolderNameTst();
    printf("all tests have passed successfully ");
}

