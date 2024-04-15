#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdlib.h>
#include <stdio.h>
//Implementacja algorytmu BFS będzie wymagać trzech plików tymczasowych
// 1) Plik Queue z kolejką do BFS
// zawiera kolejne pary [wiersz1 kolumna1[nowa_linia]wiersz2,kolumna2]
// 2) Plik Ancestors z poprzednikami odwiedzonych wierzchołków umożliwia odczytanie najkrótszej ścieżki po przejściu grafu od P do K
// Zawiera pary par [wiersz_komórki kolumna_komórki wiersz_poprzednika kolumna_poprzednika)[nowa_linia]]
// 3) Plik Visited z odwiedzonymi już komórkami zapewnia niezapentlanie się algorytmu w "otwartch prostokątach" komórek
// Zawiera pary (wiersz1,kolumna1)[spacja](wiersz2,kolumna2)...

int* maze_dim(FILE* F);

//funkcje pomocnicze do pliku Visited

void add_visited(FILE* F , int row , int col);
int is_visited(FILE* F , int row , int col);

//funkcje pomocnicze do pliku Ancestors
void add_ancestors(FILE* F , int row , int col , int A_row , int A_col);

//funkcje pomocnicze do pliku Queue

void add_to_queue(FILE* F , int row , int col);
int* pop_queue(FILE* F , long line_nr);
// pop_queue zwraca tab[0] -> wiersz tab[1] -> kol




#endif
