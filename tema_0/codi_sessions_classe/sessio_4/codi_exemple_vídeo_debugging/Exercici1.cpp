#include <iostream>
using namespace std;

int cerca(int v[], int dimensio, int valor)
{
	bool trobat = false;
	int i = 0;
	while (!trobat && (i < dimensio))
	{
		if (v[i] = valor)
			trobat = true;
		i++;
	}
	if (trobat)
		return i;
	else
		return -1;
}

const int LONGITUD = 10;

int main()
{
	int array[LONGITUD] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int index = cerca(array, LONGITUD, 20);
	cout << "Index: " << index << endl;

	index = cerca(array, LONGITUD, 3);
	cout << "Index: " << index << endl;

	return 0;
}