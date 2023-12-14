#include <stdio.h>
#include<limits.h>
 
//Function to find maximum element of the array
int max_element(int array[], int size) 
{  
    // Initializing max variable to minimum value so that it can be updated
    // when we encounter any element which is greater than it.
    int max = 0;  
    for (int i = 0; i < size; i++)
    {
        //Updating max when array[i] is greater than max
        if (array[i] > max)  
        max = array[i];  
    }
    //return the max element
    return max;  
}
 
//Implementing bucket sort 
void Bucket_Sort(int array[], int size) 
{  
    int max = max_element(array, size); 
 
    // Creating buckets 
    int bucket[max+1];  
 
    //Initializing buckets to zero
    for (int i = 0; i <= max; i++)  
    bucket[i] = 0;  
 
    // Pushing elements in their corresponding buckets
    for (int i = 0; i < size; i++)  
    bucket[array[i]]++;
 
    // Merging buckets effectively
    int j=0;   // j is a variable which points at the index we are updating
    for (int i = 0; i <= max; i++)  
    { 
        // Running while loop until there is an element in the bucket
        while (bucket[i] > 0)  
        {  
            // Updating array and increment j          
            array[j++] = i;  
 
            // Decreasing count of bucket element
            bucket[i]--;   
        }  
    }  
}  
 