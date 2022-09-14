#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

const double EPS = 0.0000000001; // dokładność porównania z zerem
const int    MAXEQ = 100;          // maksymalna ilość równań w układzie

// Funkcja dokonująca eliminacji niewiadomych. Jeśli operacja się powiedzie, zwraca true. Inaczej zwraca false.

bool GCEliminujX(int n, double AB[][MAXEQ + 1], int WK[])
{
    int i, j, k, tmp;
    double m;

    for (i = 0; i < n - 1; i++)
    {
        for (k = i, j = i + 1; j < n; j++)
        {
            if (fabs(AB[WK[k]][i]) < fabs(AB[WK[j]][i]))
            {
                k = j;
            }
        }
        tmp = WK[k]; WK[k] = WK[i]; WK[i] = tmp; //zamiana kolumn
        if (fabs(AB[WK[i]][i]) < EPS)
        {
            return false;
        }
        for (j = i + 1; j < n; j++)
        {
            m = -AB[WK[j]][i] / AB[WK[i]][i];
            AB[WK[j]][i] = 0;

            for (k = i + 1; k <= n; k++)
            {
                AB[WK[j]][k] += m * AB[WK[i]][k];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cout << AB[WK[i]][j] << " ";
        }
        cout << endl;
    }
    return true;
}

// poniższa funkcja oblicza kolejne niewiadome x z macierzy AB przetworzonej przez funkcję GCEliminujX().
// Jeśli operacja się powiedzie, zwraca true. Inaczej zwraca false.

bool GCObliczX(int n, double X[], double AB[][MAXEQ + 1], int WK[])
{

    double s;

    for (int i = n - 1; i >= 0; i--)
    {
        if (fabs(AB[WK[i]][i]) < EPS)
        {
            return false;
        }
        s = AB[i][n];
        for (int j = n - 1; j > i; j--)
        {
            s -= AB[WK[i]][j] * X[j];
        }
        X[i] = s / AB[WK[i]][i];
    }

    return true;
}

// Program główny

int main()
{
    ifstream fin; //zmienne do plików txt
    int i, j, n, WK[MAXEQ + 1];
    double AB[MAXEQ][MAXEQ + 1], X[MAXEQ];

    // Odczyt z pliku

    fin.open("in.txt");
    fin >> n; //wielkość macierzy
    if (n <= MAXEQ)
    {
        for (i = 0; i < n; i++)
        {
            WK[i] = i; // wektor kolumn
            for (j = 0; j <= n; j++)
            {
                fin >> AB[i][j];
            }
        }
        WK[n] = n;
        fin.close();

        // Poniżej wywołuje funkcje liczące i wypisuje wyniki

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n + 1; j++)
            {
                cout << AB[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl << "---------------------------------------------------------" << endl << endl;

        if (GCEliminujX(n, AB, WK) && GCObliczX(n, X, AB, WK))
        {
            cout << endl << "---------------------------------------------------";

            for (i = 0; i < n; i++)
            {
                cout << endl << "Wektor " << i << " = " << WK[i] << endl;
            }

            cout << endl << "---------------------------------------------------";
            for (i = 0; i < n; i++)
            {
                cout << endl << "x" << i + 1 << " = " << X[i] << endl;
            }
        }
        else cout << "Rozwiazanie ukladu rownan nie powiodlo sie!" << endl;
    }
    else
    {
        fin.close();
        cout << "Zbyt wiele rownan!" << endl;
    }
    cout << endl << "---------------------------------------------------------" << endl;
    return 0;
}