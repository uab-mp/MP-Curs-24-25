#ifndef SUDOKU_H
#define SUDOKU_H

const int N_FILES = 9;
const int N_COLUMNES = 9;
const int TAMANY_QUADRAT = 3;
const int MAX_MOVIMENTS = 20;

bool jugaSudoku(int tauler[N_FILES][N_COLUMNES], int nLliures, bool resultat[], int& nMoviments);

#endif
