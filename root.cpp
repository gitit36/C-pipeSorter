#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <stdio.h> /* printf() */
#include <sys/times.h> /* times() */
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
  bool operator<(const data& rhs) const
  {
    if(sort_by == 1) return ssn < rhs.ssn;// sort by ssn
    if(sort_by == 2) return firstname[0] < rhs.firstname[0];// sort by firstname
    if(sort_by == 3) return secondname[0] < rhs.secondname[0];// sort by secondname
    if(sort_by == 4) return tax < rhs.tax;// sort by tax
  }
};
int data::sort_by = 2;// default will be to sort by ssn



int main (int argc, char *argv[]){
    double t1, t2, cpu_time;
    struct tms tb1, tb2;
    double ticspersec;
    int i, sum = 0;
    ticspersec = (double) sysconf(_SC_CLK_TCK);
    t1 = (double) times(&tb1);
   
  //   argv[1] InputFile rec1000.txt
  //   argv[2] NumOfWorkers 1000
  //   argv[3] NameOfSortExecutable/childs 4
  //   argv[4] AttributeNumber 1:ssn, 2:firstname,3:secondname,4:tax
  //   argv[5] Type
  //   argv[6] Order
  //   argv[7] OutputFile
  
  //int f[2];
  int total = stoi(argv[2]);
  int pCount = stoi(argv[3]); // process count
  int jobs = total/pCount;
  int buffer[pCount][jobs];
  data::sort_by = stoi(argv[4]);
  //int counter[pCount] = {jobs,jobs,jobs,jobs};
  data buff[pCount][jobs];
  data result[total];
  data mergelist[pCount];
  
  pid_t* pID = new pid_t[pCount];
  int fd[2],fd1[2],fd2[2],fd3[2];
  int fdl[pCount][2];

  //distribute to n childs below
  for(int i=0; i<pCount; i++){
    
    if ( pipe ( fdl[i] ) == -1 ) {
      perror (" pipe "); exit (1) ;
    }
    pID[i]= fork();
    switch(pID[i]){
    case -1:
      perror("fork");
      break;
    case 0:
        cout<<"child "<<i<<endl;
        //execvp ("test.cpp" , NULL);
        string arg = to_string(i);
        const char * ag = arg.c_str();
        close(fdl[i][0]);
        dup2 ( fdl[i] [ WRITE ], 11) ;
        //close(fd[1]);
        char arg1[20], arg2[20];
       // std::strcpy(ag1, argv[1].c_str());
        execl ("test" , ag ,argv[1],argv[2],argv[3],argv[4],  NULL);
        
        //execlp("g++", "g++", "test.cpp", "-D", "IDX", "=", i, NULL);
        
        exit(0);
        break;
  }
  }
  
  
  for(int j=0; j<pCount; j++)
  {
    wait(NULL);
   
  }
  
  
  //merge below
  
  for (int i = 0; i < pCount; ++i){
    close ( fdl[i] [ WRITE ]) ;
    
    cout << "sorting"<<i<<" is done" << endl;
    string astr;

   read(fdl[i][READ], &buff[i], sizeof(buff[i]));
  }
  for (int i = 0; i < pCount; ++i){
    for (int j = 0; j < jobs; ++j){
      result[i*jobs+j] = buff[i][j];
    }
  }
  sort(result,result+total);
  ofstream outputFile;
  outputFile.open(argv[7]);
  if(argv[6]=="ascending"){
  for (int i = 0; i < total; ++i){
    cout<<result[i].ssn<<" "<<result[i].firstname<<" "<<result[i].secondname<<" "<<result[i].tax<<endl;
    outputFile<<result[i].ssn<<" "<<result[i].firstname<<" "<<result[i].secondname<<" "<<result[i].tax<<endl;
    
   // cout<<buff[i][j].ssn<<" "<<buff[i][j].firstname<<" "<<buff[i][j].secondname<<" "<<buff[i][j].tax<<endl;
  }
  }
  else {
    for (int i = total; i > 1; --i){
      cout<<result[i].ssn<<" "<<result[i].firstname<<" "<<result[i].secondname<<" "<<result[i].tax<<endl;
      outputFile<<result[i].ssn<<" "<<result[i].firstname<<" "<<result[i].secondname<<" "<<result[i].tax<<endl;
      
      // cout<<buff[i][j].ssn<<" "<<buff[i][j].firstname<<" "<<buff[i][j].secondname<<" "<<buff[i][j].tax<<endl;
    }
  }
  outputFile.close();
  
  t2 = (double) times(&tb2);
  cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -(tb1.tms_utime + tb1.tms_stime));
  printf("Run time was %lf sec (REAL time) although we used the CPU for %lf sec (CPU time).\n", (t2 - t1) / ticspersec, cpu_time / ticspersec);
  exit(0);
}


