#include "pliki.h"
/*!
* \file
* \brief Funkcja glowna
* Plik zawiera kilka funkcji oraz funkcje glowna w ktorej wystepuje petla obslugujaca gre
*/
void Koniec_Gry();
void Ruch(snake_node* gracz);
snake_node* Ruch_Ciala(snake_node* gracz, int tmp_x, int tmp_y);
void Rysowanie();
/** @brief Funkcja głowna
*
* @return Funkcja niczego nie zwraca
*/
/*!
* \brief Wynik
* Zmienna sluzaca do przechowywania wyniku gracza
*
*/
int wynik = 0;
/*!
* \brief Szybkosc
* Zmienna w ktorej zapisywana jest predkosc z jaka ma sie poruszac waz
*
*/
float szybkosc = 1.0;
/** @brief Funkcja głowna
*
* Funkcja inicjalizuje prace biblioteki allegro oraz tworzy odpowiednie bitmapy na menu, komunikaty, obrazek weza w menu.
* W funkcji znajdują się zabezpieczenia na wypadek gdyby gracz nacisnal nieodpowiedni przycisk w menu, wtedy wyswietlona
* zostanie bitmapa na ktorej pojawi sie komunikat instruujacy gracza jaki klawisz powinien nacisnac aby rozpocząć gre a jaki
* by ją zakonczyc. W funkcji znajduje się rowniez petla while w ktorej obslugiwana jest gra dopoki gracz nie zginie badz
* nie nacisnie klawisza Esc.
* @return Funkcja niczego nie zwraca
*/
int main()
{
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
    clear_to_color(screen, makecol(0,0,0));


    snejk = load_bmp("Waz.bmp", default_palette);
    blit(snejk, screen, 0, 0, 100, 100, snejk->w, snejk->h);
    Strona_glowna();
    readkey();
    clear_to_color(screen, makecol(0,0,0));
    destroy_bitmap(snejk);

    while (!key[KEY_1] && !key[KEY_2] && !key[KEY_ESC] && !key[KEY_3] && !key[KEY_4]){
       bufor2 = create_bitmap(640, 480);
       textout_ex( screen, font, "Podano nieprawidlowy przycisk. W celu rozpoczecia gry", 20, 60, makecol(0, 0, 255), -1);
       textout_ex( screen, font, "wybierz 2, aby ja zakonczyc wybierz Esc", 20, 80, makecol(0, 0, 255), -1);
       readkey();
       clear_to_color(screen, makecol(0,0,0));
       }

    if (key[KEY_1])
    {
        bufor1 = create_bitmap(640, 480);
        clear_to_color(bufor1, makecol(255,0,255));
        Info();
        readkey();
        clear_to_color(screen, makecol(0,0,0));
        destroy_bitmap(bufor1);
    }

    while (!key[KEY_1] && !key[KEY_2] && !key[KEY_ESC] && !key[KEY_3] && !key[KEY_4]){
       bufor2 = create_bitmap(640, 480);
       textout_ex( screen, font, "Podano nieprawidlowy przycisk. W celu rozpoczecia gry", 20, 60, makecol(0, 0, 255), -1);
       textout_ex( screen, font, "wybierz 2, aby ja zakonczyc wybierz Esc", 20, 80, makecol(0, 0, 255), -1);
       readkey();
       clear_to_color(screen, makecol(0,0,0));
       }


    if(key[KEY_3]){
            bufor3 = create_bitmap(640, 480);
            clear_to_color(bufor3, makecol(255,0,255));
            Sterowanie();
            readkey();
            clear_to_color(screen, makecol(255,0,255));
            destroy_bitmap(bufor3);}


    if (key[KEY_2])
    {
        bufor = create_bitmap(640, 480);
        install_timer();
        install_int(timer1, 1000);
        snake_node* gracz = malloc(sizeof(snake_node));
        gracz->kierunek =  lewo;
        gracz->x = SZEROKOSC_MAPY/2;
        gracz->y = WYSOKOSC_MAPY/2;
        gracz->next = NULL;

        int i, j; //Odwolujemy mape do niczego dzieki czemu nie ma warrningow
        for (i = 0; i < WYSOKOSC_MAPY; i++)
        {
            for (j = 0; j < SZEROKOSC_MAPY; j++)
            {
                Mapa[i][j] = nic;
            }
        }

        srand(time(NULL));
        Losuj_Cytrynke();
        Losuj_Jabluszko();
        Losuj_Truskawki();

        while( !key[KEY_ESC])  //Głowna petla gry
        {
            Ruch(gracz);
            Rysowanie();
            tick++;          //inkrementujemy ticki
            resting=0; //Zwalniamy gre kiedy poruszamy sie w dol
            rest_callback(100-szybkosc * 30, rest1); //Ustawiamy predkosc poruszania sie weza // Pozniej jak sie zje okreslony owoc waz bedzie przyspieszal
        }}



    return 0;
}
END_OF_MAIN();
/** @brief Koniec gry
*
*  Funkcja wypisuje na ekranie wynik gracza, oraz konczy dzialanie programu
* @return Funkcja niczego nie zwraca
*/
void Koniec_Gry()
{
    printf("\nKoniec gry. Wynik = %d\n",wynik);
    exit(0);
}
/** @brief Ruch
* Najpierw funkcja sprawdza warunki jezeli zostala wcisnieta lewa strzalka to waz zmienia swoj kierunek ruchu w lewo,
* analogicznie rzecz wyglada jezeli gracz wcisnie strzalke w prawo, gore oraz w doł. Nastepnie tworzone są zmienne pomocnicze
* w ktorych przechowywane sa wspolrzedne gracz x, y. Sprawdzane sa kolejne warunki jezeli gracz wcisnie np prawy przycisk
* i nadal pozostaje na mapie to zmieniany jest kierunek ruchu weza, jezeli wyjdzie poza krawedz mapy nastepuje wywolanie funkcji
* koniec gry i gra sie konczy, analogicznie sprawa sie ma do pozostalych kierunkow ruchu.
* Nastepnie sprawdzany jest warunek, czy waz zjadl cytrynke, jezeli tak to zwieksza sie liczba punktow gracza,
* waz jest powiekszany o jeden element oraz nastepuje losowanie kolejnej "cytrynki". Jezeli waz uderzy w samego siebie to nastepuje
* wywolanie funkcji koniec gry i gra się konczy. Jesli waz zje "jabluszko" to zwiększa się dlugosc jego ciala o 10 elementow,
* liczba punktów równiez sie zwieksza o 10, predkosc jest zwiekszana o 2,5 oraz losowane jest kolejne "jabluszko" i "cytrynka".
* Nastepnie sprawdzany jest warunek czy waz zjadl truskawke, jezeli tak to prędkosc jest zmniejszana do stanu wyjsciowego oraz
* liczba punktow jest zwiekszana o 1. Jezeli zaden z tych warunkow nie zostal spelniony to waz porusza się w dalszym ciągu naprzod.
*
* @param[in] funkcja jako parametr przyjmuje element na cialo weza.
* @return Funkcja niczego nie zwraca
*/
void Ruch(snake_node* gracz)
{
    //Zawiera tablicê, która informuje, który przycisk zostal wcisniety. Musi zostac wyczyszczona przed kazdym wejsciem.
    clear_keybuf();
    if (key[KEY_LEFT])
        gracz->kierunek = lewo;
    if (key[KEY_RIGHT])
        gracz->kierunek = prawo;
    if (key[KEY_DOWN])
        gracz->kierunek = dol;
    if (key[KEY_UP])
        gracz->kierunek = gora;

    int tmp_x = gracz->x, tmp_y = gracz->y;
    if (gracz->kierunek == lewo)
    {
        if (gracz->x > 0)
            tmp_x = gracz->x - 1;
        else
            Koniec_Gry();
    }
    else if (gracz->kierunek == prawo)
    {
        if (gracz->x < SZEROKOSC_MAPY - 1)
            tmp_x = gracz->x + 1;
        else
            Koniec_Gry();
    }
    else if (gracz->kierunek== dol)
    {
        if (gracz->y < WYSOKOSC_MAPY - 1)
            tmp_y = gracz->y + 1;
        else
            Koniec_Gry();
    }
    else if (gracz->kierunek == gora)
    {
        if (gracz->y > 0)
            tmp_y = gracz->y - 1;
        else
            Koniec_Gry();
    }
    else
        exit(0);

    if (Mapa[tmp_y][tmp_x] == cytrynka)  //Waz zjada cytrynke i powieksza sie
    {
        wynik++;
        snake_node* tmp = gracz;
        while (tmp->next != NULL) //waz jest kolejka polaczonych ze soba elementow przez ktore przechodzimy
            tmp = tmp->next;

        int new_node_x = tmp->x; //Kiedy dotrzemy do konca ciala weza, przechowujemy jego lokalizacjê w dwóch zmiennych
        int new_node_y = tmp->y;
        gracz = Ruch_Ciala(gracz,tmp_x,tmp_y);
        snake_node* new_node = malloc(sizeof(snake_node)); //Po przeniesieniu calego ciala tworzymy nowy element
        new_node->x = new_node_x;
        new_node->y = new_node_y; //Ustawiamy zmienne lokalizacji nowego weza
        new_node->kierunek = tmp->kierunek;
        new_node->next = NULL;
        tmp->next = new_node; //Ustawiamy wezea tmp (poprzedni ogon) nastepnego weza do naszego nowego ogona!
        Losuj_Cytrynke();

    }
    else if (Mapa[tmp_y][tmp_x] == snake)
        Koniec_Gry();
    else if (Mapa[tmp_y][tmp_x] == jabluszko)
    {
        int k;
        szybkosc = 2.5;
        wynik = wynik + 10;
        for(k=0; k<10; k++)
        {
            snake_node* tmp = gracz;

            while (tmp->next != NULL) //waz jest kolejka polaczonych ze soba elementow przez ktore przechodzimy
                tmp = tmp->next;

            int new_node_x = tmp->x; //Kiedy dotrzemy do konca ciala weza, przechowujemy jego lokalizacjê w dwóch zmiennych
            int new_node_y = tmp->y;

            gracz = Ruch_Ciala(gracz,tmp_x,tmp_y);
            snake_node* new_node = malloc(sizeof(snake_node)); //Po przeniesieniu calego ciala tworzymy nowy element
            new_node->x = new_node_x;
            new_node->y = new_node_y; //Ustawiamy zmienne lokalizacji nowego weza
            new_node->kierunek = tmp->kierunek;
            new_node->next = NULL;
            tmp->next = new_node;
        }
        Losuj_Jabluszko();
        Losuj_Cytrynke();
    }
    else if(Mapa[tmp_y][tmp_x] == truskawka)
    {

        szybkosc = 1;
        wynik = wynik + 1;
        snake_node* tmp = gracz;

        while (tmp->next != NULL) //waz jest kolejka polaczonych ze soba elementow przez ktore przechodzimy
            tmp = tmp->next;



        gracz = Ruch_Ciala(gracz,tmp_x,tmp_y);
        Losuj_Truskawki();
    }

    else
        gracz = Ruch_Ciala(gracz,tmp_x,tmp_y);
    Mapa[tmp_y][tmp_x] = snake; //Zaktualizuj mapê obiektów do nowej pozycji g³owy wê¿a

}
/** @brief Ruch gracza
*
* Funkcja sprawdza czy nastepny element ciala weza jest zerem, jezeli tak to zaruje tablice Mapa
* natomiast jezeli nie rekurencyjnie wywołuje funkcje przekazujac jej nastepny element ciala oraz wspolrzedne
* tego elementu x, y. Nastepnie przypisuje wspolrzednym odpowiednie wartosci zapamietane wczesniej.
* @param[in] (snake_node* gracz, int tmp_x, int tmp_y) Funkcja jako parametry przyjmuje element na cialo weza, oraz wspolrzedne x, y tego elementu
* @return Funkcja zwraca wspolrzedne gracza.
*/
snake_node* Ruch_Ciala(snake_node* gracz, int tmp_x, int tmp_y)
{
    if (gracz->next == NULL) //Dobiegliœmy koñca cia³a wê¿a
        Mapa[gracz->y][gracz->x] = nic; //Wyzeruj mape
    else
        gracz->next = Ruch_Ciala(gracz->next,gracz->x,gracz->y);
    gracz->x = tmp_x;
    gracz->y = tmp_y;
    return gracz;

}
/** @brief Rysowanie
* Funkcja sluzy do rysowania "owocow" i "weza". Sprawdza warunek, ze jezeli w danym punkcie na mapie niczego nie ma
* to na mapie rysowane jest czarne tlo, natomiast jezeli jest cytrynka to w zmiennej kolor zapisywany jest kolor (w tym wypadku
* żolty na ktory ma zostac ona pokolorowana. Analogicznie sprawa się ma do rysowania "jabluszka" i "weza". Następnie wywolana zostaje
* funkcja ktora rysuje kwadracik wypelniony danym kolorem oznaczającym nasz obiekt. Funkcja rysuje rowniez ilosc zdobytych
* punktów w prawym górnym rogu.
* @return Funkcja niczego nie zwraca
*/
void Rysowanie()
{
    int i,j;
    acquire_screen();
    for (i = 0; i < WYSOKOSC_MAPY; i++)
    {
        for (j = 0; j < SZEROKOSC_MAPY; j++)
        {
            int kolor; //Rysowanie mapy weza i cytrynek w odpowiednich kolorach
            if (Mapa[i][j] == nic)
                kolor = makecol(0,0,0);
            else if (Mapa[i][j] == cytrynka)
                kolor = makecol(255,255,0);
            else if (Mapa[i][j]==jabluszko)
                kolor = makecol(0,153,51);
            else if (Mapa[i][j] == truskawka)
                kolor = makecol(255, 0, 0);
            else if (Mapa[i][j] == snake)
                kolor = makecol(0,255,255);
            rectfill (bufor, MNOZNIK*j, MNOZNIK*i, MNOZNIK*(j+1),MNOZNIK*(i+1), kolor); //rysowanie elementow za pomoca wypelnionego odpowiednim kolorem prostokata
        }
    }
    //Rysowanie wyniku
    char wynik1[10];
    sprintf(wynik1,"Zdobyte punkty: %d",wynik);
    textout_ex(bufor, font, wynik1, MNOZNIK*(SZEROKOSC_MAPY)*3/5, MNOZNIK, makecol(255,255,255), makecol(0,0,0));
    rect(bufor, 0, 0, MNOZNIK*SZEROKOSC_MAPY-1, MNOZNIK*WYSOKOSC_MAPY-1, makecol( 255, 0, 0));//Rysowanie linii mapy
    draw_sprite(screen, bufor, 0, 0); //Przenoszenie z bufora na ekran obrazu.
    release_screen();
}



