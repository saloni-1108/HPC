#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void merge(vector<int> &arr, int low, int mid, int high)
{

    vector<int> temp;

    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high)
    {

        if (arr[left] <= arr[right])
        {
            temp.push_back(arr[left]);
            left++;
        }
        else
        {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while (left <= mid)
    {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high)
    {
        temp.push_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++)
    {
        arr[i] = temp[i - low];
    }
}

void mergeSort(vector<int> &arr, int low, int high)
{

    if (low >= high)
        return;

    int mid = (low + high) / 2;

#pragma omp parallel sections
    {
#pragma omp section
        mergeSort(arr, low, mid);

#pragma omp section
        mergeSort(arr, mid + 1, high);
    }

    merge(arr, low, mid, high);
}

int main()
{

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    double start = omp_get_wtime();

    mergeSort(arr, 0, n - 1);

    double end = omp_get_wtime();

    cout << "Sorted Array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    cout << "Execution Time: " << end - start << endl;

    return 0;
}