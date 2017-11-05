#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <signal.h>
#include <cstddef>
# define READ 0
# define WRITE 1
using namespace std;


struct data
{
  static int sort_by;    
  int ssn;
  string firstname;
  string secondname;
  int tax;
};
int data::sort_by = 1;// default will be to sort by ssn

// Sort arr[] of size n using Bubble Sort. 
void BubbleSort (data arr[], int n, int sort_by)
{
  //sort(datalist,datalist+jobs);
  int i, j;
  data swap;
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n-i-1; ++j)
    {
      // Comparing consecutive data and switching values if value at j > j+1.
      if(sort_by == 1){
        if (arr[j].ssn > arr[j+1].ssn){
          {
            swap       = arr[j];
            arr[j]   = arr[j+1];
            arr[j+1] = swap;
          }
        }
      }
      if(sort_by == 2){
        if (arr[j].firstname[0] > arr[j+1].firstname[0]){
          {
            swap       = arr[j];
            arr[j]   = arr[j+1];
            arr[j+1] = swap;
          }
        }
      }
      if(sort_by == 3){
        if (arr[j].secondname[0] > arr[j+1].secondname[0]){
          {
            swap       = arr[j];
            arr[j]   = arr[j+1];
            arr[j+1] = swap;
          }
        }
      }
      if(sort_by == 4){
        if (arr[j].tax > arr[j+1].tax){
          {
            swap       = arr[j];
            arr[j]   = arr[j+1];
            arr[j+1] = swap;
          }
        }
      }
 
    }
    // Value at n-i-1 will be maximum of all the values below this index.
  }	
}	

int main (int argc, char *argv[]){
  //argv[2] how many data
  //argv[3] how many childs
  int i = stoi(argv[0]);
 // int f[2];
  int jobs = stoi(argv[2])/stoi(argv[3]);
  data datalist[jobs];
  string myArray[4*stoi(argv[2])];
  cout << "new"<<argv[0]<<argv[1]<<argv[2]<<argv[3]<<argv[4]<< endl; 
  data::sort_by = stoi(argv[4]);
  ifstream file(argv[1]);
  if(file.is_open())
  {
    for(int t = 0; t < 4*stoi(argv[2]); ++t)
    {
      file >> myArray[t];
    }
  }
  for (int t = 0; t<jobs; ++t){
  //  cout<<(myArray[4*i*jobs+4*t])<<endl;
    datalist[t].ssn = stoi(myArray[4*i*jobs+4*t]);
    datalist[t].firstname = myArray[4*i*jobs+4*t+1];
    datalist[t].secondname = myArray[4*i*jobs+4*t+2];
    datalist[t].tax = stoi(myArray[4*i*jobs+4*t+3]);
  }
  
  BubbleSort(datalist, jobs, data::sort_by);
  
  char message []= " Hello ! ";
  if ( write (11 , &datalist, sizeof(datalist)) == -1)
    perror (" Write to 11 - dup2 ");
  else printf ( " Write to dup2ed file descriptor 11 succeeded \n" );
  //cout<<"finish"<<argv[0]<<endl;
	exit(0);
	return 1;
}
