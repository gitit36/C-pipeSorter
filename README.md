I spent some time learning about pipe and execl, now the sorter is fully functional. To sort a big file, I divide it into n child, and each child has a pipe to send its portion after sorting as output back to the parent. Therefore, it saves a lot of time for the sorting process. 

First compile the sorter
g++ -std=c++11 sorter.cpp -o sorter

Then compile the root
g++ -std=c++11 root.cpp 

Then run it with your customized variables
./a.out rec1000.txt 1000 10 1 int ascending output.txt

./a.out rec1000.txt <data amout> <how many sorter> <sort with which parameter> <type of the parameter> <order> output.txt

For  <type of the parameter>,
1 means by SSN number
2 means Firstname
3 means Secondname
4 means Tax amount

Thanks for the help from Nabil and Professor Alex Delis.

