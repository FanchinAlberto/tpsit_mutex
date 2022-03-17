#include <iostream>
#include <list>
#include <thread>
#include <mutex>
using namespace std;
list<string> Ingredienti;
mutex m; //semaforo binario per controllare gli accessi
string nome_ricetta;

void inserisci_ordine(string ricetta){
  m.lock(); //blocco la risorsa
    cout<<"Ordine per:"<<ricetta<<endl;
    int i = 0;
    while(i == 0){ //inserimento ordine
        string ingrediente = "";
        cout<<"Ingrediente:"<<endl;
        cin>>ingrediente;
        if(ingrediente == "fine"){
            i++;
            break;
        }
        Ingredienti.push_back(ingrediente);
    }
  m.unlock(); //sbolocco la risorsa
}

void prepara_ricetta(string ricetta)
{
  m.lock(); //blocco la risorsa
  cout<<"Preparazione di:"<< ricetta<<endl;
  int size = Ingredienti.size();
  for(int i = 0; i < size; i++){ //stampo gli ingredienti
    cout<<Ingredienti.front()<<endl;
    Ingredienti.pop_front();
  }
  m.unlock(); //sblocco la risorsa
}
void ordina(string ricetta){
  inserisci_ordine(ricetta);
  prepara_ricetta(ricetta);
}
int main() {
  thread uno(ordina, "Prosciutto Funghi");
  thread due(ordina,"Cetrioli");
  uno.join();
  due.join();
  return 0;
}
