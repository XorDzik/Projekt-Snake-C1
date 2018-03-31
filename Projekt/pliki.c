#include "pliki.h"
/*!
* \file
* \brief Ciala Funkcji
* Plik zawiera ciala funkcji sluzacych do obslugi timera oraz wyswietlania tekstu w menu
*
*/

/** @brief timer1
*
* Funkcja inkrementuje zmienna licznik, przypisuje zmiennej klatki wartosc zmiennnej tick, przypisuje zmiennej tick
* wartosc zero, oraz zmiennej rested przypisuje wartosc zmiennej resting
* @param[in] void
* @return Funkcja niczego nie zwraca
*/
void timer1(void)
{
    licznik++;
    klatki = tick;
    tick=0;
    rested=resting;
}
END_OF_FUNCTION(timer1)
/** @brief rest1
*
* Funkcja inkrementuje zmienna resting
* @param[in] void
* @return Funkcja niczego nie zwraca
*/
void rest1(void)
{
    resting++;
}
/** @brief Informacja
*
* Funkcja opisuje na czym polega gra, co powoduje zjedzenie poszczegolnych "owocow"
* @return Funkcja niczego nie zwraca
*/
void Info()
{
    textout_ex( screen, font, "                   Instrukcja roztropnego gracza:", 20, 20, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Gre rozpoczynasz poruszajac sie wezem w kolorze turkusowym, zjadajac", 40, 40, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "zolte cytrynki zwiekszasz liczbe swoich punktow o 1,", 40, 60, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Za kazde zjedzone jabluszko otrzymasz premie w postaci 10 ptk extra!", 40, 80, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Jednakze powoduje ono gwaltowne wydluzenie twojego", 40, 100, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "ciala oraz zwiekszenie predkosci dwu i pol krotnie!", 40, 120, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Uratowac Cie od tej zawrotnej predkosci moze tylko", 40, 140, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "i wylacznie zjedzenie czerwonej truskawki ktora leczy i przywraca", 40, 160, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Twoja predkosc do stanu wyjsciowego.", 40, 180, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "W grze chodzi o zjedzenie jak najwiekszej ilosci zoltych", 40, 200, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "cytrynek oraz zielonych jabluszek a co za tym idzie", 40, 220, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "zdobycie jak najwiekszej ilosci punktow.", 40, 240, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Zyczymy mocnych wrazen oraz satysfakcjonujacej liczby punktow", 40, 260, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Aby rozpoczac nacisnij klawisz 2 aby zakonczyc gre", 40, 300, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "nacisnij klawisz Esc", 40, 320, makecol(255, 0, 255), -1);
}
/** @brief Strona glowna
*
* Funkcja pokazuje opis menu.
* @return Funkcja niczego nie zwraca
*/
void Strona_glowna()
{
    textout_ex( screen, font, "                   Witamy w grze Snake i jego ogromny sad!:", 20, 60, makecol(0, 0, 255), -1);
    textout_ex( screen, font, "1. Informacje o grze", 20, 80, makecol(0, 0, 255), -1);
    textout_ex( screen, font, "2. Rozpocznij przygode", 20, 100, makecol(0, 0, 255), -1);
    textout_ex( screen, font, "3. Sterowanie", 20, 120, makecol(0, 0, 255), -1);
    textout_ex( screen, font, "Esc. Zakoncz gre", 20, 140, makecol(0, 0, 255), -1);

}
/** @brief Sterowanie
*
* Funkcja instruuje gracza jak nalezy poruszac sie wezem
* @return Funkcja niczego nie zwraca
*/
void Sterowanie(){
    textout_ex( screen, font, "                               Sterowanie:", 20, 60, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "                        Wezem poruszasz sie strzalkami", 20, 80, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Nacisniecie strzalki w gore powoduje, ze waz zaczyna poruszac sie w gore", 20, 100, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Nacisniecie strzalki w dol powoduje, ze waz zaczyna poruszac sie w dol", 20, 120, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Nacisniecie strzalki w lewo powoduje, ze waz zaczyna poruszac sie w lewo", 20, 140, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Nacisniecie strzalki w prawo powoduje, ze waz zaczyna poruszac sie w prawo", 20, 160, makecol(255, 0, 255), -1);
    textout_ex( screen, font, "Aby rozpoczac gre nacisnij 2, aby zakonczyc nacisnij ESC", 20, 200, makecol(255, 0, 255), -1);
}
/** @brief Losowanie cytrynek
*
* Funkcja losuje "cytryne" w pseudolosowym miejscu na mapie w ktorym aktualnie znajduje sie puste pole
* @return Funkcja niczego nie zwraca
*/
void Losuj_Cytrynke()
{
    int losuj_y, losuj_x;
    do
    {
        losuj_y = (int)(rand()%24);
        losuj_x = (int)(rand()%32);
    }
    while (Mapa[losuj_y][losuj_x] != nic); // Losuj na odpowienich wspolrzednych cytrynki kiedy ich nie ma;
    Mapa[losuj_y][losuj_x] = cytrynka;       //Prypisz mapie cytrynke ktora wylosowano
}
/** @brief Losowanie jabluszek
*
*  Funkcja losuje "jabluszko" w pseudolosowym miejscu na mapie w ktorym aktualnie znajduje sie puste pole
* @return Funkcja niczego nie zwraca
*/
void Losuj_Jabluszko()
{
    int losuj_y, losuj_x;
    do
    {
        losuj_y = (int)(rand()%24);
        losuj_x = (int)(rand()%32);
    }
    while (Mapa[losuj_y][losuj_x] != nic); // Losuj na odpowienich wspolrzednych cytrynki kiedy ich nie ma;
    Mapa[losuj_y][losuj_x] = jabluszko;       //Prypisz mapie cytrynke ktora wylosowano
}
/** @brief Losowanie truskawek
*
*  Funkcja losuje "truskawke" w pseudolosowym miejscu na mapie w ktorym aktualnie znajduje sie puste pole
* @return Funkcja niczego nie zwraca
*/
void Losuj_Truskawki()
{
    int losuj_y, losuj_x;
    do
    {
        losuj_y = (rand()%24);
        losuj_x = (rand()%32);
    }
    while (Mapa[losuj_y][losuj_x] != nic);
    Mapa[losuj_y][losuj_x] = truskawka;}
