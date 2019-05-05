#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <stdlib.h>  

// wartosci do ustawiania kolorów w konsoli
#define _sizeOfBoard 100
#define _colorRed  12
#define _colorBlue  9
#define _colorWhite 15
#define _colorPurple  13
#define _colorGreen 10

using namespace std;
// uchwty do konsoli oraz zmienne przechowujace informacje o statkach oraz ruchach graczy
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char* boardGamePlayerX = new char[_sizeOfBoard];
char* boardGamePlayerY = new char[_sizeOfBoard];

char* postionsSelectedByX = new char[_sizeOfBoard];
char* postionsSelectedByY = new char[_sizeOfBoard];

int numberOfShipsPlayerX = 0;
int numberOfShipsPlayerY = 0;

/// metody pomocnicze do rysowanie obszaru gry
void setConsoleColor(int colorTarget, string word) {
	SetConsoleTextAttribute(hConsole, colorTarget);
	std::cout << word;
	SetConsoleTextAttribute(hConsole, _colorWhite);

}
void drawingMenuGame(string& namePlayerX, string& namePlayerY) {
	std::cout << "GRA W STATKI" << endl;
	std::cout << "Autor: Dominik Atrasik" << endl << endl;
	std::cout << "Jest to gra dla dwoch graczy X , Y" << endl;
	std::cout << "Celem kazdego gracza jest zgadniecie pozycji statkow przeciwnika\n, milej zabawy !" << endl << endl;
	std::cout << "Wprowadz imie gracza X ";
	setConsoleColor(_colorBlue, "(niebieski)");
	std::cout << endl;
	std::cin >> namePlayerX;
	std::cout << "Wprowadz imie gracza Y ";
	setConsoleColor(_colorRed, "(czerwony)");
	std::cout << endl;
	std::cin >> namePlayerY;
}
string statusBarPlayer(string playerName, int numShips) {
	string result;

	result += "----- GRACZ ";
	result += playerName;
	result += " | ILOSC STATKOW NIEWYKRYTYCH ";
	result += to_string(numShips);
	result += " -----";
	result += "\n\n\t";

	return result;
}
string statusBarOpponent(string opponetPlayerName, int numShips) {
	string result = "\n\n ";

	result += "----- TWOJ PRZECIWNIK: ";
	result += opponetPlayerName;
	result += " | STATKI PRZECIWNIKA ";
	result += to_string(numShips);
	result += " -----";
	result += "\n\n\t";

	return result;
}
/// incjalizacja obszaru gry losowymi statki za pomoca liczb pseudolosowych
int initlizeBoard(char* source) {

	int numberOfShipsCreated = 0;
	for (int i = 0; i < _sizeOfBoard; i++) {
		if (rand() % 5 == 0)
		{
			source[i] = 'X';
			numberOfShipsCreated++;

		}
		else
			source[i] = ' ';
	}
	return numberOfShipsCreated;
}

