#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <string.h>

struct card
{
    char suitName[9];
    char suit[1];
    int cardNum;
    int cardValue;
    char cardName[18];
    int indexNum;
    bool isAce;
};

void Menu(bool& _debug, bool& _play, bool& _quit);
void CreateShuffledDeck(card _deck[]);
void PlayRound(card _deck[], int& _i, int& _bettingTokens, bool debug);

int main()
{
    std::cout << "Welcome to my BlackJack game!" << std::endl;
    std::cin.get();

    card deck[52] = { 0 };
    
    bool debug = false;
    bool play = false;
    bool quit = false;

    while (quit == false)
    {
        Menu(debug, play, quit);

        if (play)
        {
            int i = 0;
            int bettingTokens = 1000;
            CreateShuffledDeck(deck);

            while (i < 52)
            {
                if (i >= 46)
                {
                    std::cout << "Sorry, it looks like we won't have enough cards in the deck to play another round" << std::endl;
                    i = 52;
                    std::cin.get();
                }
                else if (bettingTokens <= 0)
                {
                    std::cout << "You have ran out of betting tokens! Game over" << std::endl;
                    std::cin.get();
                    i = 52;
                }
                else
                {
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                    std::cout << std::endl;
                    PlayRound(deck, i, bettingTokens, debug);
                    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                    std::cout << std::endl;
                }
            }

            if (bettingTokens != 0)
            {
                std::cout << "You finished with " << bettingTokens << " betting tokens" << std::endl;
                std::cin.get();
            }
        }
    }
    
    std::cout << "Thanks for playing!" << std::endl;
    std::cin.get();
}

void Menu(bool& _debug, bool& _play, bool& _quit)
{
    bool valid = false;
    while (valid == false)
    {
        _play = false;
        _quit = false;

        char ans[2] = { 0 };
        std::cout << "Would you like to Play, get Instructions on how to play, toggle the Debug flag, or Quit? (P/I/D/Q): ";
        std::cin.getline(ans, 2);
        std::cout << std::endl;

        if (ans[0] == 'P' || ans[0] == 'p')
        {
            valid = true;
            _play = true;
        }
        else if (ans[0] == 'I' || ans[0] == 'i')
        {
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << std::endl;
            std::cout << "BlackJack is a popular casino game in which you bet tokens." << std::endl;
            std::cin.get();
            std::cout << "The aim of the game is to get a hand that is closest to 21, but doesn't go over 21." << std::endl;
            std::cin.get();
            std::cout << "You will play against the dealer, who has the same actions available to them as you." << std::endl;
            std::cin.get();
            std::cout << "The dealer will always choose to draw a card unless they are on 17 or above." << std::endl;
            std::cin.get();
            std::cout << "You play by asking to draw a card or stick when prompted." << std::endl;
            std::cin.get();
            std::cout << "Cards are worth their face value, all picture cards are worth 10." << std::endl;
            std::cin.get();
            std::cout << "The Ace is worth either 11 or 1. To make it easier for you, the program will make the Ace's value 11, unless you go bust, where we'll make it a 1 for you." << std::endl;
            std::cin.get();
            std::cout << "You also have tokens to bet. You start with 1000. If you lose, your tokens will be lost too. If you win, your tokens will be returned to you and doubled." << std::endl;
            std::cin.get();
            std::cout << "Also note that the deck shuffles each time you exit the current game you're playing." << std::endl;
            std::cout << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << std::endl;
        }
        else if (ans[0] == 'D' || ans[0] == 'd')
        {
            if (_debug == false)
            {
                _debug = true;
                std::cout << "Debug mode on" << std::endl;
                std::cin.get();
            }
            else
            {
                _debug = false;
                std::cout << "Debug mode off" << std::endl;
                std::cin.get();
            }
        }
        else if (ans[0] == 'Q' || ans[0] == 'q')
        {
            valid = true;
            _quit = true;
        }
        else
        {
            std::cout << "That is not a valid option, please try again" << std::endl;
            std::cin.get();
        }
    }
}

