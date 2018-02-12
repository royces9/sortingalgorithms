#ifndef HEAPSORT
#define HEAPSORT

#include <stdlib.h>
#include <string.h>
#include <math.h>

//heapsort
//max heap

//swim the last index in the heap
void swimHeap(int *array, int size){  
  int parent = floor((size - 1)/2);
  int child = size;
  while(child > 0){
    if(array[child] > array[parent]){
      int temp = array[child];
      array[child] = array[parent];
      array[parent] = temp;
      
      child = parent;
      parent = floor((child - 1)/2);
    }
    else
      break;
  }
}

//size is 0-indexed
void sinkHeap(int *array, int size){
  int child;
  int parent = 0;
  int leftChild = 1;
  int rightChild = 2;

  while(rightChild <= size+1){
    //check that rightChild is less than maximum size, that short circuits, if it is
    //check whether left or right child is bigger

    child = leftChild + ((rightChild <= size ) && (array[rightChild] > array[leftChild]));

    if(array[child] > array[parent]){
      int temp = array[child];
      array[child] = array[parent];
      array[parent] = temp;
      parent = child;
    }
    else{
      break;
    }
    
    leftChild = 2 * parent + 1;
    rightChild = leftChild + 1; 
  }
}

int *buildHeap(int *array, int size){
  int *outArray = malloc(size * sizeof(*outArray));

  //this part creates the heap
  for(int i = 0; i < size; ++i){
    outArray[i] = array[i];
    swimHeap(outArray, i);
  }
  return outArray;
}

void sort(int *array, int size){
  int *heap = buildHeap(array, size);
  int lastHeapIndex = size - 1;

  for(int i = size - 1; i >= 0; --i){
    //send head of heap to output array
    array[i] = heap[0];
    
    //send last thing in heap to the front
    heap[0] = heap[lastHeapIndex--];

    //sink the head node, this should fix heap property
    sinkHeap(heap, lastHeapIndex);
  }
  free(heap);  
}

#endif //HEAPSORT
