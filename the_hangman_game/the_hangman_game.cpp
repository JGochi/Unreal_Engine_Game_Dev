#include <iostream>
#include <fstream> //Praca z plikami
#include <vector> //Wektor
#include <string> //String
#include <cstdlib> //Generacja losowych liczb
#include <ctime> //Generacja losowych liczb

using namespace std;

//Zmienne globalne
vector<string> wordPool; //S�owa z pliku txt
string selectedWord;
string displayedWord;

int attemptsLaft = ;
bool exitGame = false;
bool gameWon = false;

void Initialize();
void LoadWordsFromFile();
void DrawnWord();
void GetInput()
void UpdateGame();
void Render();
void ShutDown();



int main()
{
	Initialize(); //Przygotowanie

	while (!exitGame)
	{
		GetInput(); //Pobranie odpowiedzi od u�ytkownika
		Render(); //Bie��cy stan
	}

	ShutDown(); //Koniec

	return 0;
}

void Initialize()
{
	LoadWordsFromFile();
	DrawnWord();
}

void LoadWordsFromFile()
{
	//Za�adowanie s��w z pliku hasla_do_gry.txt}
}

void DrawnWord()
{
	//Losowanie s�owa z puli
}

void GetInput()
{
	//Pobranie litery od u�ytkownika
}

void UpdateGame(char guess)
{
	//Sprawdza, czy litera jest w selectedWord
}

void Render()
{
	//Wy�wietla bie��cy stan
}

void ShutDown()
{
	//Komunikat o zako�czeniu gry
}