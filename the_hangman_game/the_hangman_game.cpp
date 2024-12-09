#include <iostream>
#include <fstream> //Praca z plikami
#include <vector> //Wektor
#include <string> //String
#include <cstdlib> //Generacja losowych liczb
#include <ctime> //Generacja losowych liczb

using namespace std;

//Zmienne globalne
vector<string> wordPool; //S³owa z pliku txt
string drawnWord;
string displayedWord;

int attemptsLeft = 5;
bool exitGame = false;
bool gameWon = false;

//Update no.1 - Dodanie zmiennych do systemu punktacji
int score = 0;
time_t startTime;

//Update no.2 - Pobranie nazwy gracza 
string playerName;

void Initialize();
void LoadWordsFromFile(const string& filename);
void DrawnWord();
void GetInput();
void UpdateGame(char playerGuess);
void Render();
void ShutDown();
void SaveScore();
void LeaderBoard(); //Update no.3 - wczytanie tablicy wyników

int main()
{
	Initialize(); //Przygotowanie

	while (!exitGame)
	{
		GetInput(); //Pobranie odpowiedzi od u¿ytkownika
		Render(); //Bie¿¹cy stan
	}

	LeaderBoard(); // Update no.3 - Wyœwietlona tablica wyników
	ShutDown(); //Koniec
	//SaveScore(); //Update no.2 - Zapis wyników w pliku
	//UPDATE - w finalnej wersji SveScore jeest realizowane w LeaderBoard

	return 0;
}

void Initialize()
{
	cout << "Welcome to The Hangman Game!" << endl;

	cout << "Enter your name: ";
	cin >> playerName;

	cout << "Loading words..." << endl;
	LoadWordsFromFile("hasla_do_gry.txt");

	if (wordPool.empty()) //Sprawdzenie czy w pliku s¹ s³owa
	{
		cout << "No words were found in the file!" << endl;
		exitGame = true;
		return;
	}

	DrawnWord();

	displayedWord = string(drawnWord.size(), '_');

	cout << "The game started! You have " << attemptsLeft << " attempts to guess correct letters." << endl;
	cout << "Current Word: " << displayedWord << endl;

	startTime = time(nullptr);
}

void LoadWordsFromFile(const string& filename)
{
	//Za³adowanie s³ów z pliku hasla_do_gry.txt
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "The file has not been opened." << endl;
		exitGame = true;
		return;
	}

	string word;
	while (file >> word) //Zastosowanie operatora strumienia
	{
		wordPool.push_back(word);
	}
	file.close();
}

void DrawnWord()
{
	//Losowanie s³owa z puli
	srand(static_cast<unsigned int>(time(nullptr))); //Losowoœæ w oparciu o aktualny czas w sekundach
	int index = rand() % wordPool.size();
	drawnWord = wordPool[index];
}

void GetInput()
{
	//Pobranie litery od u¿ytkownika
	char playerGuess;
	cout << "Enter your guess: ";
	cin >> playerGuess;
	playerGuess = toupper(playerGuess); //Przekszta³ca znak na wielk¹ literê, jeœli to mo¿liwe
	UpdateGame(playerGuess);
}

void UpdateGame(char guess)
{
	//Sprawdza, czy litera jest w selectedWord
	bool correctGuess = false;

	for (int i = 0; i < drawnWord.size(); ++i)
	{
		if (drawnWord[i] == guess && displayedWord[i] != guess)
		{
			displayedWord[i] = guess;
			correctGuess = true;
		}
	}

	if (!correctGuess)
	{
		//Niepoprawny traf. Zmniejsza iloœæ prób
		cout << "Wrong guess! Attempts left: " << --attemptsLeft << endl;
	}
	else
	{
		cout << "Good guess!" << endl;
	}

	if (displayedWord == drawnWord)
	{
		gameWon = true;
		exitGame = true;
	}

	if (attemptsLeft == 1)
	{
		cout << "This is your last chance!" << endl;
	}

	if (attemptsLeft <= 0)
	{
		cout << "You have no attempts left!" << endl;
		exitGame = true;
	}
}

void Render()
{
	//Wyœwietla bie¿¹cy stan
	cout << endl;
	cout << "Current word: " << displayedWord << endl;

	if (gameWon)
	{
		time_t endTime = time(nullptr);
		double timeTaken = difftime(endTime, startTime);

		//Update no. 1 - PUNKTACJA
		// 10 pkt za pozosta³e szanse
		// 0-100 pkt za pozosta³y czas, poni¿ej 0 nie ma ujemnych pkt
		score = (attemptsLeft * 10) + max(0, 100 - static_cast<int>(timeTaken));

		cout << "You guessed the word correctly! The word was: " << drawnWord << endl;
		cout << "Your score: " << score << endl;
	}
	else if (exitGame)
	{
		cout << "Game over! The correct word was: " << drawnWord << endl;
	}
}

void ShutDown()
{
	//Komunikat o zakoñczeniu gry
	cout << "Thank you for playing The Hangman." << endl;
}

void SaveScore()
{
	//Zapis wyniku w pliku tablica_wynikow.txt
	ofstream file("tablica_wynikow.txt", ios::app); //Dopisanie danych do pliku bez nadpisania tych istniej¹cych

	if (file.is_open())
	{
		file << "Player name: " << playerName << " | Score: " << score << endl;
		file.close();
	}
	else
	{
		cout << "Failed to open the leaderboard file." << endl;
	}
}

void LeaderBoard()
{
	SaveScore();

	cout << endl;
	cout << "--- Leaderboard ---" << endl;

	// Otwieramy plik do odczytu
	ifstream file("tablica_wynikow.txt");
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			cout << line << endl; // Wyœwietlenie ka¿dej linii
		}
		file.close();
	}
	else
	{
		cout << "Failed to open the leaderboard file." << endl;
	}

	cout << "-------------------" << endl;
}