/// rysowanie obszaru gry
void drawingBoard(char source[], string playerName, int numShips, int colorPlayer) {

	setConsoleColor(colorPlayer, statusBarPlayer(playerName, numShips));

	for (int i = 0; i < _sizeOfBoard / 10; i++)
		std::cout << "==";
	std::cout << "=||\n\t||";


	for (int i = 1; i <= _sizeOfBoard; i++) {
		if (i % 10 == 0)
		{
			if (source[i - 1] == 'X')
			{
				setConsoleColor(_colorGreen, "X");
				std::cout << "||\n\t||";
			}
			else if (source[i - 1] == 'T')
			{
				setConsoleColor(_colorRed, "T");
				std::cout << "||\n\t||";
			}
			else
				std::cout << source[i - 1] << "||" << endl << "\t||";
		}
		else
		{
			if (source[i - 1] == 'X') {
				setConsoleColor(_colorGreen, "X ");
			}
			else if (source[i - 1] == 'T') {
				setConsoleColor(_colorRed, "T ");
			}
			else
				std::cout << source[i - 1] << " ";
		}

	}
	for (int i = 0; i < _sizeOfBoard / 10; i++)
		std::cout << "==";
}
/// rysowanie obaszaru gry przeciwnika
void drawingOpponentBoard(char* sourceSelected, char* source, string opponentPlayerName,
		int numberShips, int colorPlayer)
{

	setConsoleColor(colorPlayer, statusBarOpponent(opponentPlayerName, numberShips));

	for (int i = 0; i < _sizeOfBoard / 10 + 5; i++)
		std::cout << "==";

	std::cout << "=||\n\t||";

	for (int i = 1; i <= _sizeOfBoard; i++) {
		if (i % 10 == 0) {
			if (sourceSelected[i - 1] == 'X' && source[i - 1] == 'T')
			{
				setConsoleColor(_colorGreen, "XX");
				std::cout << "||" << endl << "\t||";
			}
			else if (sourceSelected[i - 1] == 'X')
			{
				setConsoleColor(_colorPurple, "XX");
				std::cout << "||" << endl << "\t||";
			}
			else if (i <= 10)
				std::cout << 0 << i - 1 << "||" << endl << "\t||";
			else
				std::cout << i - 1 << "||" << endl << "\t||";
		}
		else {
			if (sourceSelected[i - 1] == 'X' && source[i - 1] == 'T')
			{
				setConsoleColor(_colorGreen, "XX");
				cout << " ";
			}
			else if (sourceSelected[i - 1] == 'X') {
				setConsoleColor(_colorPurple, "XX");
				cout << " ";
			}
			else if (i <= 10)
				cout << 0 << i - 1 << " ";
			else
				cout << i - 1 << " ";
		}
		
	}
	
for (int i = 0; i < _sizeOfBoard / 10 + 5; i++)
	std::cout << "==";

}
/// metody odpowiedzialne za wprowadzanie danych 
/// -- nie uzywane
int getSuspectedPostionShip() {
	int shipPostion = 0;
	char ch;

	std::cout << endl << "Wprowadz pozycje statku przeciwnika " << endl;
	while (!(std::cin >> shipPostion) || (shipPostion > 100 || shipPostion < 0))
	{
		std::cin.clear();
		while (std::cin.get(ch) && ch != '\n')
			continue;
		std::cout << "Podaj Ponownie " << endl;
	}
	return shipPostion;
}
/// -- nie uzywane
bool input(char* opponnetBoard, int& numShips, char* sourceSelected) {

	int postion = getSuspectedPostionShip();
	sourceSelected[postion] = 'X';

	while (opponnetBoard[postion] == 'X' && numShips > 0)
	{
		numShips--;
		if (numShips <= 0)
			return true;

		opponnetBoard[postion] = ' ';
		std::cout << "Trafi³es w przeciwnik statek !" << endl;
		std::cout << "Masz nastepny ruch" << endl;

		postion = getSuspectedPostionShip();
		sourceSelected[postion] = 'X';
	}
	std::cout << "Nie udalu ci sie trafic w statek przeciwnika" << endl;
	std::cout << "TERAZ RUCH KOLEJNEGO GRACZA" << endl;
	return false;
}

/// metoda odpowiedzialna za wprowadzanie wartosci z konsoli oraz podstawowa validacje danych
/// jest ona syntez¹ dwoch poprzednich metod
int inputWithValidation(char* sourceSelected) {
	int shipPostion = 0;
	char ch = '0';
	bool areaAlreadyTaken = false;
	std::cout << endl << "\n----- Wprowadz pozycje statku przeciwnika " << endl;
	do {
		while (!(std::cin >> shipPostion) || (shipPostion > 100 || shipPostion < 0))
		{
			std::cin.clear();
			while (std::cin.get(ch) && ch != '\n')
				continue;
			std::cout << "Podaj ponownie nieprawidlowa liczba " << endl;
		}
		if (sourceSelected[shipPostion] == 'X')
		{
			areaAlreadyTaken = true;
			std::cout << "Juz podales taki punkt:" << shipPostion << endl;
			std::cout << "Podaj Ponownie" << endl;
		}
		else
			areaAlreadyTaken = false;
	} while (areaAlreadyTaken);

	return shipPostion;
}

