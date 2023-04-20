// A program to calculate the minimum of maximum path of all possible binary search tree of an array

// library needed
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long cal_min_max_path(int* arr, int start, int end, long long** dp)
{
    // Only one element
    if (start == end)
    {
        dp[start][end] = arr[start];
        return arr[start];
    }

    // Two elements
    if (start + 1 == end)
    {
        dp[start][end] = arr[start] + arr[end];
        return arr[start] + arr[end];
    }
    
    // More than two elements
    long long min_max_path = 0;
    for (int i = start + 1; i < end; i++)
    {
        // Calculate the minimum of maximum path of all possible binary search tree of arr[start] to arr[i - 1]
        long long left_min_max_path = 0;
        if (dp[start][i - 1] < 0)
            dp[start][i - 1] = cal_min_max_path(arr, start, i - 1, dp);
        
        left_min_max_path = dp[start][i - 1];
        
        // Calculate the minimum of maximum path of all possible binary search tree of arr[i + 1] to arr[end]
        long long right_min_max_path = 0;
        if (dp[i + 1][end] < 0)
            dp[i + 1][end] = cal_min_max_path(arr, i + 1, end, dp);
        
        right_min_max_path = dp[i + 1][end];
        
        // Calculate the minimum of maximum path of all possible binary search tree of arr[start] to arr[end]
        long long min_max_path_of_i = arr[i] + (left_min_max_path > right_min_max_path ? left_min_max_path : right_min_max_path);
        if (min_max_path_of_i < min_max_path || min_max_path == 0)
            min_max_path = min_max_path_of_i;
    }

    // Store the minimum of maximum path of all possible binary search tree of arr[start] to arr[end]
    dp[start][end] = min_max_path;

    return min_max_path;
}

// Compare function for qsort
int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

// main function
int main()
{
    // Get the number of elements
    int N;
    scanf("%d", &N);

    // Create array and get the elements
    int* arr = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        scanf("%d", arr + i);
    
    // Sort the array
    qsort(arr, N, sizeof(int), compare);

    // Create a 2D array to store the minimum of maximum path
    // for dp[i][j] = minimum of maximum path of all possible binary search tree of arr[i] to arr[j]
    long long** dp = (long long**)malloc(sizeof(long long*) * N);
    for (int i = 0; i < N; i++)
    {
        dp[i] = (long long*)malloc(sizeof(long long) * N);
        memset(dp[i], -1, sizeof(long long) * N);
    }

    // Print the minimum of maximum path
    printf("%lld", cal_min_max_path(arr, 0, N - 1, dp));

    return 0;
}