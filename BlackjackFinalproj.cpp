#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <map>
#include <conio.h>
#include <bits/stdc++.h>

using namespace std;
                                                // Updates: Added a display of chances of not busting.
                                                // Initialized a map with each type of card and its count, and
                                                // an integer type numOfCards that holds the number of cards(52).
                                                // both of these variables will be deducted for each draw.
                                                // The map will be decremented by 1 for each drawn for the specific type of card, 
                                                // same for numOfCards. Then the total of all values in the map together is equal to numOfCards.
                                                // The chances of not busting are calculated by dividing the number of safe cards by the total number of cards.
struct Player {
    string username;
    float balance = 5000;
    int bet = 0;
    char hitStand;
    bool exist = false;
};

struct GameState {
    bool twoPlayers = false;
    bool continueGame = false;
    int whichPlayer = 0;
    int playerSelected = 0;
    bool player1Kicked = false, player2Kicked = false;
    int playersRegistered = 0;
    int aceVal = 0;
};

int numOfCards = 52;
map<string, int> cardCount = {
    {"Ace", 4}, {"2", 4}, {"3", 4}, {"4", 4}, {"5", 4}, {"6", 4}, {"7", 4}, {"8", 4}, {"9", 4}, {"10", 4}, {"Jack", 4}, {"Queen", 4}, {"King", 4}
};

map<string, string> cardArt = {
    {"A", "  _____\n |A .  |\n | /.\\ |\n |(_._)|\n |  |  |\n |____V|"},
    {"2", "  _____\n |2    |\n |  o  |\n |     |\n |  o  |\n |____Z|"},
    {"3", "  _____\n |3    |\n | o o |\n |     |\n |  o  |\n |____E|"},
    {"4", "  _____\n |4    |\n | o o |\n |     |\n | o o |\n |____h|"},
    {"5", "  _____\n |5    |\n | o o |\n |  o  |\n | o o |\n |____S|"},
    {"6", "  _____\n |6    |\n | o o |\n | o o |\n | o o |\n |____9|"},
    {"7", "  _____\n |7    |\n | o o |\n |o o o|\n | o o |\n |____L|"},
    {"8", "  _____\n |8    |\n |o o o|\n | o o |\n |o o o|\n |____8|"},
    {"9", "  _____\n |9    |\n |o o o|\n |o o o|\n |o o o|\n |____6|"},
    {"10", "  _____\n |10  o|\n |o o o|\n |o o o|\n |o o o|\n |___0I|"},
    {"J", "  _____\n |J  ww|\n | o {)|\n |o o% |\n | | % |\n |__%%[|"},
    {"Q", "  _____\n |Q  ww|\n | o {(|\n |o o%%|\n | |%%%|\n |_%%%O|"},
    {"K", "  _____\n |K  WW|\n | o {)|\n |o o%%|\n | |%%%|\n |_%%%>|"}
};

Player player1;
Player player2;
char tap2Continue;

struct Node {
    string data; // Change from int to string
    Node* next;
};

class Stack {
    Node* top;
    
    public:
        Stack() : top(nullptr) {}

        void push(const string& value) { // Push method takes a string
            Node* newNode = new Node();
            newNode->data = value;
            newNode->next = top;
            top = newNode;
        }

        void pop() { // Pop method to remove the top element
            if (!top) {
                cout << "Stack is empty." << endl;
                return;
            }

            Node* temp = top; 
            top = top->next;
            delete temp;
        }

        string peek() { // Peek method returns a string
            if(top) {
                return top->data;
            }
            return ""; // Return an empty string if the stack is empty
        }

        void clearStack() {
            while (top) {
                pop();
            }
        }

        void display() { // Display the stack contents
            if (!top) {
                cout << "Stack is empty." << endl;
                return;
            }
        
            Node* temp = top;
            while (temp) {
                cout << temp->data << endl;
                temp = temp->next;
            }
        }
};

class Node2 {
public:
    std::string data;
    Node2* next;

    Node2(const std::string& value) : data(value), next(nullptr) {}
};

class Queue {
private:
    Node2* front;
    Node2* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(const string& value) {
        Node2* newNode = new Node2(value);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = rear->next;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        Node2* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    string getFront() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return "";
        }
        return front->data;
    }

    string peek() {
        if (front) {
            return front->data;
        }
        return ""; // Return an empty string if the queue is empty
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        Node2* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void clearQueue() {
        while(front) {
            dequeue();
        }
    }
};

void createDeck(Stack& cardDeck) {
    vector<string> fullDeck = {
    "Ace of Spades", "Ace of Hearts", "Ace of Clubs", "Ace of Diamonds",
    "2 of Spades", "2 of Hearts", "2 of Clubs", "2 of Diamonds",
    "3 of Spades", "3 of Hearts", "3 of Clubs", "3 of Diamonds",
    "4 of Spades", "4 of Hearts", "4 of Clubs", "4 of Diamonds",
    "5 of Spades", "5 of Hearts", "5 of Clubs", "5 of Diamonds",
    "6 of Spades", "6 of Hearts", "6 of Clubs", "6 of Diamonds",
    "7 of Spades", "7 of Hearts", "7 of Clubs", "7 of Diamonds",
    "8 of Spades", "8 of Hearts", "8 of Clubs", "8 of Diamonds",
    "9 of Spades", "9 of Hearts", "9 of Clubs", "9 of Diamonds",
    "10 of Spades", "10 of Hearts", "10 of Clubs", "10 of Diamonds",
    "Jack of Spades", "Jack of Hearts", "Jack of Clubs", "Jack of Diamonds",
    "Queen of Spades", "Queen of Hearts", "Queen of Clubs", "Queen of Diamonds",
    "King of Spades", "King of Hearts", "King of Clubs", "King of Diamonds"
    };

    //Shuffle card deck
    random_device rd;
    mt19937 g(rd());
    shuffle(fullDeck.begin(), fullDeck.end(), g);

        //Push all the cards into a stack
    for (int i=0; i<fullDeck.size(); i++) {
        cardDeck.push(fullDeck[i]);
    }
}

