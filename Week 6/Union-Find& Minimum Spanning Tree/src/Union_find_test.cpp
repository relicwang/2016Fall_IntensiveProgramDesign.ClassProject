#include <ctime>
#include <iostream>
#include "Union_find.h"
#include <chrono> // C++11
/** Test Sample
  0         5
/ | \       |
2 3 6       1
    |
     4
**/
using namespace ipd;

    int main(){
        using namespace std::chrono ;

        Union_find uf1= Union_find(7);
        Union_find uf2= Union_find(2);


        //Create 6-4 chain
        uf1.do_union(4,6);
        uf1.do_union(2,0);
        uf1.do_union(3,0);
        uf1.do_union(6,0);


        auto start = steady_clock::now() ;
        //Check the id of Node 4, expect 0
        uf1.find(4);
        auto end = steady_clock::now() ;
        // std::cout <<"Second find for 4, time is "<<  duration_cast<milliseconds>(end-start).count();
        std::cout << "First find for 4that took " << duration_cast<milliseconds>(end-start).count()
                  << " milliseconds\n" ;


        auto start1 = steady_clock::now() ;
        //Check the id of Node 4, expect 0
        uf1.find(4);
        auto end1 = steady_clock::now() ;
       // std::cout <<"Second find for 4, time is "<<  duration_cast<milliseconds>(end-start).count();
        std::cout << "Second find for 4that took " << duration_cast<milliseconds>(end1-start1).count()
                  << " milliseconds\n" ;












    }
