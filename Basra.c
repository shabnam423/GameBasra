#include <stdio.h>

typedef struct
{
    int id; 
    char suit;
    char value; 
}
Card;

int main(void)
{
    Card board[52];
    Card player1[4];
    Card player2[4];
    Card shop[52]; 

    fillShop(shop);


    

    return 0;
}

void fillShop(Card shop[])
{
    char allSuits[4] = {'S', 'H', 'D', 'C'};  // all suits
    char allValues[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'};  // all values

    int shopIndex = 0; 
    int idCounter = 1; 

    for (int i = 0; i < 13; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            Card card; 
            card.id = idCounter; 
            card.suit = allSuits[j];
            card.value = allValues[i];
            shop[shopIndex] = card;
            idCounter++; 
            shopIndex++; 
        }
    }
}

Card findById(Card cards[], int id, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (cards[i].id == id)
        {
            return cards[i];
        }
    }
}

