#include <iostream>
#include <list>
#include <thread>
#include <mutex>
using namespace std;
list<string> Ingredienti;
mutex m;
string nome_ricetta;
void inserisci_ordine(string ricetta){
  m.lock();
    cout<<"Ordine per:"<<ricetta<<endl;
    int i = 0;
    while(i == 0){
        string ingrediente = "";
        cout<<"Ingrediente:"<<endl;
        cin>>ingrediente;
        if(ingrediente == "fine"){
            i++;
            break;
        }
        Ingredienti.push_back(ingrediente);
    }
  m.unlock();
}

void prepara_ricetta(string ricetta)
{
  m.lock();
  cout<<"Preparazione di:"<< ricetta<<endl;
  int size = Ingredienti.size();
  for(int i = 0; i < size; i++){
    cout<<Ingredienti.front()<<endl;
    Ingredienti.pop_front();
  }
  m.unlock();
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