void CreateShuffledDeck(card _deck[])
{
    bool sameNum = false;
    int randNum = 0;
    int suitNum = 0;

    for (int i = 0; i < 52; i++)
    {
        _deck[i].indexNum = 0;
    }

    srand(time(0));

    for (int i = 0; i < 52; i++)
    {
        do
        {
            randNum = 1 + rand() % 52;

            for (int y = 0; y < 52; y++)
            {
                if (randNum == _deck[y].indexNum)
                {
                    sameNum = true;
                    y = 52;
                }
                else
                {
                    sameNum = false;
                }
            }
        } while (sameNum);

        _deck[i].indexNum = randNum;

        suitNum = ((_deck[i].indexNum - 1) / 13) + 1;

        if (suitNum == 1)
        {
            _deck[i].suit[1] = 'C';
            strcpy_s(_deck[i].suitName, "Clubs");
        }
        else if (suitNum == 2)
        {
            _deck[i].suit[1] = 'D';
            strcpy_s(_deck[i].suitName, "Diamonds");
        }
        else if (suitNum == 3)
        {
            _deck[i].suit[1] = 'H';
            strcpy_s(_deck[i].suitName, "Hearts");
        }
        else if (suitNum == 4)
        {
            _deck[i].suit[1] = 'S';
            strcpy_s(_deck[i].suitName, "Spades");
        }

        if (_deck[i].indexNum <= 13)
        {
            _deck[i].cardNum = _deck[i].indexNum;
        }
        else if (_deck[i].indexNum <= 26)
        {
            _deck[i].cardNum = _deck[i].indexNum - 13;
        }
        else if (_deck[i].indexNum <= 39)
        {
            _deck[i].cardNum = _deck[i].indexNum - 26;
        }
        else
        {
            _deck[i].cardNum = _deck[i].indexNum - 39;
        }

        if ((_deck[i].cardNum == 11) ||
            (_deck[i].cardNum == 12) ||
            (_deck[i].cardNum == 13))
        {
            _deck[i].cardValue = 10;
        }
        else if (_deck[i].cardNum == 1)
        {
            _deck[i].cardValue = 11;
            _deck[i].isAce = true;
        }
        else
        {
            _deck[i].cardValue = _deck[i].cardNum;
        }

        if (_deck[i].cardNum == 1)
        {
            strcpy_s(_deck[i].cardName, "Ace of ");
            strcat_s(_deck[i].cardName, _deck[i].suitName);
        }
        else if (_deck[i].cardNum == 11)
        {
            strcpy_s(_deck[i].cardName, "Jack of ");
            strcat_s(_deck[i].cardName, _deck[i].suitName);
        }
        else if (_deck[i].cardNum == 12)
        {
            strcpy_s(_deck[i].cardName, "Queen of ");
            strcat_s(_deck[i].cardName, _deck[i].suitName);
        }
        else if (_deck[i].cardNum == 13)
        {
            strcpy_s(_deck[i].cardName, "King of ");
            strcat_s(_deck[i].cardName, _deck[i].suitName);
        }
        else
        {
            char temp[3] = { 0 };
            _itoa_s(_deck[i].cardNum, temp, 10);
            strcpy_s(_deck[i].cardName, temp);
            strcat_s(_deck[i].cardName, " of ");
            strcat_s(_deck[i].cardName, _deck[i].suitName);
        }
    }   
}

