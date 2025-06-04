#include <stdio.h>
#include <stdlib.h>


//Complexidade: O(N)^2
void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    // Um por um, move o limite do subarray não classificado
    for (i = 0; i < n - 1; i++) {
        // Encontra o elemento mínimo no array não classificado
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Troca o elemento mínimo encontrado com o primeiro elemento
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}