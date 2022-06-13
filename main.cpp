#include<iostream>
#include"kolko_i_krzyzyk.hh"

using namespace std;

int main(){
  int ile;
  int rozmiar;
  char start;


  cout<<"Aby zagrac w kolko i krzyzyk musisz zdefiniowac rozmiar planszy oraz ilosc znakow w rzędzie potrzebnych, by wygrac."<<endl;
  cout<<"Rozmiar planszy (nxn)  n=";
  cin>>rozmiar;
  cout<<endl<<"Ilosc znakow w rzedzie potrzebnych, by wygrac i=";
  cin>>ile;

  cout<<"Pola na planszy numerowane sa od 1 do "<<rozmiar*rozmiar<<"."<<endl;


  KolkoIKrzyzyk gra (rozmiar, ile);
  cout<<"Rozpoczynamy gre? (T=TAK)";
  cin>>start;
  if((start=='T')||(start=='t'))
      gra.ObslugaGry();

}