void placeBet(Player& player) {
    cout << "    " << player.username << " Balance: " << player.balance << endl;
    cout << "    Place your bet(min: 100): ";
    while (!(cin >> player.bet) || player.bet <= 0) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a valid bet: ";
    }

    if (player.bet > player.balance || player.bet < 100) {
        cout << "Invalid bet." << endl;
        placeBet(player); // Retry on invalid bet
    }
    else {
        player.balance -= player.bet;
    }
}

void playerInfo(GameState& gameState) {
    int playerCount = 0;
    cout << "    [1]  Single-player" << endl;
    cout << "    [2]  Two Players" << endl;
    cout << "Choose option: ";
    while (!(cin >> playerCount) || (playerCount != 1 && playerCount != 2)) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter 1 or 2: ";
    }

    if (!gameState.continueGame) {
        if (playerCount == 1) {
            cout << "Enter username: ";
            cin >> player1.username;
            placeBet(player1);
            gameState.twoPlayers = false;
            gameState.whichPlayer = 1;
            gameState.playersRegistered = 1;
            gameState.whichPlayer = 1;
            player1.exist = true;
        }
        else if (playerCount == 2) {
            cout << "Enter username for Player 1: ";
            cin >> player1.username;
            placeBet(player1);

            cout << "Enter username for Player 2: ";
            cin >> player2.username;
            placeBet(player2);

            player1.exist = true;
            player2.exist = true;
            gameState.twoPlayers = true;
            gameState.playersRegistered = 2;
        }
    }
    else { // Continuing an existing game
        if (gameState.twoPlayers) { // Scenario: Started with two players
            if (playerCount == 1) { // Switching to single-player mode
                bool playerSelected = false;
                while (!playerSelected) {
                    cout << "1. " << player1.username << endl;
                    cout << "2. " << player2.username << endl;
                    cout << "Choose user: ";
                    while (!(cin >> gameState.whichPlayer) || (gameState.whichPlayer != 1 && gameState.whichPlayer != 2)) {
                        cin.clear(); // clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                        cout << "Invalid input. Please enter 1 or 2: ";
                    }

                    if (gameState.whichPlayer == 1 && !gameState.player1Kicked) {
                        placeBet(player1);
                        playerSelected = true;
                    } 
                    else if (gameState.whichPlayer == 2 && !gameState.player2Kicked) {
                        placeBet(player2);
                        playerSelected = true;
                    } 
                    else {
                        cout << "Selected player is out of the game." << endl;
                        cout << "Reason: Insufficient funds." << endl;
                        playerSelected = false;
                    }
                }
                gameState.twoPlayers = false;
            } 
            else if (playerCount == 2) { // Continuing with two players
                if (player1.balance >= 100 && player2.balance >= 100) {
                    placeBet(player1);
                    placeBet(player2);
                    gameState.twoPlayers = true;
                } 
                else {
                    if (gameState.player1Kicked) {
                        cout << player1.username << " has insufficient funds. Kicking player out.." << endl;
                        placeBet(player2);
                        gameState.twoPlayers = false;
                    } 
                    else if (gameState.player2Kicked) {
                        cout << player2.username << " has insufficient funds. Kicking player out.." << endl;
                        placeBet(player1);
                        gameState.twoPlayers = false;
                    }
                }
            }
        }
        else if (!gameState.twoPlayers) { // Scenario: Started with single-player mode
            if (playerCount == 1) { // Continuing as single-player
                int createPlayer = 0;
                bool playerSelected = false;
                if (player2.exist) {
                    while (!playerSelected) {
                        cout << "1. " << player1.username << endl;
                        cout << "2. " << player2.username << endl;
                        cout << "Choose user: ";
                        while (!(cin >> gameState.whichPlayer) || (gameState.whichPlayer != 1 && gameState.whichPlayer != 2)) {
                            cin.clear(); // clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                            cout << "Invalid input. Please enter 1 or 2: ";
                        }

                        if (gameState.whichPlayer == 1 && !gameState.player1Kicked) {
                            placeBet(player1);
                            playerSelected = true;
                        } 
                        else if (gameState.whichPlayer == 2 && !gameState.player2Kicked) {
                            placeBet(player2);
                            playerSelected = true;
                        } 
                        else {
                            cout << "Selected player is out of the game." << endl;
                            cout << "Reason: Insufficient funds." << endl;
                            playerSelected = false;
                        }
                    }
                }
                else if (!player2.exist) {
                    while (!playerSelected) { // Loop until the user makes a valid choice
                        cout << "1. " << player1.username << endl;
                        cout << "2. Create new player" << endl;
                        cout << "Choose option: ";
                        while (!(cin >> createPlayer) || (createPlayer != 1 && createPlayer != 2)) {
                            cin.clear(); // clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                            cout << "Invalid input. Please enter 1 or 2: ";
                        }

                        if (createPlayer == 2 && gameState.playersRegistered != 2) {
                            cout << "Enter username for Player 2: ";
                            cin >> player2.username;
                            placeBet(player2);
                            gameState.whichPlayer = 2;
                            gameState.playersRegistered = 2;
                            gameState.player2Kicked = false;
                            playerSelected = true; // Exit loop after creating a new player
                            player2.exist = true;
                        } 
                        else if (createPlayer == 1) {
                            if (!gameState.player1Kicked) {
                                placeBet(player1);
                                gameState.whichPlayer = 1;
                                playerSelected = true; // Exit loop after placing a bet for player 1
                                player2.exist = false;
                            } 
                            else {
                                cout << "Selected player has insufficient funds. Please create a new player." << endl;
                            }
                        } 
                        else {
                            cout << "Invalid choice. Please choose again." << endl;
                        }
                    }
                }
            }
            else if (playerCount == 2) { // Transitioning to two-player mode
                if (gameState.playersRegistered == 1) {
                    if (player1.balance < 100 && !player2.exist) {
                        cout << player1.username << " has insufficient funds. Creating new player.." << endl;
                        cout << "Enter username for Player 2: ";
                        cin >> player2.username;
                        placeBet(player2);
                        gameState.twoPlayers = false;
                        gameState.player2Kicked = false;
                        gameState.whichPlayer == 2;
                    } 
                    else if (player2.balance < 100 && player1.balance >= 100) {
                        cout << player2.username << " has insufficient funds. Continuing to existing player.." << endl;
                        placeBet(player1);
                        gameState.twoPlayers = false;
                        gameState.whichPlayer == 1;
                    }
                    else if (player1.balance >= 100) {
                        placeBet(player1);
                        cout << "Enter username for Player 2: ";
                        cin >> player2.username;
                        placeBet(player2);
                        gameState.twoPlayers = true;
                        gameState.playersRegistered = 2;
                    }
                }
                else if (gameState.playersRegistered == 2 && player2.exist) {
                    if (player1.balance >= 100 && player2.balance >= 100) {
                    placeBet(player1);
                    placeBet(player2);
                    gameState.twoPlayers = true;
                    } 
                    else {
                        if (gameState.player1Kicked) {
                            cout << player1.username << " has insufficient funds. Kicking player out.." << endl;
                            placeBet(player2);
                            gameState.twoPlayers = false;
                        } 
                        if (gameState.player2Kicked) {
                            cout << player2.username << " has insufficient funds. Kicking player out.." << endl;
                            placeBet(player1);
                            gameState.twoPlayers = false;
                        }
                    }
                }
            }
        }
    }
}

