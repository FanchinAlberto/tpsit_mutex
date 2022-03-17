#include <iostream>
#include <list>
#include <thread>
#include <mutex>
using namespace std;
list<string> Ingredienti;
mutex prepara;
mutex ordina;
bool works = true;
string Ricetta;

void inserisci_ordine(string ricetta)
{
	ordina.lock();
	cout << "Ordine per:" << ricetta << endl;
	cout << "Inserire il numero di ingredienti:" << endl;
	int numero_ingredienti;
	cin >> numero_ingredienti;
	for (int i = 0; i < numero_ingredienti; i++)
	{
		string ingrediente = "";
		cout << "Ingrediente:" << endl;
		cin >> ingrediente;
		Ingredienti.push_back(ingrediente);
	}
	prepara.unlock();
	Ricetta = ricetta;
}

void prepara_ricetta()
{
	while (works == true)
	{
		prepara.lock();
		cout << "Ricetta:" << Ricetta << endl;
		int size = Ingredienti.size();
		for (int i = 0; i < size; i++)
		{
			cout << Ingredienti.front() << endl;
			Ingredienti.pop_front();
		}
		ordina.unlock();
	}
}

int main()
{
	thread uno(inserisci_ordine, "Prosciutto Funghi");
	thread due(inserisci_ordine, "Cetrioli");
	thread cuoco(prepara_ricetta);
	prepara.lock();
	uno.join();
	due.join();
	works = false;
	cuoco.join();
	return 0;
}