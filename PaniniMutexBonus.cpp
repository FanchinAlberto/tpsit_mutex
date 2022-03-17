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

void inserisci_ordine(string ricetta) //funzione per inserire gli ordini
{
	ordina.lock(); //blocco il mutex degli ordini
	cout << "Ordine per:" << ricetta << endl;
	cout << "Inserire il numero di ingredienti:" << endl;
	int numero_ingredienti;
	cin >> numero_ingredienti;
	for (int i = 0; i < numero_ingredienti; i++) //faccio inserire all'utente gli ingredienti
	{
		string ingrediente = "";
		cout << "Ingrediente:" << endl;
		cin >> ingrediente;
		Ingredienti.push_back(ingrediente);
	}
	prepara.unlock(); //sblocco il mutex del cuoco
	Ricetta = ricetta; //valorizzo la variabile globale con il nome della ricetta
}

void prepara_ricetta()
{
	while (works == true)//fiche i thread degli ordini non finiscono il cuoco continua a preparare gli ordini
	{
		prepara.lock(); //blocco il mutex del cuoco
		cout << "Ricetta:" << Ricetta << endl;
		int size = Ingredienti.size();
		for (int i = 0; i < size; i++)
		{
			cout << Ingredienti.front() << endl;
			Ingredienti.pop_front();
		}
		ordina.unlock(); //sblocco il mutex degli ordini
	}
}

int main()
{
	thread uno(inserisci_ordine, "Prosciutto Funghi"); //primo thread
	thread due(inserisci_ordine, "Cetrioli"); //secondo thread
	thread cuoco(prepara_ricetta);
	prepara.lock(); //blocco il cuoco in modo che non inizi a lavorare prima che il primo ordine sia inserito
	uno.join();
	due.join();
	works = false; //gli ordini sono finiti, blocco il cuoco
	cuoco.join();
	return 0;
}
