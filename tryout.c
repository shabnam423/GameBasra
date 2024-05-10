#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    int id;
    char suit;
    char value;
} Card;

void fillShop(Card shop[]);
void dealCards(Card shop[], Card player1[], Card player2[], int* player1NumCards, int* player2NumCards);
int findCardIndex(Card player[], int numCards, char value, char suit);
void playCard(Card player[], int* numCards, char value, char suit);
void printPlayerHand(Card player[], int numCards);

int main(void)
{
    Card board[52];
    Card player1[52];
    Card player2[52];
    Card shop[52];

    fillShop(shop);

    int player1NumCards = 4;
    int player2NumCards = 4;

    while (player1NumCards > 0 && player2NumCards > 0)
    {
        // Player 1's turn
        printf("Player 1's hand: ");
        printPlayerHand(player1, player1NumCards);

        char player1CardValue, player1CardSuit;
        printf("Player 1, enter the value and suit of the card you want to play (e.g., 3S): ");
        scanf(" %c%c", &player1CardValue, &player1CardSuit);
        playCard(player1, &player1NumCards, player1CardValue, player1CardSuit);

        // Check if Player 1 needs more cards
        if (player1NumCards == 0)
        {
            dealCards(shop, player1, player2, &player1NumCards, &player2NumCards);
        }

        // Player 2's turn
        printf("Player 2's hand: ");
        printPlayerHand(player2, player2NumCards);

        char player2CardValue, player2CardSuit;
        printf("Player 2, enter the value and suit of the card you want to play (e.g., 3S): ");
        scanf(" %c%c", &player2CardValue, &player2CardSuit);
        playCard(player2, &player2NumCards, player2CardValue, player2CardSuit);

        // Check if Player 2 needs more cards
        if (player2NumCards == 0)
        {
            dealCards(shop, player1, player2, &player1NumCards, &player2NumCards);
        }
    }

    if (player1NumCards == 0)
    {
        printf("Player 1 wins!");
    }
    else
    {
        printf("Player 2 wins!");
    }

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
        for (int j = 0; j < 4; j++)
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

void dealCards(Card shop[], Card player1[], Card player2[], int* player1NumCards, int* player2NumCards)
{
    srand(time(NULL)); // Seed the random number generator

    // Deal 4 random cards to player1
    for (int i = 0; i < 4; i++)
    {
        int randomIndex = rand() % (52 - i);
        player1[*player1NumCards] = shop[randomIndex];
        (*player1NumCards)++;

        // Remove the dealt card from the shop
        for (int j = randomIndex; j < 51 - i; j++)
        {
            shop[j] = shop[j + 1];
        }
    }

    // Deal 4 random cards to player2
    for (int i = 0; i < 4; i++)
    {
        int randomIndex = rand() % (52 - i - 4);
        player2[*player2NumCards] = shop[randomIndex];
        (*player2NumCards)++;

        // Remove the dealt card from the shop
        for (int j = randomIndex; j < 51 - i - 4; j++)
        {
            shop[j] = shop[j + 1];
        }
    }
}

int findCardIndex(Card player[], int numCards, char value, char suit)
{
    for (int i = 0; i < numCards; i++)
    {
        if (player[i].value == value && player[i].suit == suit)
        {
            return i;
        }
    }
    return -1; // Card not found
}

void playCard(Card player[], int* numCards, char value, char suit)
{
    int cardIndex = findCardIndex(player, *numCards, value, suit);
    if (cardIndex == -1)
    {
        printf("Card not found in your hand.\n");
        return;
    }

    Card playedCard = player[cardIndex];
    printf("Player played: %c%c\n", playedCard.value, playedCard.suit);

    // Remove the played card from the player's hand
    for (int i = cardIndex; i < *numCards - 1; i++)
    {
        player[i] = player[i + 1];
    }
    (*numCards)--;
}

void printPlayerHand(Card player[], int numCards)
{
    for (int i = 0; i < numCards; i++)
    {
        printf("%c%c ", player[i].value, player[i].suit);
    }
    printf("\n");
}
