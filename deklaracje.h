/** @file */

#ifndef SLOWA_LINIE_DEKLARACJE_H
#define SLOWA_LINIE_DEKLARACJE_H

/**
 * Lista jednokierunkowa slow. Struktura przechowujaca dane wczytanego slowa
 * @param word slowo wczytane z pliku
 * @param line_number numer lini z ktorej zostalo wczytane dane slowo
 * @param pNext wskaznik na nastepny element listy
 */
typedef struct words{
    char * word;
    struct lines * lines_head;
    struct words * pNext;
}words;

/**
 * Lista jednokierunkowa numerow lini. Struktura przechowujaca numer lini w ktorej wystapilo slowo.
 * @param line numer lini
 * @param pNext wksaznik na nastepny element listy
 */
typedef struct lines{
    int line;
    struct lines * pNext;
}lines;

/**
 * Funkcja dodaje do listy nowe slowo wraz z linia, lub gdy slowo juz jest w liscie - dodaje tylko kolejny nr lini
 * @param pHead wskaznik na glowe listy slow
 * @param new_word slowo ktore ma byc dodane do listy
 * @param line_nr nr lini w ktorym znajduje sie slowo
 */
void add_to_list(words ** pHead, char * word, int line_nr);

/**
 * Funkcja czyta slowa z pliku i uzywajac funkcji add_to_list tworzy liste ze slowami
 * @param input_name nazwa pliku wejsciowego
 * @param pHead wskaznik na poczatek listy
 */
void read_input(char * input_name, words ** pHead);

/**
 * Funkcja zapisuje do pliku slowa z listy
 * @param pHead wskaznik na poczatek listy
 * @param output_name nazwa pliku wyjsciowego
 */
void create_output(words * pHead, char * output_name);

/**
 * Funkcja do testowania dodawania do listy
 * @param pHead wskaznik na poczatek listy
 */
void print_list(words * pHead);

/**
 * Funkcja usuwajaca dynamicznie alokowane elementy listy,
 * aby pozbyc sie wyciekow pamieci
 * @param pHead wskaznik na poczatek listy
 */
void delete_list(words ** pHead);

#endif //SLOWA_LINIE_DEKLARACJE_H
