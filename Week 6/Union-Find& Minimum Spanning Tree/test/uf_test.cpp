#include "Union_find.h"
#include <UnitTest++/UnitTest++.h>
#include <ctime>
#include <iostream>

#include <cstddef>
#include <vector>

using namespace ipd;

/** Test Sample
  0         5
/ | \       |
2 3 6       1
    |
     4
**/

TEST(Union_find_general){
    Union_find uf1= Union_find(7);
    Union_find uf2= Union_find(2);

    std::vector<size_t> result_uf1=     uf1.get_curt_unionfind();
    std::vector<size_t> result_uf2=     uf2.get_curt_unionfind();
    //Check initial Union_find works
    for(int i=0;i<uf1.size();++i){
        result_uf1.at(i)=i;
    }

    for(int i=0;i<uf2.size();++i){
        result_uf2.at(i)=i;
    }

    //Check size
    CHECK_EQUAL(7,uf1.size());
    CHECK_EQUAL(2,uf2.size());

   //Add edge between 4 and 6
    uf1.do_union(4,6);
    CHECK_EQUAL(6,uf1.find(4));
    CHECK_EQUAL(6,uf1.find(6));

    //Add edge between 2 and 0
    uf1.do_union(2,0);
    CHECK_EQUAL(0,uf1.find(0));
    CHECK_EQUAL(0,uf1.find(2));

    //Add edge between 3 and 0
    uf1.do_union(3,0);
    CHECK_EQUAL(0,uf1.find(0));
    CHECK_EQUAL(0,uf1.find(3));

    //Union two sections with root of  6 and 0
    uf1.do_union(4,0);
    CHECK_EQUAL(0,uf1.find(0));
    CHECK_EQUAL(0,uf1.find(6));
  //Check the id of Node 4, expect 0
    CHECK_EQUAL(0,uf1.find(4));

    //Add edge between 1 and 5
    uf1.do_union(1,5);
    CHECK_EQUAL(5,uf1.find(1));
    CHECK_EQUAL(5,uf1.find(5));
/**
Expected Result:

               0
           / | \  \
           2 3 6   5
               |    \
               4     1
               **/
    //Union two sections
    uf1.do_union(0,5);
    CHECK_EQUAL(0,uf1.find(4));
    CHECK_EQUAL(0,uf1.find(6));
    CHECK_EQUAL(0,uf1.find(3));
    CHECK_EQUAL(0,uf1.find(2));
    CHECK_EQUAL(0,uf1.find(0));
    CHECK_EQUAL(0,uf1.find(1));
    CHECK_EQUAL(0,uf1.find(5));


    //Check size
    CHECK_EQUAL(7,uf1.size());
    CHECK_EQUAL(2,uf2.size());

}

//Test cases for ranking
//  1.Repeated pair of nodes union ranking test
TEST(RepeatPairRanking){
    //Initialize the Union_Find
    Union_find uf1= Union_find(10);
    std::vector<size_t> ranks=   uf1.get_curt_ranking();

    //Check the rank of initialized Union_Find
    std::vector<size_t> ranks_expected (uf1.size(),1);
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //1.Check the most simple union, which is one-one union
    //      for 0, 1 union
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[1]=2;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }


    //2.Check the most simple union, which is one-one union AGAIN
    //      for 0, 1 union
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();

    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }


    //3.Check the most simple union, which is one-one union AGAIN, AGAIN
    //      for 0, 1 union
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();

    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

}

//  2.General ranking test
TEST(RankingGeneral){
    //Initialize the Union_Find
    Union_find uf1= Union_find(10);
    std::vector<size_t> ranks=   uf1.get_curt_ranking();

    //Check the rank of initialized Union_Find
    std::vector<size_t> ranks_expected (uf1.size(),1);
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //1.Check the most simple union, which is one-one union
    //      for 0, 1 union
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[1]=2;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //      for 2, 3 union
    uf1.do_union(2,3);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[3]=2;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //      for 4, 5 union
    uf1.do_union(4,5);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[5]=2;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }


    //      for 6, 7 union
    uf1.do_union(6,7);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[7]=2;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //      for 0, 1 union again! To check whether the union handle the union twice situation
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[1]=2;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }


    //2.Check the union with the case that left node has higher height.
    //      Here, the height is 2, 1 respectively.
    //      Expected result should have no change for the height.
    uf1.do_union(4,8);;
    ranks=   uf1.get_curt_ranking();
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }



    //3.Check the union with the case that left node has lower height.
    //      Here, the height is 1, 2 respectively.
    //      Expected result should have no change for the height.
    uf1.do_union(9,6);;
    ranks=   uf1.get_curt_ranking();
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //uf1.print_cur_ranking();
  //  std::cout<<'\n';

    //4.Check the union with the case that both "tree" have height the same height
    //      Here, the height is 2, 2 respectively.
    //
    uf1.do_union(0,2);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[3]=3;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }

    //uf1.print_cur_ranking();

    //5.Check the union with a case that left tree has higher height (but more complex)
    //      Here, the height is 3, 2 respectively.
    //
    uf1.do_union(0,6);;
    ranks=   uf1.get_curt_ranking();
   // ranks_expected[3]=3;
    for(int i=0;i<uf1.size();++i){
        CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }
}