void instructions() {
    cout << endl;
    cout << "Things You Should Know" << endl;
    cout << "   -In Blackjack, every player is betting against the dealer. The individual non-dealer players\nare not playing against one another." << endl;
    cout << "   -The goal of the game is to get a higher hand than the dealer without going over 21. Going\nover 21 is called busting." << endl;
    cout << "   -If a player has a better hand than the dealer without busting, they win their bet. If they have\na worse hand, the dealer takes their bet." << endl;
    cout << endl;
    cout << "Card Values:" << endl;
    cout << "   -2 through 10: The number listed on the card (e.g., 2 is worth 2 points)" << endl;
    cout << "   -Jack, Queen, King: 10 points" << endl;
    cout << "   -Ace: 1 or 11 points (the player gets to choose)" << endl;
    cout << endl;
    cout << "Blackjack Rules" << endl;
    cout << "   1. All the players must place a bet." << endl;
    cout << "   2. The dealer gives a card to each player as well as themselves." << endl;
    cout << "   3. The dealer hands out a second card to every player." << endl;
    cout << "   4. The dealer starts gameplay." << endl;
    cout << "   5. Decide if you want to stay or hit. (Take another card or settle with your cards)" << endl;
    cout << "   6. Cycle through each player until they have each finished their turn." << endl;
    cout << "   7. The dealer reveals their second card and winners are determined." << endl;
    cout << "   8. Bets are paid out and a new round begins." << endl;
    cout << endl;
}

int cardValue(const string& card, int aceVal=1) {
    if (card.find("Ace") != string::npos && aceVal == 1) { return 1; }
    else if (card.find("Ace") != string::npos && aceVal == 11) { return 11; }
    else if (card.find("2") != string::npos) { return 2; }
    else if (card.find("3") != string::npos) { return 3; }
    else if (card.find("4") != string::npos) { return 4; }
    else if (card.find("5") != string::npos) { return 5; }
    else if (card.find("6") != string::npos) { return 6; }      // Convert the card string to a value
    else if (card.find("7") != string::npos) { return 7; }
    else if (card.find("8") != string::npos) { return 8; }
    else if (card.find("9") != string::npos) { return 9; }
    else if (card.find("10") != string::npos) { return 10; }  
    else if (card.find("Jack") != string::npos) { return 10; }
    else if (card.find("Queen") != string::npos) { return 10; }
    else if (card.find("King") != string::npos) { return 10; }
    return 0;
}

void chances(int handtotal, Stack& cardDeck) { 
    double safeCards = 0;
    for (auto& card : cardCount) {
        if (cardValue(card.first) + handtotal <= 21) {
            safeCards += card.second;
        }
    }
    double chance = 0;
    cout << safeCards << " Safe cards" << endl << numOfCards << " Cards left" << endl;
    chance = (safeCards / numOfCards) * 100;
    cout << fixed << setprecision(2) << "Chance of not busting: " << chance << "%" << endl;
}

void updateCardCount(Stack& card) {
    size_t spacePos = card.peek().find(' ');
    string firstWord = card.peek().substr(0, spacePos);
    numOfCards--; // Decrease the total number of cards by 1
    cardCount[firstWord]--; // Decrease the count of the specific card
}

int cardArtPrint(const string& card) {
    if (card.find("Ace") != string::npos) cout << cardArt["A"]; 
    else if (card.find("2") != string::npos) cout << cardArt["2"];
    else if (card.find("3") != string::npos) cout << cardArt["3"];
    else if (card.find("4") != string::npos) cout << cardArt["4"];
    else if (card.find("5") != string::npos) cout << cardArt["5"];
    else if (card.find("6") != string::npos) cout << cardArt["6"]; 
    else if (card.find("7") != string::npos) cout << cardArt["7"];
    else if (card.find("8") != string::npos) cout << cardArt["8"];
    else if (card.find("9") != string::npos) cout << cardArt["9"];
    else if (card.find("10") != string::npos) cout << cardArt["10"];
    else if (card.find("Jack") != string::npos) cout << cardArt["J"];
    else if (card.find("Queen") != string::npos) cout << cardArt["Q"];
    else if (card.find("King") != string::npos) cout << cardArt["K"];
    return 0;
}

