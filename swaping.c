//This file contains functions of- 1. print an 2D array 2. swap two rows or coloumn
//the array must be square e.g-2x2,3x3,4x4;
//by-Mr.ari


//size the size of the square 2D array


void printArray(int *a,int size){
  printf("\n");
  for(int i=0;i<=(size-1)*size;i=i+size) {
    for (int j=0;j<size;j++)
    printf("%d ",*((a+i)+j));
    printf("\n");
  }
}
/*
specifier 1 ----> Row wise swaping
specifier 2 ----> Coloumn wise swaping
*/

int rowColExchange(int *a,int size,int i1,int i2,int specifier){   /*rowColExchange swap row or col i1 and i2 */
      if (i1 != i2){
        int temp;
      switch (specifier){
        case 1:
        for (int j=0;j<size;j++){
          temp = *((a+size*i1)+j);
          *((a+size*i1)+j)=*((a+size*i2)+j);
          *((a+size*i2)+j)=temp;
        }
        break;
        case 2:
        for (int j=0;j<size;j++){
          temp = *((a+size*j)+i1);
          *((a+size*j)+i1)=*((a+size*j)+i2);
          *((a+size*j)+i2)=temp;
        }
        break;
    }
  }
  }

int compareArray(int *x,int *y,int size){
  for(int i=0;i<=(size-1)*size;i=i+size)
    for (int j=0;j<size;j++)
    if (*((x+i)+j) != *((y+i)+j)) return 0;
  return 1;
}
