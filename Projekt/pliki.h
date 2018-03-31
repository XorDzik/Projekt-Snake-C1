#ifndef PLIKI_H_INCLUDED
#define PLIKI_H_INCLUDED
/*!
* \file
* \brief Naglowki
* Plik zawiera deklaracje bibliotek niezbednych do funkcjonowania programu, deklaracje stalych,
* zmiennych, bitmap, mapy, typow wyliczeniowych oraz funkcji.
*
*/

#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*!
* \brief Stale
* Stala przechowujaca informacje o wyskosci mapy
*
*/
#define WYSOKOSC_MAPY 48
/*!
* \brief Stale
* Stala przechowujaca informacje o szerokosci mapy
*
*/
#define SZEROKOSC_MAPY 64
/*!
* \brief Stale
* Stala przechowujaca informacje o mnozniku
*
*/
#define MNOZNIK 10

/*!
* \brief Licznik
* Deklaracja zmiennej licznik z przydomkiem volatile w celu wylaczenia stosowanej prze kompilator optymalizacji
*
*/
volatile int licznik;
/*!
* \brief Tick
* Deklaracja zmiennej tick z przydomkiem volatile w celu wylaczenia stosowanej prze kompilator optymalizacji
*
*/
volatile int tick;
/*!
* \brief Klatki
* Deklaracja zmiennej klatki z przydomkiem volatile w celu wylaczenia stosowanej prze kompilator optymalizacji
*
*/
volatile int klatki;
/*!
* \brief resting
* Deklaracja zmiennych resting z przydomkiem volatile w celu wylaczenia stosowanej prze kompilator optymalizacji
*
*/
volatile int resting;
/*!
* \brief rested
* Deklaracja zmiennej rested z przydomkiem volatile w celu wylaczenia stosowanej prze kompilator optymalizacji
*
*/
volatile int rested;

/** @brief Lock Variable
* Funkcja przydzielajace pamiec na zmienna licznik za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/

LOCK_VARIABLE(licznik);

/** @brief Lock Variable
* Funkcja przydzielajace pamiec na zmienna klatki za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/

LOCK_VARIABLE(klatki);

/** @brief Lock Variable
* Funkcja przydzielajace pamiec na zmienna tick za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/
LOCK_VARIABLE(tick);

/** @brief Lock Variable
* Funkcja przydzielajace pamiec na zmienna resting za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/
LOCK_VARIABLE(resting);

/** @brief Lock Variable
* Funkcja przydzielajace pamiec na zmienna rested za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/
LOCK_VARIABLE(rested);

/** @brief Lock Function
*
* Funkcja przydzielajaca pamiec na timer1 za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/

LOCK_FUNCTION(timer1);

/** @brief Lock Function
*
* Funkcja przydzielajaca pamiec na rest1 za pomoca specjalnych makr
* @return Funkcja niczego nie zwraca
*/
LOCK_FUNCTION(rest1);

/** @brief Mapa
*
* Deklaracja tablicy za pomoca ktorej rysowana jest mapa
*
*/
int Mapa[WYSOKOSC_MAPY][SZEROKOSC_MAPY];

/*!
* \brief Bitmapy
* Deklaracja wskaznika na bitmape, na ktorej toczy sie gra
*
*/
BITMAP *bufor;
/*!
* \brief Bitmapy
* Deklaracja wskaznika na bitmape, na ktorej rysowana jest instrukcja
*
*/
BITMAP *bufor1;
/*!
* \brief Bitmapy
* Deklaracja wskaznika na bitmape, na ktorej rysowany jest komunikat o bledzie
*
*/
BITMAP *bufor2;
/*!
* \brief Bitmapy
* Deklaracja wskaznika na bitmape, na ktorej rysowana jest instrukcja sterowania
*
*/
BITMAP *bufor3;
/*!
* \brief Bitmapy
* Deklaracja wskaznika na bitmape, na ktorej rysowany jest waz
*
*/
BITMAP *snejk;

/*!
* \brief Kierunki ruchu
*
* Wartosci zapisane w tym typie sluza do okreslenia kierunku poruszania sie "weza"
*/
typedef enum
{
    lewo = 0, prawo, gora, dol
} direction;

/*!
* \brief Obiekty
* Przechowuje wartosci "owocow", "weza", oraz nic.
*
*/
typedef enum
{
    nic = 0, cytrynka, snake, jabluszko, truskawka
} object;
/*!
* \brief Elementy ciala weza
* Struktura przechowuje zmienna w ktorej zapisany jest kierunek ruchu weza oraz jego aktualne wspolrzedne.
* Zawiera takze wskaznik na nastepny element ciala weza.
*
*/
typedef struct snake_node
{
    int kierunek;
    int x;
    int y;
    struct snake_node *next;
} snake_node;

void timer1(void);
void rest1(void);
void Losuj_Cytrynke();
void Losuj_Jabluszko();
void Losuj_Truskawki();
void Info();
void Sterowanie();
void Strona_glowna();

#endif // PLIKI_H_INCLUDED