void drawCards(GameState& gameState, Stack& cardDeck, int& playerhandValue, vector<string>& playerhand, const string& playerName, Queue& history) {
    // Draw cards for player 1
        // First card
    if (cardValue(cardDeck.peek()) == 1) {
        cout << "   " << playerName << ", 1 You drew an Ace, set its value (1 or 11): ";
        while (!(cin >> gameState.aceVal) || (gameState.aceVal != 1 && gameState.aceVal != 11)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid value. Please enter 1 or 11: ";
        }
    }
    cout << cardArtPrint(cardDeck.peek()) << endl;
    playerhand.push_back(cardDeck.peek());
    playerhandValue += cardValue(cardDeck.peek(), gameState.aceVal);
    updateCardCount(cardDeck);
    cardDeck.pop();
    cout << "Continue.." << endl;
    getch();
    cin.ignore();
}

void dealerdrawCards(GameState& gameState, Stack& cardDeck, int& dealerhandValue, vector<string>& dealerHand, const string& card, Queue& history) {
    // Draw cards for the dealer
        // First card
    cout << "Dealer drew cards" << endl; 
    if (cardValue(cardDeck.peek()) == 1) { // If the dealer draws an Ace as their first card, it will be automatically 11
        gameState.aceVal == 11;
    }
    dealerHand.push_back(cardDeck.peek());
    dealerhandValue = cardValue(cardDeck.peek(), gameState.aceVal);
    cout << cardArtPrint(cardDeck.peek()) << endl;
    updateCardCount(cardDeck);
    cardDeck.pop();
    cout << "Continue.." << endl;
    getch();
    cin.ignore();

        // Second card
    if (cardValue(cardDeck.peek()) == 1) {
        gameState.aceVal == 1; // In case the dealer drew an Ace as their first card (11), make the Ace value as 1 because it doesn't put them into a bust
    }
    dealerHand.push_back(cardDeck.peek());
    dealerhandValue = dealerhandValue + cardValue(cardDeck.peek(), gameState.aceVal);
    cout << "  _____\n |____X|\n |  |  |\n |(_._)|\n | /.\\ |\n |X .  |" << endl;
    updateCardCount(cardDeck);
    cardDeck.pop();
    cout << "Continue.." << endl;
    getch();
    cin.ignore();
}

void playerHit(Stack& cardDeck, vector<string>& playerhand, int& playerhandValue, const string& card, const string& playerName, GameState& gameState, Queue& history) {
    // Draw cards for player 1
        // First card
    history.enqueue(playerName + " chose to hit\n");
    if (cardValue(cardDeck.peek()) == 1) {
        cout << playerName << ", 1 You drew an Ace, set its value (1 or 11): ";
        while (!(cin >> gameState.aceVal) || (gameState.aceVal != 1 && gameState.aceVal != 11)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid value. Please enter 1 or 11: ";
        }
    }
    playerhand.push_back(cardDeck.peek());
    cout << "You drew " << cardDeck.peek() << endl;
    cout << cardArtPrint(cardDeck.peek()) << endl;
    playerhandValue += cardValue(cardDeck.peek(), gameState.aceVal);
    updateCardCount(cardDeck);
    cardDeck.pop();
    
    // Display updated hand
    cout << playerName << " cards: " << endl;
    for (int i=0; i<playerhand.size(); i++) {
        cout << "   " << playerhand[i] << endl;
    }
    cout << playerName << " hand total: " << playerhandValue << endl;   
    history.enqueue(playerName + " hand value: " + to_string(playerhandValue) + "\n");

    // Check if bust or blackjack
    if (playerhandValue>21) {
        cout << "   Bust!" << endl;
    }
    if (playerhandValue==21) {
        cout << "   Blackjack!" << endl;
    }
    cout << endl;
}

void playerStand(Stack& cardDeck, vector<string>& playerHand, int& playerhandValue, const string& playerName, Queue& history) {
    cout << playerName << " final cards: " << endl;
    for (int i=0; i<playerHand.size(); i++) {
        cout << "   " << playerHand[i] << endl;
    }
    cout << playerName << " hand total: " << playerhandValue << endl << endl;   
    history.enqueue(playerName + " chose to stand\n");
    history.enqueue(playerName + " final hand value: " + to_string(playerhandValue) + "\n");
}

void playerDecision(Stack& cardDeck, int& playerhandValue, vector<string>& playerHand, const string& playerName, GameState& gameState, char& hitStand, Queue& history) {
    cout << playerName << " cards: " << endl;
    for (int i=0; i<playerHand.size(); i++) {
        cout << "   " << playerHand[i] << endl;
    }
    cout << playerName << " hand total: " << playerhandValue << endl << endl;

    // Ask player to hit or stand
    while (playerhandValue < 21) {
        chances(playerhandValue, cardDeck);
        cout << playerName << ", do you want to hit or stand? (H/S): ";
        while (!(cin >> hitStand) || (toupper(hitStand) != 'H' && toupper(hitStand) != 'S')) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter H or S: ";
        }
        hitStand = toupper(hitStand);
        cout << "" << endl;

        switch(hitStand) {
            case 'H':
                playerHit(cardDeck, playerHand, playerhandValue, cardDeck.peek(), playerName, gameState, history);
                break;
            case 'S':
                playerStand(cardDeck, playerHand, playerhandValue, playerName, history);
                break;
            default:
                break;
        }
        if (hitStand == 'S') {
            break;
        }
    }
}

