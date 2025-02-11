#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to draw a horizontal line of specified length and symbol
void drawLine(int n, char symbol);

// Function to display the game rules
void rules();

int main()
{
    string playerName; // Stores the player's name
    int amount; // Player's balance amount
    int bettingAmount; // Amount the player wants to bet
    int guess; // Player's guessed number
    int dice; // Randomly generated number (1-10)
    char choice; // Player's choice to continue or quit

    srand(time(0)); // Seed for random number generation

    // Display game title
    drawLine(60, '_');
    cout<<"\n\n\n\t\tCASINO GAME\n\n\n\n";
    drawLine(60, '_');

    // Get player's name
    cout<<"\n\nEnter Your Name: ";
    getline(cin, playerName);

    // Get deposit amount
    cout<<"\n\nEnter Deposit amount to play game: $";
    cin>>amount;

    do
    {
        system("cls"); // Clear the screen for a fresh display
        rules(); // Show game rules
        cout<<"\n\nYour current balance is $ "<<amount<<"\n";

        // Get a valid betting amount
        do
        {
            cout<<playerName<<", enter money to bet : $";
            cin>>bettingAmount;
            if(bettingAmount > amount)
                cout<<"Your betting amount is more than your current balance\n"
                <<"\nRe-enter data\n";
        }
        while(bettingAmount > amount);

        // Get a valid number to bet on (1-10)
        do
        {
            cout<<"Guess your number to bet between 1 to 10 :";
            cin>>guess;
            if(guess <= 0 || guess > 10)
                cout<<"Please check the number!! It should be between 1 to 10\n"
                <<"\nRe-enter data\n";
        } while (guess <= 0 || guess > 10);

        // Generate a random number between 1 and 10
        dice = rand() % 10 + 1;

        // Check if the player's guess matches the generated number
        if(dice == guess)
        {
            cout<<"\n\nGood Luck!! You won $ "<<bettingAmount * 10;
            amount = amount + bettingAmount * 10; // Update balance with winnings
        }
        else
        {
            cout<<"Bad luck this time!! You lost $ "<<bettingAmount<<"\n";
            amount = amount - bettingAmount; // Deduct the lost bet from balance
        }

        // Show the winning number
        cout<<"\nThe winning number was : "<<dice<<"\n";
        cout<<"\n"<<playerName<<", You have $ "<<amount<<"\n";

        // Check if the player has run out of money
        if(amount == 0)
        {
            cout<<"You have no money to play";
            break;
        }

        // Ask if the player wants to continue playing
        cout<<"\n\n--> Do you want to play again (y/n)? ";
        cin>>choice;

    } while(choice == 'Y' || choice == 'y'); // Loop continues if the player chooses 'y'

    // Display game exit message
    cout<<"\n\n\n";
    drawLine(70, '=');
    cout<<"\n\nThanks for playing the game. Your balance amount is $ "<<amount<<"\n\n";
    drawLine(70, '=');

    return 0;
}

// Function to draw a horizontal line of specified length and symbol
void drawLine(int n, char symbol)
{
    for(int i = 0; i<n; i++)
        cout<<symbol;
    cout<<"\n";
}

// Function to display the game rules
void rules()
{
    system("cls"); // Clear the screen
    cout<<"\n\n";
    drawLine(80, '-');
    cout<<"\n1) Choose any number between 1 to 10\n";
    cout<<"\n2) If you win, you will get 10 times the money you bet\n";
    cout<<"\n3) If you bet on the wrong number, you will lose your betting amount\n\n";
    drawLine(80,'-');
}
