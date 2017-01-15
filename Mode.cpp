/* Annual Programming Efficiency Conference and Challenge
Compiled in Microsoft Visual Studio 2010
Submitted by Jithendar Anandan
CWID - 50154397
Texas A&M Univerity - Commerce */

#include <fstream>  // header file needed to read a file
#include<iostream>
#include<time.h> 
using namespace std;

//Function declaration
void mode(long data[], long size,long &num_modes, long modeNums[],long &maxFrequency);
void quickSort(long arr[], long left, long right);

void main ()
{
  long double time1; // variables used to time the code
  clock_t start,stop;  // clock_t is a valid type
  double duration;

  long *data,*modeNums,size; // polonger needed to dynamically allocate memory
  long num_modes,maxFrequency;
  // the name of the file containing the test data is “TestData.bin”
  ifstream binaryin("TestData.bin", ios::binary);  // statement to open the binary file
  binaryin.read(reinterpret_cast<char *>(&size), 4);    // statement to read the size of the data array to allocate
  data = new(nothrow)long[size];  // statement to dynamically allocate the data array to have size elements
  modeNums = new(nothrow)long[size];
  if(!data)  // this statement will test the polonger to determine if memory was dynamically allocated
    { cout<<"Memory allocation error for data array, program will terminate\n";
       system("pause");  // this is a windows command to pause the program
       exit(0); }    // this statement will terminate the  program if memory was not allocated
  // statement to read the data/values in the file and store the numbers in the array data.
  binaryin.read(reinterpret_cast<char *>(data), size*sizeof(long));  

  start=clock(); // Start the benchmark    
  // call the function that is to be timed

  mode(data,size,num_modes,modeNums,maxFrequency);

  stop=clock();  // stop the clock
  time1 = double(stop-start)/CLK_TCK; // compute/record the time

  //Display output
  cout<<"time to execute the mode : "<<time1<<endl;  // output the time to compute the mode(s)
  cout<<"The Modes are : ";
  for(int i = 0; i < num_modes; i++)
  {
    cout<<modeNums[i]<<" ";
  }
  cout<<endl;
  cout << "No. of modes : " << num_modes << endl; 
  cout << "Maximum frequency : " << maxFrequency << endl; 
  delete[] data; // free up the memory
  system("pause");
  return;
}

void mode(long data[], long size,long &num_modes, long modeNums[],long &maxFrequency)
{
  //Sorting the dataset before finding the mode
  quickSort(data,0,size-1);

  //Finding the mode
  auto modes = new long[size][2]; //statement to dynamically allocate the modes array to have size elements
  modes = new long[size][2]();
  long counter = 1;
  maxFrequency = 0; //Maximum frequency
  num_modes = 0;   //Number of modes
  long mode = data[0]; 
  int modescounter = 0;
  for (int pass = 0; pass < size - 1; pass++)
  {
    //Check if subsequent numbers are equal
      if ( data[pass] == data[pass+1] )
      {
        //If equal check if is greater than maxFrequency and if it is greater add it to the modes array
          counter++;
          if ( counter >= maxFrequency )
          {
              if(data[pass] != modes[modescounter][0] )
              {
                modes[modescounter][0] = data[pass];
                modes[modescounter++][1] = counter;
              }
              //Set maximum frequency to the new maximum
              maxFrequency = counter;
          }
      }
      //Reset counter 
       else
       {
        counter = 1; 
       }
  }

  //Find the modes with the maximum frequency from the mode array and store it in modeNums array
  for(int i = 0; i < modescounter; i++)
  {
    if(modes[i][1] == maxFrequency)
    {
      modeNums[num_modes++] = modes[i][0];
    }
  }
  return;
}

//Sorting the dataset using quicksort algorithm
void quickSort(long arr[], long left, long right) {
      long i = left, j = right;
      long tmp;
      long pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