void dealerHit(Stack& cardDeck, vector<string>& dealerHand, int& dealerhandValue, const string& card, Queue& history) {
    int aceVal;
    history.enqueue("Dealer chose to hit\n");
    if (card.find("Ace") != std::string::npos) {
    cout << "Dealer drew an Ace, choosing its value.." << endl;
        if (dealerhandValue<11) {
            cout << "Dealer chose 11" << endl;
            aceVal = 11;
        }
        else {
            cout << "Dealer chose 1" << endl;
            aceVal = 1;
        }

    // Add the Ace with chosen value to dealer's hand
    dealerHand.push_back(cardDeck.peek());
    cout << "Continue..";
    getch();
    cin.ignore();
    cout << cardArtPrint(cardDeck.peek()) << endl;
    }
    else {
        cout << cardArtPrint(cardDeck.peek()) << endl;
        dealerHand.push_back(cardDeck.peek()); // Add new card to dealer's hand
    }

    dealerhandValue = dealerhandValue + cardValue(cardDeck.peek(), aceVal); // Update dealer's hand value
    updateCardCount(cardDeck);
    cardDeck.pop(); // Remove the card from the stack
    cout << "Dealer drew " << dealerHand.back() << endl; // Show the card drawn
    cout << "Dealer's cards: " << endl;
    //Display updated hand
    for (int i=0; i<dealerHand.size(); i++) {
        cout << "   " << dealerHand[i] << endl;
    }
    cout << "Dealer hand total: " << dealerhandValue << endl << endl;   
    history.enqueue("Dealer's hand value: " + to_string(dealerhandValue) + "\n");

    //Check if bust or blackjack
    if (dealerhandValue>21) {
        cout << "   Dealer bust!" << endl << endl;
    }
    else if (dealerhandValue==21) {
        cout << "Dealer Blackjack!" << endl << endl;
    }
    cout << "Continue..";
    getch();
    cin.ignore();
    cout << endl;
}

void dealerStand(Stack& cardDeck, vector<string>& dealerHand, int& dealerhandValue, Queue& history) {
    cout << "Dealer's final cards: " << endl;
    for (int i=0; i<dealerHand.size(); i++) {
        cout << "   " << dealerHand[i] << endl;
    }
    cout << "Dealer's hand total: " << dealerhandValue << endl << endl;     
    history.enqueue("Dealer chose to stand\n");
    history.enqueue("Dealer's final hand value: " + to_string(dealerhandValue) + "\n");
}

void dealerDecision(Stack& cardDeck, vector<string>& dealerHand, int& dealerhandValue, Queue& history) {
    cout << "Dealer reveals their cards: " << endl;
    for (int i=0; i<dealerHand.size(); i++) {
        cout << "   " << dealerHand[i] << endl;
    }
    history.enqueue("Dealer reveals their cards..\n");
    history.enqueue("Dealer's hand value: " + to_string(dealerhandValue) + "\n");
    cout << "Dealer's hand total: " << dealerhandValue << endl << endl;
    cout << "Continue..";
    getch();
    cin.ignore();
    cout << endl;

    // Dealer decision to hit
    while (dealerhandValue <= 16) {
        cout << "Dealer chooses to hit.." << endl;
        dealerHit(cardDeck, dealerHand, dealerhandValue, cardDeck.peek(), history);
    }
    // Dealer decision to stand
    if (dealerhandValue > 16 && dealerhandValue < 21) {
        cout << "Dealer chooses to stand.." << endl;
        dealerStand(cardDeck, dealerHand, dealerhandValue, history);
        cout << "Continue..";
        getch();
        cin.ignore();
        cout << endl;
    }
}

void earlyResults(int& dealerhandValue, vector<string>& dealerHand, Queue& history) {
    cout << "Dealer Blackjack!" << endl;
    cout << "Dealer's final cards: " << endl;
    for (int i=0; i<dealerHand.size(); i++) {
        cout << "   " << dealerHand[i] << endl;
    }
    cout << "Dealer's hand total: " << dealerhandValue << endl << endl;
    history.enqueue("Dealer BlackJack!\n");
    cout << "Continue..";
    getch();
    cin.ignore();
    cout << endl;

    cout << player1.username << " loss!" << endl;
    cout << "\t-" << player1.bet << endl;
    player1.bet = 0;
    cout << "\tBalance: " << player1.balance << endl;
    history.enqueue(player1.username + " loss!\n");

    cout << "Continue..";
    getch();
    cin.ignore();
    cout << endl;

    if (player2.exist) {
        cout << player2.username << " loss!" << endl;
        cout << "\t-" << player2.bet << endl;
        player2.bet = 0;
        cout << "\tBalance: " << player2.balance << endl;
        history.enqueue(player2.username + " loss!\n");
        
        cout << "Continue..";
        getch();
        cin.ignore();
        cout << endl;
    }
}

