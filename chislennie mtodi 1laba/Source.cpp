#include <iostream>
using namespace std;

double** initial(int n, int k)
{
	double** A = new double* [n];
	for (int i = 0; i < n; i++)
		A[i] = new double[k];
	return A;
}
void create(char choice, double** arr, int n, int k)
{
	if (choice == 'm') {
		arr[0][0] = 8.64;
		arr[0][1] = 1.71;
		arr[0][2] = 5.42;
		arr[1][0] = 10.21;
		arr[1][1] = -6.39;
		arr[1][2] = 4.25;
		arr[2][0] = 1.84;
		arr[2][1] = 3.41;
		arr[2][2] = 4.21;

		arr[0][3] = 7.92;
		arr[1][3] = -3.41;
		arr[2][3] = 12.29;
	}
	else {
		cout << "enter n and k " << '\t';
		cin >> n >> k;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < k; j++)
				cin >> arr[i][j];
		}
	}

}
void print(double** arr, int n, int k)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
			cout << arr[i][j] << '\t';
		cout << endl;
	}
}
double* gauss(double** arr, int n, int k)
{
	double elem; int variable = 0;
	for (int j = 0; j < n; j++)
	{
		if (arr[0][0] == 0)
		{
			cout << "error";
			return 0;
		}
		double max = 0; variable = 0;
		for (int t = j; t < n; t++) // проходим по стобцу 
		{

			if (abs(arr[t][j]) > max)
			{
				max = abs(arr[t][j]);
				variable = t;
				//cout << "35 str, variable and max " << variable <<'\t'<<max << endl;
			}
			if (max > abs(arr[j][j]))
			{
				double* ptr = arr[j];
				arr[j] = arr[variable];
				arr[variable] = ptr;
				//cout << "43 str, arr[variable] " << ptr[j] << endl;
			}
			elem = arr[j][j];
			for (int c = j; c < k; c++)
				arr[j][c] /= elem;
			//cout << "48 str, arr[j][c]= " << arr[j][c] << endl;			
			for (int s = j + 1; s < n; s++)
			{
				elem = arr[s][j];
				for (int d = j; d < k; d++)
					arr[s][d] -= elem * arr[j][d];
				//cout << "54-56 str, elem and arr[s][d] " << elem << '\t' << arr[s][d] << endl;				
			}
		}
		cout << endl;
		print(arr, n, k);
		cout << endl;
	}
	//обратный ход
	double* xx = new double[k];
	xx[n - 1] = arr[n - 1][n];
	for (int i = n - 2; i >= 0; i--)
	{
		xx[i] = arr[i][n];
		for (int j = i + 1; j < n; j++)
			xx[i] -= arr[i][j] * xx[j];
	}
	cout << "x: ";
	for (int i = 0; i < n; i++)
		cout << xx[i] << '\t';
	cout << endl << endl;
	return xx;
}
double FAULTS(int n, double max_new, double max, double* results_2, double* results)
{
	double* vect = new double[n];
	for (int i = 0; i < n; i++)
	{
		vect[i] = results_2[i] - results[i];
		if (vect[i] > max)
			max = vect[i];
		if (results[i] > max_new)
			max_new = results[i];
	}
	return abs(max / max_new);

}

int main()
{
	int n = 3, k = 4;
	double** arr; char choice;
	arr = initial(n, k);
	cout << "m - manual/ a - auto (default): ";
	cin >> choice;
	create(choice, arr, n, k);
	double** copy = initial(n, n);
	double* b = new double[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		{
			copy[i][j] = arr[i][j];
			b[i] = arr[i][n];
		}
	}

	print(arr, n, k);
	cout << endl;
	double* results = new double[n];
	for (int i = 0; i < n; i++)
		cout << b[i] << '\t';
	cout << endl;
	results = gauss(arr, n, k);
	double* new_b = new double[n];
	for (int i = 0; i < n; i++)
	{
		new_b[i] = 0;
		for (int j = 0; j < n; j++)
		{
			double temp = copy[i][j] * results[j];
			cout << temp << '\t';
			new_b[i] += temp; //new vector b
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << "b' " << new_b[i] << '\t';
	cout << endl << endl;
	//посчитали b' и вставляем в матрицу для подсчета x''
	double** arr_2 = initial(n, k);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr_2[i][j] = copy[i][j];
	for (int i = 0; i < n; i++)
		for (int j = n; j < k; j++)
			arr_2[i][j] = new_b[i];
	print(arr_2, n, k);
	cout << endl;
	double* results_2 = new double[n];
	results_2 = gauss(arr_2, n, k);
	double* F = new double[n];
	cout << endl;
	double X_max = INT_MIN, X_max_new = INT_MIN, b_max = INT_MIN, b_max_new = INT_MIN, f_n = INT_MIN;
	cout << "FAULT: " << FAULTS(n, X_max_new, X_max, results_2, results) << endl;
	cout << "F_nevyaz: ";
	for (int i = 0; i < n; i++)
	{
		F[i] = results_2[i] - results[i];
		cout << F[i] << '\t';
		if (F[i] > f_n)
			f_n = F[i];
	}
	cout << endl;
	cout << "F_norm " << f_n << endl; // максимальная норма невязки
	cout << endl;

	return 0;
}