void PlayRound(card _deck[], int& _i, int& _bettingTokens, bool _debug)
{
    card playerHand[11] = { 0 };
    card dealerHand[11] = { 0 };
    int playerHandValue = 0;
    int dealerHandValue = 0;
    
    int playerBet = 0;
    bool valid = false;
    while (valid == false)
    {
        char check[10] = { 0 };
        std::cout << "You have " << _bettingTokens << " betting tokens" << std::endl;
        std::cout << "How much would you like to bet?: ";
        std::cin.getline(check, '\n');
        std::cout << std::endl;

        bool isNum = false;
        for (int i = 0; i < strlen(check); i++)
        {
            if (isdigit(check[i]))
            {
                isNum = true;
            }
        }

        if (isNum == true)
        {
            playerBet = atoi(check);

            if (playerBet > _bettingTokens)
            {
                std::cout << "You don't have enough tokens to make that bet" << std::endl;
                std::cin.get();
            }
            else if (playerBet == 0)
            {
                std::cout << "You must make a bet to play" << std::endl;
                std::cin.get();
                playerBet = 0;
            }
            else if (playerBet < 0)
            {
                std::cout << "You can't bet a negative amount of tokens" << std::endl;
                std::cin.get();
            }
            else
            {
                valid = true;
            }
        }
        else
        {
            std::cout << "You must enter a number" << std::endl;
            std::cin.get();
        }
    }

    int playerAces = 0;
    int dealerAces = 0;

    playerHand[0] = _deck[_i];
    if (_deck[_i].isAce == true)
    {
        playerAces = playerAces + 1;
    }
    playerHandValue = playerHandValue + playerHand[0].cardValue;
    _i++;

    dealerHand[0] = _deck[_i];
    if (_deck[_i].isAce == true)
    {
        dealerAces = dealerAces + 1;
    }
    dealerHandValue = dealerHandValue + dealerHand[0].cardValue;
    _i++;

    playerHand[1] = _deck[_i];
    if (_deck[_i].isAce == true)
    {
        playerAces = playerAces + 1;
    }
    playerHandValue = playerHandValue + playerHand[1].cardValue;
    _i++;

    dealerHand[1] = _deck[_i];
    if (_deck[_i].isAce == true)
    {
        dealerAces = dealerAces + 1;
    }
    dealerHandValue = dealerHandValue + dealerHand[1].cardValue;
    _i++;

    if (playerAces == 2)
    {
        playerHandValue = 11;
        playerAces = playerAces - 1;
    }

    if (dealerAces == 2)
    {
        dealerHandValue = 11;
        dealerAces = dealerAces - 1;
    }

    std::cout << "Dealer has:" << std::endl;
    std::cout << dealerHand[0].cardName << std::endl;
    if (_debug)
    {
        std::cout << dealerHand[1].cardName << std::endl;
        std::cout << "Dealers total is: " << dealerHandValue << std::endl;
    }
    else
    {
        std::cout << "And one hidden card" << std::endl;
    }
    std::cin.get();

    std::cout << "Player has:" << std::endl;
    std::cout << playerHand[0].cardName << std::endl;
    std::cout << playerHand[1].cardName << std::endl;
    std::cout << "Your total is: " << playerHandValue << std::endl;
    std::cin.get();
    
    bool playerBlackjack = false;  

    if (playerHandValue == 21)
    {
        std::cout << "You got BlackJack!" << std::endl;
        std::cin.get();
        std::cout << "If the dealer got BlackJack too, this round will be a draw" << std::endl;
        std::cin.get();
        playerBlackjack = true;
    }

    if (_debug)
    {
        bool valid = false;
        while (valid == false)
        {
            char outputCards[2] = { 0 };
            std::cout << "Would you like to output the next 8 cards? (Y/N): ";
            std::cin.getline(outputCards, 2);
            std::cout << std::endl;


            if (outputCards[0] == 'Y' || 
                outputCards[0] == 'y')
            {
                valid = true;

                int i = 0;
                _i = i;
                for (int y = 0; y < 8; y++)
                {
                    std::cout << _deck[i].cardName << std::endl;
                    i++;
                }
                std::cout << std::endl;
            }
            else if (outputCards[0] == 'N' || 
                outputCards[0] == 'n')
            {
                valid = true;
            }
            else
            {
                std::cout << "That is not a valid option, please try again" << std::endl;
                std::cin.get();
            }
        }
    }

    int playerDeckNum = 2;
    bool playerStick = false;
    bool playerBust = false;

    if (playerBlackjack == false)
    {
        do
        {
            char drawOrStick[2] = { 0 };
            std::cout << "Would you like to Draw another card or Stick? (D/S): ";
            std::cin.getline(drawOrStick, 2);
            std::cout << std::endl;

            if (drawOrStick[0] == 'S' || 
                drawOrStick[0] == 's')
            {
                playerStick = true;
                std::cout << "Your score for the dealer to beat is " << playerHandValue << std::endl;
                std::cin.get();
            }
            else if (drawOrStick[0] == 'D' || 
                drawOrStick[0] == 'd')
            {
                playerHand[playerDeckNum] = _deck[_i];
                if (_deck[_i].isAce == true)
                {
                    playerAces = playerAces + 1;
                }
                playerHandValue = playerHandValue + playerHand[playerDeckNum].cardValue;
                _i++;
                std::cout << "The card you drew was " << playerHand[playerDeckNum].cardName << std::endl;
                std::cin.get();
                playerDeckNum = playerDeckNum + 1;
                if (playerHandValue > 21 && playerAces > 0)
                {
                    playerHandValue = playerHandValue - 10;
                    playerAces = playerAces - 1;
                    std::cout << "Your ace value has been changed from 11 to 1 because you went over 21" << std::endl;
                    std::cin.get();
                }
                std::cout << "Your new total is: " << playerHandValue << std::endl;
                std::cin.get();

                if (playerHandValue > 21)
                {
                    std::cout << "Bust!" << std::endl;
                    std::cin.get();
                    playerBust = true;
                }
            }
            else
            {
                std::cout << "That is not a valid option, please try again" << std::endl;
                std::cin.get();
            }
        } while (playerHandValue < 21 && 
            playerStick == false);
    }

    if (playerHandValue == 21)
    {
        std::cout << "We'll stick on 21 for you!" << std::endl;
        std::cin.get();
    }

    std::cout << std::endl;
    std::cout << "The dealers hidden card was " << dealerHand[1].cardName << std::endl;
    std::cin.get();
    std::cout << "The dealers total is: " << dealerHandValue << std::endl;
    std::cin.get();

    bool dealerBlackjack = false;
    if (dealerHandValue == 21)
    {
        std::cout << "Dealer got BlackJack!" << std::endl;
        std::cin.get();
        dealerBlackjack = true;
    }

    int dealerDeckNum = 2;
    bool dealerBust = false;
    bool dealerStick = false;

    if (!dealerBlackjack && !playerBlackjack)
    {
        do
        {
            if (dealerHandValue >= 17)
            {
                std::cout << "Dealer is sticking" << std::endl;
                std::cin.get();
                dealerStick = true;
            }
            else
            {
                std::cout << "Dealer is drawing a card" << std::endl;
                std::cin.get();

                dealerHand[dealerDeckNum] = _deck[_i];
                if (_deck[_i].isAce == true)
                {
                    dealerAces = dealerAces + 1;
                }
                dealerHandValue = dealerHandValue + dealerHand[dealerDeckNum].cardValue;
                _i++;
                std::cout << "The card dealer drew was " << dealerHand[dealerDeckNum].cardName << std::endl;
                std::cin.get();
                dealerDeckNum = dealerDeckNum + 1;
                if (dealerHandValue > 21 && dealerAces > 0)
                {
                    dealerHandValue = dealerHandValue - 10;
                    dealerAces = dealerAces - 1;
                    std::cout << "The dealers ace value has been changed from 11 to 1 because they went over 21" << std::endl;
                    std::cin.get();
                }
                std::cout << "Dealers new total is: " << dealerHandValue << std::endl;
                std::cin.get();

                if (dealerHandValue > 21)
                {
                    std::cout << "Dealer is bust!" << std::endl;
                    std::cin.get();
                    dealerBust = true;
                }
            }
        } while (dealerHandValue < 21 && dealerStick == false);
    }

    if (dealerBlackjack && playerBlackjack)
    {
        std::cout << "Both players got BlackJack, so it is a draw" << std::endl;
        std::cin.get();
        std::cout << "Betting tokens have been returned to you. You still have " << _bettingTokens << std::endl;
        std::cin.get();
    }
    else if ((playerBust && !dealerBust) || dealerBlackjack || (dealerHandValue > playerHandValue && !dealerBust))
    {
        std::cout << "Dealer wins!" << std::endl;
        std::cin.get();

        _bettingTokens = _bettingTokens - playerBet;
        std::cout << "You lose " << playerBet << std::endl;
        std::cout << "You have " << _bettingTokens << " betting tokens" << std::endl;
        std::cin.get();
    }
    else if ((dealerBust && !playerBust) || playerBlackjack || (playerHandValue > dealerHandValue && !playerBust))
    {
        std::cout << "Player wins!" << std::endl;
        std::cin.get();

        _bettingTokens = _bettingTokens + playerBet;
        std::cout << "Your bet of " << playerBet << " has been doubled and given back to you" << std::endl;
        std::cout << "You have " << _bettingTokens << " betting tokens" << std::endl;
        std::cin.get();
    }
    else if (playerBust && dealerBust)
    {
        std::cout << "Both players went bust, so it is a draw" << std::endl;
        std::cin.get();
        std::cout << "Betting tokens have been returned to you. You still have " << _bettingTokens << std::endl;
        std::cin.get();
    }
    else
    {
        std::cout << "Both players stuck on the same number, so it is a draw" << std::endl;
        std::cin.get();
        std::cout << "Betting tokens have been returned to you. You still have " << _bettingTokens << std::endl;
        std::cin.get();
    }

    if (_bettingTokens != 0)
    {
        bool valid = false;
        while (valid == false)
        {
            char ans[2] = { 0 };
            std::cout << "Would you like to play another round? (Y/N): ";
            std::cin.getline(ans, 2);
            std::cout << std::endl;

            if (ans[0] == 'N' || 
                ans[0] == 'n')
            {
                _i = 52;
                valid = true;
            }
            else if (ans[0] == 'Y' || 
                ans[0] == 'y')
            {
                valid = true;
            }
            else
            {
                std::cout << "That is not a valid option, please try again" << std::endl;
                std::cin.get();
            }
        }
    }
}