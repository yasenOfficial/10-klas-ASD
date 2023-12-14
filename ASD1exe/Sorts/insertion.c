void insertionSort(int arr[], int n) {
    int i, element, j;
    for (i = 1; i < n; i++) {
        element = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > element) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        arr[j + 1] = element;
    }
}