/// glowna gra
int main() {

	srand(time(NULL));
	bool _gameEnd = false;
	bool blueWinner = false;
	int round = 1;
	bool nextTry = false;
	string  namePlayerX,
		namePlayerY;

	/// inicializacja obszaru gry losowymi statkami dla obydwu graczy
	do {
		numberOfShipsPlayerX = initlizeBoard(boardGamePlayerX);
		numberOfShipsPlayerY = initlizeBoard(boardGamePlayerY);
	} while (numberOfShipsPlayerX != numberOfShipsPlayerY || numberOfShipsPlayerX < 15);

	
	/// rysowanie menu gry
	drawingMenuGame(namePlayerX, namePlayerY);
	system("cls");

	//.. glowna petla z gra
	while (!_gameEnd) {

		// ruchy gracza niebieskiego
		do {
			std::cout << "Tura nr: " << round << " . Ruch gracz X (niebieski) " << namePlayerX << endl << endl;
			drawingBoard(boardGamePlayerX, namePlayerX, numberOfShipsPlayerX, _colorBlue);
			drawingOpponentBoard(postionsSelectedByX, boardGamePlayerY, namePlayerY, numberOfShipsPlayerY, _colorRed);

			int area = inputWithValidation(postionsSelectedByX);
			postionsSelectedByX[area] = 'X';

			if (boardGamePlayerY[area] == 'X') {
				numberOfShipsPlayerY--;
				if (numberOfShipsPlayerY == 0)
				{
					_gameEnd = true;
					blueWinner = true;
					nextTry = false;
					setConsoleColor(_colorGreen, "To byl ostatni statek przeciwnika"
						" wygrales !!!");
				}
				else {
					boardGamePlayerY[area] = 'T';
					std::cout << "Trafiles w przeciwnika statek !" << endl;
					std::cout << "Masz nastepny ruch" << endl;
					nextTry = true;
				}
			}
			else
			{
				std::cout << "Nie udalo ci sie trafic w przeciwnika statek" << endl;
				std::cout << "Ruch ma nastepny gracz" << endl;
				nextTry = false;
			}
			Sleep(3000);
			system("cls");
		} while (nextTry);

		if (_gameEnd == true)
			break;

		// ruchy gracza czerwonego
		do {
			std::cout << "Tura nr: " << round << " . Zaczyna gracz X (czerwony) " << namePlayerY << endl << endl;
			drawingBoard(boardGamePlayerY, namePlayerY, numberOfShipsPlayerY, _colorRed);
			drawingOpponentBoard(postionsSelectedByY, boardGamePlayerX, namePlayerX, numberOfShipsPlayerX, _colorBlue);
			int area = inputWithValidation(postionsSelectedByY);

			postionsSelectedByY[area] = 'X';
			if (boardGamePlayerX[area] == 'X') {
				numberOfShipsPlayerX--;
				if (numberOfShipsPlayerX == 0) {
					_gameEnd = true; 
					blueWinner = false;
					nextTry = false;
					setConsoleColor(_colorGreen, "To byl ostatni statek przeciwnika"
						" wygrales !!!");
				}
				else {
					boardGamePlayerX[area] = 'T';
					std::cout << "Trafiles w przeciwnika statek !" << endl;
					std::cout << "Masz nastepny ruch" << endl;
					nextTry = true;
				}
			}
			else {
				std::cout << "Nie udalo ci sie trafic w przeciwnika statek" << endl;
				std::cout << "Ruch ma nastepny gracz" << endl;
				nextTry = false;
			}
			Sleep(3000);
			system("cls");
		} while (nextTry);

		round++;
	}

	std::cout << "Gra zakonczona wygral";
	if (blueWinner) {
		cout << " gracz niebieski \n\t ->> ";
		setConsoleColor(_colorBlue, namePlayerX + '\n');
	}
	else
	{
		cout << " gracz czerwony \n\t ->> ";
		setConsoleColor(_colorRed, namePlayerY + '\n');
	}
	cout << "Gra zajela " << round << " runde" << endl;
	std::cout << "Nacisnij dowolny klawisz aby zakonczyc gre" << endl;
	std::cin.get();

	return 0;
}