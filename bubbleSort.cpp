#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubble_sort(vector<int> &arr)
{

    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {

#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{

    int n;

    cout << "Please enter the number of elements: ";
    cin >> n;

    vector<int> arr;

    for (int i = 0; i < n; i++)
    {

        cout << "Enter element " << i + 1 << ": ";

        int number;
        cin >> number;

        arr.push_back(number);
    }

    cout << "Array before Sorting: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    double start = omp_get_wtime();

    bubble_sort(arr);

    double end = omp_get_wtime();

    cout << "Array After Sorting: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    cout << "Parallel Execution Time: " << end - start << endl;

    return 0;
}