void results(GameState& gameState, int& player1handValue, int& player2handValue, int& dealerhandValue, Queue& history) {
    history.enqueue("Results: \n");
    // Both players tie with dealer  
    if (gameState.twoPlayers) {
        if (player1handValue==dealerhandValue && player2handValue==dealerhandValue) {
            cout << "Tie Game!\n\tReturning bets.." << endl << endl;
            player1.balance += player1.bet;
            player1.bet = 0;
            player2.balance += player2.bet;
            player2.bet = 0;
            history.enqueue("All Tie Game\n");
            } 
        }

    if (!gameState.twoPlayers) {
        if (gameState.whichPlayer == 1) {
            // Player 1 ties with dealer    
            if (player1handValue==dealerhandValue) {
                cout << player1.username << " Tie Game!\n\tReturning bet.." << endl << endl;
                player1.balance += player1.bet; // Return back values
                player1.bet = 0;
                history.enqueue(player1.username + " Tie Game\n");
            }
            // Player 1 bust
            else if (player1handValue>21) {
                cout << player1.username << " bust!" << endl;
                cout << "\t-" << player1.bet << endl;
                player1.bet = 0;
                cout << "\tBalance: " << player1.balance << endl << endl;
                if (player1.balance < 100) {
                    gameState.player1Kicked = true;
                }
                history.enqueue(player1.username + " bust\n");
            }
            // Player 1 blackjack
            else if (player1handValue == 21) {
                cout << player1.username << " Blackjack!" << endl;
                player1.balance += (player1.bet * 1.5);
                cout << "\t+" << player1.bet * 1.5 << endl;
                cout << "\tBalance: " << player1.balance << endl << endl;
                history.enqueue(player1.username + " Blackjack\n");
            }
            // Player 1 win
            else if (player1handValue>dealerhandValue && player1handValue < 21) {
                cout << player1.username << " win!" << endl;
                cout << "Reason: Higher hand than the Dealer" << endl;
                player1.balance += (player1.bet * 2);
                cout << "\t+" << player1.bet * 2 << endl;
                cout << "\tBalance: " << player1.balance << endl << endl;
                history.enqueue(player1.username + " won by higher hand\n");
            }
            // Player 1 loss
            else if (player1handValue<dealerhandValue && dealerhandValue < 21) {
                cout << player1.username << " loss!" << endl;
                cout << "Reason: Lower hand than the Dealer" << endl;
                cout << "\t-" << player1.bet << endl;
                player1.bet = 0;
                cout << "\tBalance: " << player1.balance << endl << endl;
                if (player1.balance < 100) {
                    gameState.player1Kicked = true;
                }
                history.enqueue(player1.username + " lost by lower hand\n");
            }
        }
        else {
        // Player 2 ties with dealer
            if (player2handValue==dealerhandValue) {
                cout << player2.username << " Tie Game!\n\tReturning bet.." << endl << endl;
                player2.balance += player2.bet;
                player2.bet = 0;
                history.enqueue(player2.username + " Tie Game\n");
            }
        // Player 2 bust
            else if (player2handValue>21) {
                cout << player2.username << " bust!" << endl;
                cout << "\t-" << player2.bet << endl;
                player2.bet = 0;
                cout << "\tBalance: " << player2.balance << endl << endl;
                if (player2.balance < 100) {
                    gameState.player2Kicked = true;
                }
                history.enqueue(player2.username + " bust\n");
            }
            // Player 2 blackjack
            else if (player2handValue == 21) {
                cout << player2.username << " Blackjack!" << endl;
                player2.balance += (player2.bet * 1.5);
                cout << "\t+" << player2.bet * 1.5 << endl;
                cout << "\tBalance: " << player2.balance << endl << endl;
                history.enqueue(player2.username + " Blackjack\n");
            }
            // Player 2 win
            else if (player2handValue>dealerhandValue && player2handValue < 21) {
                cout << player2.username << " win!" << endl;
                cout << "Reason: Higher hand than the Dealer" << endl;
                player2.balance += (player2.bet * 2);
                cout << "\t+" << player2.bet * 2 << endl;
                cout << "\tBalance: " << player2.balance << endl << endl;
                history.enqueue(player2.username + " won by higher hand\n");
            }
            // Player 2 loss
            else if (player2handValue<dealerhandValue && dealerhandValue < 21) {
                cout << player2.username << " loss!" << endl;
                cout << "Reason: Lower hand than the Dealer" << endl;
                cout << "\t-" << player2.bet << endl;
                player2.bet = 0;
                cout << "\tBalance: " << player2.balance << endl << endl;
                if (player2.balance < 100) {
                    gameState.player2Kicked = true;
                }
                history.enqueue(player2.username + " lost by lower hand\n");
            }
        }
    }

    else {
        // Player 1 ties with dealer    
        if (player1handValue==dealerhandValue) {
            cout << player1.username << " Tie Game!\n\tReturning bet.." << endl << endl;
            player1.balance += player1.bet; // Return back values
            player1.bet = 0;
            history.enqueue(player1.username + " Tie Game\n");
        }
        // Player 1 bust
        else if (player1handValue>21) {
            cout << player1.username << " bust!" << endl;
            cout << "\t-" << player1.bet << endl;
            player1.bet = 0;
            cout << "\tBalance: " << player1.balance << endl << endl;
            if (player1.balance < 100) {
                gameState.player1Kicked = true;
            }
            history.enqueue(player1.username + " bust\n");
        }
        // Player 1 blackjack
        else if (player1handValue == 21) {
            cout << player1.username << " Blackjack!" << endl;
            player1.balance += (player1.bet * 1.5);
            cout << "\t+" << player1.bet * 1.5 << endl;
            cout << "\tBalance: " << player1.balance << endl << endl;
            history.enqueue(player1.username + " Blackjack\n");
        }
        // Player 1 win
        else if (player1handValue>dealerhandValue && player1handValue < 21) {
            cout << player1.username << " win!" << endl;
            cout << "Reason: Higher hand than the Dealer" << endl;
            player1.balance += (player1.bet * 2);
            cout << "\t+" << player1.bet * 2 << endl;
            cout << "\tBalance: " << player1.balance << endl << endl;
            history.enqueue(player1.username + " won by higher hand\n");
        }
        // Player 1 loss
        else if (player1handValue<dealerhandValue && dealerhandValue < 21) {
            cout << player1.username << " loss!" << endl;
            cout << "Reason: Lower hand than the Dealer" << endl;
            cout << "\t-" << player1.bet << endl;
            player1.bet = 0;
            cout << "\tBalance: " << player1.balance << endl << endl;
            if (player1.balance < 100) {
                gameState.player1Kicked = true;
            }
            history.enqueue(player1.username + " lost by hand\n");
        }  

        // Player 2 ties with dealer
        if (player2handValue==dealerhandValue) {
            cout << player2.username << " Tie Game!\n\tReturning bet.." << endl << endl;
            player2.balance += player2.bet;
            player2.bet = 0;
            history.enqueue(player2.username + " Tie Game\n");
        }
        // Player 2 bust
        else if (player2handValue>21) {
            cout << player2.username << " bust!" << endl;
            cout << "\t-" << player2.bet << endl;
            player2.bet = 0;
            cout << "\tBalance: " << player2.balance << endl << endl;
            if (player2.balance < 100) {
                gameState.player2Kicked = true;
            }
            history.enqueue(player2.username + " bust\n");
        }
        // Player 2 blackjack
        else if (player2handValue == 21) {
            cout << player2.username << " Blackjack!" << endl;
            player2.balance += (player2.bet * 1.5);
            cout << "\t+" << player2.bet * 1.5 << endl;
            cout << "\tBalance: " << player2.balance << endl << endl;
            history.enqueue(player2.username + " Blackjack\n");
        }
        // Player 2 win
        else if (player2handValue>dealerhandValue && player2handValue < 21) {
            cout << player2.username << " win!" << endl;
            cout << "Reason: Higher hand than the Dealer" << endl;
            player2.balance += (player2.bet * 2);
            cout << "\t+" << player2.bet * 2 << endl;
            cout << "\tBalance: " << player2.balance << endl << endl;
            history.enqueue(player2.username + " won by higher hand\n");
        }
        // Player 2 loss
        else if (player2handValue<dealerhandValue && dealerhandValue < 21) {
            cout << player2.username << " loss!" << endl;
            cout << "Reason: Lower hand than the Dealer" << endl;
            cout << "\t-" << player2.bet << endl;
            player2.bet = 0;
            cout << "\tBalance: " << player2.balance << endl << endl;
            if (player2.balance < 100) {
                gameState.player2Kicked = true;
            }
            history.enqueue(player2.username + " lost by lower hand\n");
        }
    } // if (twoPlayers)

    // Dealer bust
    if (dealerhandValue>21) {
        if (gameState.twoPlayers) {
            if (player1handValue < 21) {
                cout << player1.username << " win!" << endl;
                player1.balance += (player1.bet * 2);
                cout << "\t+" << player1.bet * 2 << endl;
                cout << "\tBalance: " << player1.balance << endl << endl;
                history.enqueue(player1.username + " win\n");
            }
            if (player2handValue < 21) {
                cout << player2.username << " win!" << endl;
                player2.balance += (player2.bet * 2);
                cout << "\t+" << player2.bet * 2 << endl;
                cout << "\tBalance: " << player2.balance << endl << endl;
                history.enqueue(player2.username + " win\n");
            }
        }
        else {
            if (gameState.whichPlayer == 1) {
                if (player1handValue < 21) {
                    cout << player1.username << " win!" << endl;
                    player1.balance += (player1.bet * 2);
                    cout << "\t+" << player1.bet * 2 << endl;
                    cout << "\tBalance: " << player1.balance << endl << endl;
                    history.enqueue(player1.username + " win\n");
                }
            }
            else {
                if (player2handValue < 21) {
                    cout << player2.username << " win!" << endl;
                    player2.balance += (player2.bet * 2);
                    cout << "\t+" << player2.bet * 2 << endl;
                    cout << "\tBalance: " << player2.balance << endl << endl;
                    history.enqueue(player2.username + " win\n");
                }
            }
        }
    }

    // Dealer blackjack
    else if (dealerhandValue==21) {
        cout << "Dealer Blackjack!" << endl;
        if (player1handValue!=21) {
            cout << player1.username << " loss!" << endl;
            cout << "\t-" << player1.bet << endl;
            player1.bet = 0;
            cout << "\tBalance: " << player1.balance << endl;
            if (player1.balance < 100) {
                gameState.player1Kicked = true;
            }
            history.enqueue(player1.username + " loss");
        }
        if (player2handValue!=21 && player2.exist) {
            cout << player2.username << " loss!" << endl;
            cout << "\t-" << player2.bet << endl;
            player2.bet = 0;
            cout << "\tBalance: " << player2.balance << endl;
            if (player2.balance < 100) {
                gameState.player2Kicked = true;
            }
            history.enqueue(player1.username + " loss");
        }
    }

} // else if (dealerhandValue!=21)

