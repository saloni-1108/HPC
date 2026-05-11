#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <omp.h>
using namespace std;

int main()
{
    cout << "=== Parallel Reduction using OpenMP ===" << endl;

    int n;
    cout << "\nEnter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // print original array
    cout << "\nArray: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // =====================
    // SEQUENTIAL OPERATIONS
    // =====================
    cout << "\n--- Sequential Operations ---" << endl;

    clock_t seqStart = clock();

    // Sequential Min
    int seqMin = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < seqMin)
            seqMin = arr[i];
    }

    // Sequential Max
    int seqMax = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > seqMax)
            seqMax = arr[i];
    }

    // Sequential Sum
    long long seqSum = 0;
    for (int i = 0; i < n; i++)
    {
        seqSum += arr[i];
    }

    // Sequential Average
    double seqAvg = (double)seqSum / n;

    clock_t seqEnd = clock();
    double seqTime = double(seqEnd - seqStart) / CLOCKS_PER_SEC;

    cout << "Min     : " << seqMin << endl;
    cout << "Max     : " << seqMax << endl;
    cout << "Sum     : " << seqSum << endl;
    cout << "Average : " << seqAvg << endl;
    cout << "Time    : " << seqTime << " seconds" << endl;

    // =====================
    // PARALLEL OPERATIONS
    // =====================
    cout << "\n--- Parallel Operations ---" << endl;

    clock_t parStart = clock();

    // Parallel Min
    int parMin = arr[0];
#pragma omp parallel for reduction(min : parMin)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < parMin)
            parMin = arr[i];
    }

    // Parallel Max
    int parMax = arr[0];
#pragma omp parallel for reduction(max : parMax)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > parMax)
            parMax = arr[i];
    }

    // Parallel Sum
    long long parSum = 0;
#pragma omp parallel for reduction(+ : parSum)
    for (int i = 0; i < n; i++)
    {
        parSum += arr[i];
    }

    // Parallel Average
    double parAvg = (double)parSum / n;

    clock_t parEnd = clock();
    double parTime = double(parEnd - parStart) / CLOCKS_PER_SEC;

    cout << "Min     : " << parMin << endl;
    cout << "Max     : " << parMax << endl;
    cout << "Sum     : " << parSum << endl;
    cout << "Average : " << parAvg << endl;
    cout << "Time    : " << parTime << " seconds" << endl;

    // =====================
    // PERFORMANCE COMPARISON
    // =====================
    cout << "\n=== Performance Comparison ===" << endl;
    cout << "Sequential Time : " << seqTime << " seconds" << endl;
    cout << "Parallel Time   : " << parTime << " seconds" << endl;
    if (parTime > 0)
        cout << "Speedup         : " << seqTime / parTime << "x faster" << endl;
    else
        cout << "Speedup         : Parallel was too fast to measure!" << endl;

    return 0;
}