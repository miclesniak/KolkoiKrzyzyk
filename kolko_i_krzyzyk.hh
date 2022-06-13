#ifndef KOLKO_I_KRZYZYK_HH
#define KOLKO_I_KRZYZYK_HH


class KolkoIKrzyzyk{
  int rozmiar;
  int ile_zeby_wygrac;
  char* tablicagry;


public:
  KolkoIKrzyzyk(int rozm, int ile);
  void ObslugaGry();
private:
  void RysujPlansze();
  bool CzyWygrana(char gracz, bool cisza);
  bool CzyRemis(bool cisza);
  int AlfaBeta(char gracz, int alfa, int beta);
  int RuchKomputera();
  void Ruch(char &gracz);
  void CzyscPlansze();

};
#endif