void displayMenu(GameState& gameState) {
    char start;
    while (1) {
        cout << "--------BLACKJACK--------" << endl;
        cout << "       [P]    Play" << endl;
        cout << "       [H] How to play" << endl;
        cout << "       [Q]    Quit" << endl;
        cout << "Choose option: ";
        while (!(cin >> start) || (toupper(start) != 'H' && toupper(start) != 'P' && toupper(start) != 'Q')) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter H, P, or Q: ";
        }
        start = toupper(start);
        if (start == 'H') instructions();
        else if (start == 'Q') { cout << "       Game Over"; exit(0); }
        else if (start == 'P') break;
    }
    if (start == 'P') playerInfo(gameState);
}

int main() {
    char start;
    GameState gameState;
    displayMenu(gameState);

    Stack cardDeck;
    Queue history;

    gameState.player1Kicked = false;
    gameState.player2Kicked = false;

    cout << endl;
    while (1) {
        createDeck(cardDeck);
        vector<string> player1Hand;
        vector<string> dealerHand;
        vector<string> player2Hand;

        int player1handValue = 0;
        int player2handValue = 0;
        cout << "- - - Game Starting - - -" << endl;
        cout << "   Drawing Cards.." << endl << endl;
        history.enqueue("-----Game Start-----\n");
        cout << "Continue..";
        getch();
        cin.ignore();
        cout << endl;

        if (!gameState.twoPlayers) {
            if (!gameState.player1Kicked && gameState.whichPlayer == 1) {
                history.enqueue(player1.username + " drew cards\n");
                cout << player1.username << " drew cards" << endl;
                drawCards(gameState, cardDeck, player1handValue, player1Hand, player1.username, history);
                drawCards(gameState, cardDeck, player1handValue, player1Hand, player1.username, history);
                history.enqueue(player1.username + " hand value: " + to_string(player1handValue) + "\n");
            }
            if (!gameState.player2Kicked && gameState.whichPlayer == 2) {
                history.enqueue(player2.username + " drew cards\n");
                cout << player2.username << " drew cards" << endl;
                drawCards(gameState, cardDeck, player2handValue, player2Hand, player2.username, history);
                drawCards(gameState, cardDeck, player2handValue, player2Hand, player2.username, history);
                history.enqueue(player2.username + " hand value: " + to_string(player2handValue)+ "\n");
            }
        }
        else if (gameState.twoPlayers) {
            if (!gameState.player1Kicked) {
                history.enqueue(player1.username + " drew cards\n");
                cout << player1.username << " drew cards" << endl;
                drawCards(gameState, cardDeck, player1handValue, player1Hand, player1.username, history);
                drawCards(gameState, cardDeck, player1handValue, player1Hand, player1.username, history);
                history.enqueue(player1.username + " hand value: " + to_string(player1handValue)+ "\n");
            }
            if (!gameState.player2Kicked) {
                history.enqueue(player2.username + " drew cards\n");
                cout << player2.username << " drew cards" << endl;
                drawCards(gameState, cardDeck, player2handValue, player2Hand, player2.username, history);
                drawCards(gameState, cardDeck, player2handValue, player2Hand, player2.username, history);
                history.enqueue(player2.username + " hand value: " + to_string(player2handValue)+ "\n");
            }
        }

        int dealerhandValue = 0;
        dealerdrawCards(gameState, cardDeck, dealerhandValue, dealerHand, cardDeck.peek(), history);
        history.enqueue("Dealer drew their cards\n");
        
        // Display dealer cards
        cout << "Dealer's cards: " << endl;
        cout << "   " << dealerHand[0] << endl;
        cout << "   [Hidden card]" << endl;
        cout << "Dealer's hand total: " << cardValue(dealerHand[0]) << " + ___" << endl << endl;
        history.enqueue("Dealer's hand value: " + to_string(cardValue(dealerHand[0])) + " + ___\n");

        cout << "Continue..";
        getch();
        cin.ignore();
        cout << endl;

        if (dealerhandValue == 21) {
            earlyResults(dealerhandValue, dealerHand, history);
        }

        else if (dealerhandValue!=21) {
            // Display player 1 cards
            if (!gameState.twoPlayers && gameState.whichPlayer == 1) {
                playerDecision(cardDeck, player1handValue, player1Hand, player1.username, gameState, player1.hitStand, history);
                cout << "Continue..";
                getch();
                cin.ignore();
                cout << endl;
            }

            // Display player 2 cards
            else if (!gameState.twoPlayers && gameState.whichPlayer == 2) {
                playerDecision(cardDeck, player2handValue, player2Hand, player2.username, gameState, player2.hitStand, history);
                cout << "Continue..";
                getch();
                cin.ignore();
                cout << endl;
            }

            // If there are 2 players
            else if (gameState.twoPlayers) {
                if (!gameState.player1Kicked) {
                    playerDecision(cardDeck, player1handValue, player1Hand, player1.username, gameState, player1.hitStand, history);
                    cout << "Continue..";
                    getch();
                    cin.ignore();
                    cout << endl;
                }
                if (!gameState.player2Kicked) {
                    playerDecision(cardDeck, player2handValue, player2Hand, player2.username, gameState, player2.hitStand, history); 
                    cout << "Continue..";
                    getch();
                    cin.ignore();
                    cout << endl;
                }
            }

            // Reveal dealer card
            if (player1handValue < 21 || player2handValue < 21) {
                // If single-player and player 1 did a stand
                if (!gameState.twoPlayers) {
                    if (gameState.whichPlayer == 1 && player1.hitStand == 'S') {
                        dealerDecision(cardDeck, dealerHand, dealerhandValue, history);
                    }
                    else if (gameState.whichPlayer == 2 && player2.hitStand == 'S') {
                        dealerDecision(cardDeck, dealerHand, dealerhandValue, history);
                    }
                }
                else if (gameState.twoPlayers) {
                    dealerDecision(cardDeck, dealerHand, dealerhandValue, history);    
                }
            }
            // Results:
            results(gameState, player1handValue, player2handValue, dealerhandValue, history);
            history.enqueue("-----Game End-----\n");
        }
    
        char choice;
        while(1) {
            cout << "       [P] Continue Playing" << endl;
            cout << "       [H]   Review Game" << endl;
            cout << "       [Q]       Quit" << endl;
            cout << "Choose option: ";
            while (!(cin >> choice) || (toupper(choice) != 'P' && toupper(choice) != 'H' && toupper(choice) != 'Q')) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter P, H, or Q: ";
            }
            choice = toupper(choice);
            switch (choice) {
            case 'P':
                player1Hand.clear();
                player2Hand.clear();
                dealerHand.clear();
                gameState.continueGame = true;
                cout << string(100, '\n');
                playerInfo(gameState);
                cout << endl;
                cardDeck.clearStack();
                history.clearQueue();
                numOfCards = 52;
                cardCount = {{"Ace", 4}, {"2", 4}, {"3", 4}, {"4", 4}, {"5", 4}, {"6", 4},
                            {"7", 4}, {"8", 4}, {"9", 4}, {"10", 4}, {"Jack", 4}, {"Queen", 4}, {"King", 4}};
                break;
            case 'H':
                cout << string(100, '\n');
                history.display();
                break;
            case 'Q':
                cout << "       Game Over";
                exit(0);
            }
            if (choice == 'P') {
            break; 
            }
        }
        }
    return 0;
}