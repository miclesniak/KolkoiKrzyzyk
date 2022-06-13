#include <iostream>
#include "kolko_i_krzyzyk.hh"
#define INFINITY 2147483647 
using namespace std;

void KolkoIKrzyzyk::RysujPlansze(){
  int i, j;
  cout <<endl<<endl;
  cout<<"#############################################################"<<endl;
  cout<<"#______________________KOLKO I KRZYZYK______________________#"<<endl;
  cout<<"#_________________ X - KOMPUTER, O - GRACZ _________________#"<<endl;
  cout<<"#___________________________________________________________#"<<endl;
  cout<<"#_________ABY WYGRAC MUSISZ ULOZYC "<<ile_zeby_wygrac<<" ZNAKI W RZEDZIE________#"<<endl;
  cout<<"#############################################################"<<endl<<endl;
  
  for(i = 1; i <= rozmiar*rozmiar+1; i++){
    cout<<" "<<tablicagry[i]<<" ";
    if(i % rozmiar)
      cout << "|";
    else if (i!= rozmiar*rozmiar && i!=0){
      cout<<endl;
      for(j=0; j<rozmiar;  j++)
	cout<<"--- ";
      cout<<endl;
    }
    else
      cout<<endl<<endl<<endl;  
  }    
}

bool KolkoIKrzyzyk::CzyWygrana(char gracz, bool cisza){
  bool test;
  int i,k,j;
  int ile_zliczono=0;

  test = false;

  // Sprawdzamy wiersze
  for(k=0; k<rozmiar; k++){ //
    for(i=k*rozmiar+1; i<k*rozmiar+rozmiar-ile_zeby_wygrac+2;i++){//start
      for(j=0; j<ile_zeby_wygrac;j++){
	if(tablicagry[i+j]==gracz)
	  ile_zliczono++;
      }
      if(ile_zliczono == ile_zeby_wygrac)
	test=true;
      else
          ile_zliczono=0;
    }
  }
  
  // Sprawdzamy kolumny
  if(test==false){
    for(i=1; i<rozmiar*(rozmiar-ile_zeby_wygrac+1)+1; i++){
      for(j=0; j<ile_zeby_wygrac; j++){
	if(tablicagry[i+j*rozmiar]==gracz)
	  ile_zliczono++;
      }
      if(ile_zliczono == ile_zeby_wygrac)
	test=true;
      else
          ile_zliczono=0;
    }
  }
  // Sprawdzamy przekątną prawo w dol
  if(test==false){
    for(k=0; k<rozmiar-ile_zeby_wygrac+1;k++){//wiersz
      for(i=k*rozmiar+1; i<k*rozmiar+rozmiar-ile_zeby_wygrac+2;i++){//start
	for(j=0; j<ile_zeby_wygrac; j++){
	  if(tablicagry[i+rozmiar*j+j]==gracz)
	    ile_zliczono++;
	}
	if(ile_zliczono == ile_zeby_wygrac)
	  test=true;
	else
        ile_zliczono=0;      }
    }
  }

  // Sprawdzamy przekątną lewo w dol
  if(test==false){
    for(k=0; k<rozmiar-ile_zeby_wygrac+1;k++){//wiersz
      for(i=k*rozmiar+ile_zeby_wygrac; i<k*rozmiar+rozmiar+1; i++){//start
	for(j=0; j<ile_zeby_wygrac; j++){
	  if(tablicagry[i+j*rozmiar-j]==gracz)
	    ile_zliczono++;
	}
	if(ile_zliczono == ile_zeby_wygrac)
	  test=true;
	else
        ile_zliczono=0;
      }
    }
  }

  if(test==true){
    if(cisza==false){
      RysujPlansze();
      cout << "\nGRACZ " << gracz << " WYGRYWA!!!\n\n";
    }
    return true;
  }
  return false;
}

bool KolkoIKrzyzyk::CzyRemis(bool cisza){
  int i;
  
  for(i=1; i<rozmiar*rozmiar+1; i++)
    if(tablicagry[i]==' ')
      return false; // jest puste pole?


  if(cisza==false){
    RysujPlansze();
    cout << "\nREMIS !!!\n\n";
  }
  return true;
}




int KolkoIKrzyzyk::AlfaBeta(char gracz, int alfa, int beta){
  int i;
  int r, x;
  int pomoc;


  if(CzyWygrana(gracz, true)){
    if(gracz=='X')
      return 1;
    else
      return -1;
  }

  if(CzyRemis(true))
    return 0;


  if(gracz=='X')
    gracz='O';
  else
    gracz='X';

  
  if(gracz=='X'){
    r=-INFINITY;
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	    tablicagry[i]=gracz;
	    pomoc=max(r, alfa);
	    x=AlfaBeta(gracz, pomoc, beta);
	    tablicagry[i]=' ';
	    if(x>=beta)
	     return x;
	    r=max(r, x);
      }
    }
  }
  else{//ruch czlowieka
    r=INFINITY; // ta tez...
    for(i=1; i<rozmiar*rozmiar+1;i++){
      if(tablicagry[i]==' '){
	tablicagry[i]=gracz;
	pomoc=min(r, beta);
	x=AlfaBeta(gracz, alfa, pomoc);
	tablicagry[i]=' ';
	if(x<=alfa)
	  return x;
	r=min(r,x);
      }
    }
  }
  return r;
}


int KolkoIKrzyzyk::RuchKomputera(){
  int ruch, i, wynik;
  int max;
  max=-10;


  
  for(i = 1; i < rozmiar*rozmiar+1; i++){
    if(tablicagry[i] == ' '){
      tablicagry[i] = 'X';
      wynik=AlfaBeta('X', -INFINITY, INFINITY);
      tablicagry[i] = ' ';
      if(wynik > max){
          max = wynik;
          ruch = i;
      }
    }
  }

  return ruch;
}


void KolkoIKrzyzyk::Ruch(char &gracz){
  int ruch;
  int licznik = 0;

  RysujPlansze();

  if(gracz == 'O'){ //kolej czlowieka
    cout << "\nRuch: ";
    cin >> ruch;
  }
  else{
    ruch = RuchKomputera();
  }
  
  while(!((ruch >= 1) && (ruch < rozmiar*rozmiar+1) && (tablicagry[ruch] == ' ')))
  {
      cout << "\n Nie dostepne Pole! Sprobuj ponownie. Ruch: ";
      cin >> ruch;
  }
  tablicagry[ruch] = gracz;
  gracz = (gracz == 'O') ? 'X' : 'O';
}

KolkoIKrzyzyk::KolkoIKrzyzyk(int rozm, int ile){
  int i;
  
  rozmiar=rozm;
  ile_zeby_wygrac=ile;

  tablicagry=new char[rozmiar*rozmiar+1];
  for(i=0; i<rozmiar*rozmiar+1; i++)
    tablicagry[i]=' ';
}

void KolkoIKrzyzyk::CzyscPlansze(){
  int i;
  for (i=0; i<rozmiar*rozmiar+1; i++)
    tablicagry[i]=' ';
}

void KolkoIKrzyzyk::ObslugaGry(){
  char wybor;
  char gracz;

  do {
    gracz='O';
    CzyscPlansze();
    while(!CzyWygrana('X', false) && !CzyWygrana('O', false) && !CzyRemis(false))
      Ruch(gracz);
   
    cout<<"Jeszcze raz? (T=TAK) ";
    cin>>wybor;
   
   
  } while((wybor=='T')||(wybor=='t'));
 
}

