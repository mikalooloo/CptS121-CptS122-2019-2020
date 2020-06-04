/* Programmer: Mikaela Dean
Class: CPTS122, Spring 2020
Lab Section: 3
Programming Assignment: PA 5
Date: March 27, 2020
Description: Offbrand Yu Gi Oh! Game
Main.cpp
*/

#include "Header.h"
#include "Player.h"
#include "Queue.h"
#include "Stack.h"
#include "Stats.h"

int main(void)
{
	srand(time(NULL));

	// General
	std::string garbage;
	bool players_created = false;
	int menu_choice = 0;
	int round = 1;
	int round_winner = 0;
	int coin_toss = 0;
	// Players
	Player player1;
	Player player2;
	bool player_won = false;
	int p1mode = 0;
	int p2mode = 0;
	// Trading
	CardStackNode* trade_card1 = new CardStackNode;
	CardStackNode* trade_card2 = new CardStackNode;
	CardStackNode* temp = new CardStackNode;
	
	
	while (menu_choice != 5) // repeat until 5 or Quit is selected
	{
		print_main_menu();
		std::cin >> menu_choice;

		switch (menu_choice) // what choice the user entered for the menu
		{
		case 1: // 1. Create Players
			std::cout << "Enter a name for Player 1: ";
			player1.setName();
			std::cout << std::endl << "Enter a name for Player 2: ";
			player2.setName();

			system("cls");
			std::cout << "Player 1 added as " << player1.getName() << " and Player 2 added as " << player2.getName() << "!" << std::endl << std::endl;
			players_created = true;
			break;
		case 2: // 2. Add Cards to a Player
			system("cls");
			std::cout << "Adding Cards to a Player" << std::endl << std::endl;
			if (players_created)
			{
				std::cout << "Which player do you want to add cards to?" << std::endl;
				std::cout << "1. " << player1.getName() << std::endl;
				std::cout << "2. " << player2.getName() << std::endl;
				std::cin >> menu_choice;

				while (menu_choice < 1 || menu_choice > 2) // while choice is not Player 1 or 2
				{
					std::cout << std::endl << "Not a valid choice! Pick Player 1 or Player 2. " << std::endl;
				}

				if (menu_choice == 1) // if Player 1
				{
					system("cls");
					player1.new_card(); // add card to player 1
				}
				else // otherwise
				{
					system("cls");
					player2.new_card(); // add card to player 2
				}
			}
			else // if no players
			{ 
				system("cls");
				std::cout << "Adding Cards to a Player" << std::endl << std::endl;
				std::cout << "Please create some players first!" << std::endl << std::endl;
			}
			
			break;
		case 3: // 3. Trade Cards with Other Player
			system("cls");
			std::cout << "Trading Cards" << std::endl;

			if (players_created) // if players are created
			{
				std::cout << "Which Player do you want to start with?" << std::endl;

				std::cout << "1. " << player1.getName() << std::endl;
				std::cout << "2. " << player2.getName() << std::endl;
				std::cin >> menu_choice;

				while (menu_choice < 1 || menu_choice > 2) // while not player 1 or 2
				{
					if (std::cin.fail()) // if a character is entered instead of a number
					{
						system("cls");
						std::cout << std::endl << "Not a valid choice! Pick Player 1 or Player 2. " << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
					}
					else
					{
						system("cls");
						std::cout << std::endl << "Not a valid choice! Pick Player 1 or Player 2. " << std::endl;
					}
				}

				if (menu_choice == 1) // if player 1
				{
					system("cls");
					trade_card1 = player1.trade_cards(); // pick a card from player 1 first then
					system("cls");
					trade_card2 = player2.trade_cards(); // then player 2
					system("cls");
					std::cout << "Trading Cards" << std::endl; // following just prints the cards being traded nicely
					std::cout << "The cards being traded are: " << std::endl;
					std::cout << player1.getName() << "'s Card" << std::endl;
					std::cout << trade_card1->name << std::endl;
					std::cout << "Attack: " << trade_card1->attack << std::endl;
					std::cout << "Defense: " << trade_card1->defense << std::endl;
					std::cout << "Type: " << trade_card1->type << std::endl << std::endl;
					std::cout << player2.getName() << "'s Card" << std::endl;
					std::cout << trade_card2->name << std::endl;
					std::cout << "Attack: " << trade_card2->attack << std::endl;
					std::cout << "Defense: " << trade_card2->defense << std::endl;
					std::cout << "Type: " << trade_card2->type << std::endl << std::endl;
					temp = player1.swap(trade_card1, trade_card2); // makes card1 card2
					player2.swap(trade_card2, temp); // and card2 card 1
					std::cout << "Swap successful. Enter any character to continue. ";
					std::cin >> garbage;
				}
				else // otherwise, start with player 2 first
				{
					system("cls");
					trade_card2 = player2.trade_cards();
					system("cls");
					trade_card1 = player1.trade_cards();
					system("cls");
					std::cout << "Trading Cards" << std::endl; // printing pretty
					std::cout << "The cards being traded are: " << std::endl;
					std::cout << player2.getName() << "'s Card" << std::endl;
					std::cout << trade_card2->name << std::endl;
					std::cout << "Attack: " << trade_card2->attack << std::endl;
					std::cout << "Defense: " << trade_card2->defense << std::endl;
					std::cout << "Type: " << trade_card2->type << std::endl << std::endl;
					std::cout << player1.getName() << "'s Card" << std::endl;
					std::cout << trade_card1->name << std::endl;
					std::cout << "Attack: " << trade_card1->attack << std::endl;
					std::cout << "Defense: " << trade_card1->defense << std::endl;
					std::cout << "Type: " << trade_card1->type << std::endl << std::endl;
					temp = player1.swap(trade_card1, trade_card2); // makes card1 card2
					player2.swap(trade_card2, temp); // and card2 card1
					std::cout << "Swap successful. Enter any character to continue. ";
					std::cin>> garbage;
				}
			}
			else
			{
				system("cls"); // otherwise you need players
				std::cout << "Trading Cards" << std::endl<< std::endl;
				std::cout << "Please create some players first!" << std::endl << std::endl;
			}
			break;
		case 4: // 4. Battle with Other Player
			
			if (players_created) // if players are created
			{
				player1.setLifePoints(); // set to 8000
				player2.setLifePoints(); // set to 8000

				coin_toss = rand() % 2; // randomize who goes first

				system("cls");

				std::cout << "Coin toss initiating"; // makes this part pretty
				Sleep(500);
				std::cout << ".";
				Sleep(500);
				std::cout << ".";
				Sleep(500);
				std::cout << "." << std::endl;
				Sleep(500);

				if (coin_toss == 0) // player 1 goes first
				{
					std::cout << "Congrats " << player1.getName() << ", you are going first in this battle." << std::endl;
					std::cout << std::endl << "Enter any character to continue. ";
					std::cin >> garbage;
				}
				else // player 2 goes first
				{
					std::cout << "Congrats " << player2.getName() << ", you are going first in this battle." << std::endl;
					std::cout << std::endl << "Enter any character to continue. ";
					std::cin >> garbage;
				}

				while (!player_won && !player1.deckEmpty()) // as long as a player has not won and the deck has cards
				{
					if (!coin_toss) // if coin_toss is 0, or for Player 1 to go first
					{
						system("cls");
						std::cout << player1.getName() << ", please enter any character when you're ready! ";
						std::cin >> garbage;
						p1mode = player1.turn(player1, round); // returns what mode is activated
						system("cls");
						std::cout << player2.getName() << ", please enter any character when you're ready! ";
						std::cin >> garbage;
						p2mode = player2.turn(player2, round);
						round_winner = player1.battle(player1, player2, p1mode, p2mode); // returns who won
						if (round_winner == 1)
						{
							player_won = player1.win_check(player2); // if player 1 won, check to see if player 2 lost the entire game
						}
						else
						{
							player_won = player2.win_check(player1); // same with this but visa versa
						}
						++round;
					}
					else // otherwise player 2 goes first
					{
						system("cls");
						std::cout << player2.getName() << ", please enter any character when you're ready! ";
						std::cin >> garbage;
						p2mode = player2.turn(player2, round);
						system("cls");
						std::cout << player1.getName() << ", please enter any character when you're ready! ";
						std::cin >> garbage;
						p1mode = player1.turn(player1, round);
						round_winner = player2.battle(player1, player2, p1mode, p2mode);
						if (round_winner == 1)
						{
							player_won = player1.win_check(player2);
						}
						else
						{
							player_won = player2.win_check(player1);
						}
						++round;
					}
				}

				system("cls");

				if (round_winner == 1) // if player 1 won the whole game
				{
					std::cout << "Congrats " << player1.getName() << ", you have reduced " << player2.getName() << "'s Life Points to 0 and you have won the game!" << std::endl;
					player1.deal_cards();
					player2.deal_cards();
				}
				else if (round_winner == 2) // or if player 2 did
				{
					std::cout << "Congrats " << player2.getName() << ", you have reduced " << player1.getName() << "'s Life Points to 0 and you have won the game!" << std::endl;
					player1.deal_cards();
					player2.deal_cards();
				}
				else // or if the deck ran out
				{
					std::cout << "Since both players' decks have been depleted," << std::endl << "we will calculate the winner by comparing the Life Points left of each player!" << std::endl << std::endl;
					if (player1.get_lp() > player2.get_lp())
					{
						std::cout << "Congrats " << player1.getName() << ", you have more Life Points (" << player1.get_lp() << ") than " << player2.getName() << "'s Life Points (" << player2.get_lp() << ") and you have won the game!" << std::endl;
						round_winner = 1;
					}
					else if (player2.get_lp() > player1.get_lp())
					{
						std::cout << "Congrats " << player2.getName() << ", you have more Life Points (" << player2.get_lp() << ") than " << player1.getName() << "'s Life Points (" << player1.get_lp() << ") and you have won the game!" << std::endl;
						round_winner = 2;
					}
					else
					{
						std::cout << "Congrats you two! Both " << player1.getName() << " & " << player2.getName() << " have won with " << player1.get_lp() << " Life Points!" << std::endl;
					}
				}

				std::cout << std::endl << "Enter any character to continue. ";
				std::cin >> garbage;

				system("cls");
			}
			else
			{
				system("cls");
				std::cout << "Battle" << std::endl;
				std::cout << "Please create players before trying to battle!" << std::endl << std::endl;
			}
			break;
		case 5: // 5. Quit
			std::cout << "Quitting..." << std::endl;
			break;
		default:
			if (std::cin.fail()) // if a character is entered instead of a number
			{
				system("cls");
				std::cout << "Invalid input, please enter 1, 2, 3, 4, or 5!" << std::endl << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				system("cls");
				std::cout << "Invalid input, please enter 1, 2, 3, 4, or 5!" << std::endl << std::endl;
			}
			break;
		}
	}
}