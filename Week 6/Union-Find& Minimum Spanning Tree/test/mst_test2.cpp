#include "mst.h"
#include <UnitTest++/UnitTest++.h>


using namespace ipd;

//Check for minimal spanning tree as "tree"
// with option of two same weight edge: Case 1
TEST(mst_Sample2_tree) {
    //Check for minimal spanning tree as "tree"
    WU_graph mst_original=  WU_graph(9);
    mst_original.add_edge(0,1,4);
    mst_original.add_edge(0,7,8);
    mst_original.add_edge(1,7,11);
    mst_original.add_edge(1,2,8);
    mst_original.add_edge(2,8,2);

    mst_original.add_edge(2,3,7);
    mst_original.add_edge(2,5,4);
    mst_original.add_edge(3,5,14);
    mst_original.add_edge(3,4,9);
    mst_original.add_edge(4,5,10);

    mst_original.add_edge(5,6,2);
    mst_original.add_edge(6,7,1);
    mst_original.add_edge(6,8,6);
    mst_original.add_edge(7,8,7);

    WU_graph mst_rst =kruskal(mst_original);

    WU_graph mst =  WU_graph(9);
    mst.add_edge(0,1,4);
    mst.add_edge(1,2,8);
   // mst.add_edge(0,7,8);
    mst.add_edge(2,8,2);
    mst.add_edge(2,5,4);
    mst.add_edge(2,3,7);
    mst.add_edge(3,4,9);
    mst.add_edge(5,6,2);
    mst.add_edge(6,7,1);


    CHECK_EQUAL(true,mst_rst==mst);

}