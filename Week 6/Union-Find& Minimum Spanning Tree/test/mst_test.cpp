#include "mst.h"
#include <UnitTest++/UnitTest++.h>


using namespace ipd;

//Test case for compare operation
TEST(compareOperation) {
    //Two edge with same weight
    WU_edge edge1 = WU_edge {1, 2, 1};
    WU_edge edge2 = WU_edge {2, 3, 1};
    CHECK_EQUAL(true,cmp(edge1,edge2));

    //Two edge where first edge smaller than second edge
    WU_edge edge3 = WU_edge {1, 2, 1};
    WU_edge edge4 = WU_edge {2, 3, 2};
    CHECK_EQUAL(true,cmp(edge3,edge4));

    //Two edge where first edge greater than second edge
    WU_edge edge5 = WU_edge {1, 2, 3};
    WU_edge edge6 = WU_edge {2, 3, 2};
    CHECK_EQUAL(false,cmp(edge5,edge6));
}
//Test case for heapSort
TEST(heapSort) {
    WU_edge edge1 = WU_edge {1, 2, 1};
    WU_edge edge2 = WU_edge {9, 1, 2};
    WU_edge edge3 = WU_edge {7, 3, 3};

    std::vector<WU_edge> edge_sorted_order;
    edge_sorted_order.emplace_back(edge1);
    edge_sorted_order.emplace_back(edge2);
    edge_sorted_order.emplace_back(edge3);


    //Edge order 1, 2, 3
    std::vector<WU_edge> edge_order1;
    edge_order1.emplace_back(edge1);
    edge_order1.emplace_back(edge2);
    edge_order1.emplace_back(edge3);

    std::vector<WU_edge> edge_order1_sorted=   sort_edges(edge_order1);

    CHECK_EQUAL(edge_sorted_order.at(0).w, edge_order1_sorted.at(0).w);
    CHECK_EQUAL(edge_sorted_order.at(1).w, edge_order1_sorted.at(1).w);
    CHECK_EQUAL(edge_sorted_order.at(2).w, edge_order1_sorted.at(2).w);

    CHECK_EQUAL(edge_sorted_order.at(0).u, edge_order1_sorted.at(0).u);
    CHECK_EQUAL(edge_sorted_order.at(1).u, edge_order1_sorted.at(1).u);
    CHECK_EQUAL(edge_sorted_order.at(2).u, edge_order1_sorted.at(2).u);

    CHECK_EQUAL(edge_sorted_order.at(0).v, edge_order1_sorted.at(0).v);
    CHECK_EQUAL(edge_sorted_order.at(1).v, edge_order1_sorted.at(1).v);
    CHECK_EQUAL(edge_sorted_order.at(2).v, edge_order1_sorted.at(2).v);


    //Edge order 2, 1, 3
    std::vector<WU_edge> edge_order2;
    edge_order2.emplace_back(edge2);
    edge_order2.emplace_back(edge1);
    edge_order2.emplace_back(edge3);
    std::vector<WU_edge> edge_order2_sorted=  sort_edges(edge_order2);

    CHECK_EQUAL(edge_sorted_order.at(0).w, edge_order2_sorted.at(0).w);
    CHECK_EQUAL(edge_sorted_order.at(1).w, edge_order2_sorted.at(1).w);
    CHECK_EQUAL(edge_sorted_order.at(2).w, edge_order2_sorted.at(2).w);

    CHECK_EQUAL(edge_sorted_order.at(0).u, edge_order2_sorted.at(0).u);
    CHECK_EQUAL(edge_sorted_order.at(1).u, edge_order2_sorted.at(1).u);
    CHECK_EQUAL(edge_sorted_order.at(2).u, edge_order2_sorted.at(2).u);

    CHECK_EQUAL(edge_sorted_order.at(0).v, edge_order2_sorted.at(0).v);
    CHECK_EQUAL(edge_sorted_order.at(1).v, edge_order2_sorted.at(1).v);
    CHECK_EQUAL(edge_sorted_order.at(2).v, edge_order2_sorted.at(2).v);

    //Edge order 3, 1, 2
    std::vector<WU_edge> edge_order3;
    edge_order3.emplace_back(edge3);
    edge_order3.emplace_back(edge1);
    edge_order3.emplace_back(edge2);

    std::vector<WU_edge> edge_order3_sorted=    sort_edges(edge_order3);
    CHECK_EQUAL(edge_sorted_order.at(0).w, edge_order3_sorted.at(0).w);
    CHECK_EQUAL(edge_sorted_order.at(1).w, edge_order3_sorted.at(1).w);
    CHECK_EQUAL(edge_sorted_order.at(2).w, edge_order3_sorted.at(2).w);

    CHECK_EQUAL(edge_sorted_order.at(0).u, edge_order3_sorted.at(0).u);
    CHECK_EQUAL(edge_sorted_order.at(1).u, edge_order3_sorted.at(1).u);
    CHECK_EQUAL(edge_sorted_order.at(2).u, edge_order3_sorted.at(2).u);

    CHECK_EQUAL(edge_sorted_order.at(0).v, edge_order3_sorted.at(0).v);
    CHECK_EQUAL(edge_sorted_order.at(1).v, edge_order3_sorted.at(1).v);
    CHECK_EQUAL(edge_sorted_order.at(2).v, edge_order3_sorted.at(2).v);


    //Edge order 3, 2, 1
    std::vector<WU_edge> edge_order4;
    edge_order4.emplace_back(edge3);
    edge_order4.emplace_back(edge2);
    edge_order4.emplace_back(edge1);

    std::vector<WU_edge> edge_order4_sorted=    sort_edges(edge_order4);
    CHECK_EQUAL(edge_sorted_order.at(0).w, edge_order4_sorted.at(0).w);
    CHECK_EQUAL(edge_sorted_order.at(1).w, edge_order4_sorted.at(1).w);
    CHECK_EQUAL(edge_sorted_order.at(2).w, edge_order4_sorted.at(2).w);

    CHECK_EQUAL(edge_sorted_order.at(0).u, edge_order4_sorted.at(0).u);
    CHECK_EQUAL(edge_sorted_order.at(1).u, edge_order4_sorted.at(1).u);
    CHECK_EQUAL(edge_sorted_order.at(2).u, edge_order4_sorted.at(2).u);

    CHECK_EQUAL(edge_sorted_order.at(0).v, edge_order4_sorted.at(0).v);
    CHECK_EQUAL(edge_sorted_order.at(1).v, edge_order4_sorted.at(1).v);
    CHECK_EQUAL(edge_sorted_order.at(2).v, edge_order4_sorted.at(2).v);



    //Edge order 1, 3, 2
    std::vector<WU_edge> edge_order5;
    edge_order5.emplace_back(edge1);
    edge_order5.emplace_back(edge3);
    edge_order5.emplace_back(edge2);

    std::vector<WU_edge> edge_order5_sorted=   sort_edges(edge_order5);

    CHECK_EQUAL(edge_sorted_order.at(0).w, edge_order5_sorted.at(0).w);
    CHECK_EQUAL(edge_sorted_order.at(1).w, edge_order5_sorted.at(1).w);
    CHECK_EQUAL(edge_sorted_order.at(2).w, edge_order5_sorted.at(2).w);

    CHECK_EQUAL(edge_sorted_order.at(0).u, edge_order5_sorted.at(0).u);
    CHECK_EQUAL(edge_sorted_order.at(1).u, edge_order5_sorted.at(1).u);
    CHECK_EQUAL(edge_sorted_order.at(2).u, edge_order5_sorted.at(2).u);

    CHECK_EQUAL(edge_sorted_order.at(0).v, edge_order5_sorted.at(0).v);
    CHECK_EQUAL(edge_sorted_order.at(1).v, edge_order5_sorted.at(1).v);
    CHECK_EQUAL(edge_sorted_order.at(2).v, edge_order5_sorted.at(2).v);




    //Edge order 2, 3, 1
    std::vector<WU_edge> edge_order6;
    edge_order6.emplace_back(edge2);
    edge_order6.emplace_back(edge3);
    edge_order6.emplace_back(edge1);
    std::vector<WU_edge> edge_order6_sorted=  sort_edges(edge_order6);

    CHECK_EQUAL(edge_sorted_order.at(0).w, edge_order6_sorted.at(0).w);
    CHECK_EQUAL(edge_sorted_order.at(1).w, edge_order6_sorted.at(1).w);
    CHECK_EQUAL(edge_sorted_order.at(2).w, edge_order6_sorted.at(2).w);

    CHECK_EQUAL(edge_sorted_order.at(0).u, edge_order6_sorted.at(0).u);
    CHECK_EQUAL(edge_sorted_order.at(1).u, edge_order6_sorted.at(1).u);
    CHECK_EQUAL(edge_sorted_order.at(2).u, edge_order6_sorted.at(2).u);

    CHECK_EQUAL(edge_sorted_order.at(0).v, edge_order6_sorted.at(0).v);
    CHECK_EQUAL(edge_sorted_order.at(1).v, edge_order6_sorted.at(1).v);
    CHECK_EQUAL(edge_sorted_order.at(2).v, edge_order6_sorted.at(2).v);
}

//Check for minimal spanning tree as "tree"
TEST(mst_Sample1_tree) {

    WU_graph mst_original=  WU_graph(8);
    mst_original.add_edge(0,1,4);
    mst_original.add_edge(1,2,24);
    mst_original.add_edge(2,3,9);
    mst_original.add_edge(3,4,7);
    mst_original.add_edge(4,5,21);

    mst_original.add_edge(5,0,16);
    mst_original.add_edge(0,6,6);
    mst_original.add_edge(6,2,23);
    mst_original.add_edge(6,5,8);
    mst_original.add_edge(6,7,5);

    mst_original.add_edge(7,5,10);
    mst_original.add_edge(7,2,18);
    mst_original.add_edge(7,3,11);
    mst_original.add_edge(7,4,14);


    WU_graph mst_rst =kruskal(mst_original);

    WU_graph mst1 =  WU_graph(8);
    mst1.add_edge(3,4,7);
    mst1.add_edge(0,1,4);
    mst1.add_edge(0,6,6);
    mst1.add_edge(6,5,8);
    mst1.add_edge(6,7,5);
    mst1.add_edge(7,3,11);
    mst1.add_edge(2,3,9);


    CHECK_EQUAL(true,mst_rst==mst1);



    //Check for minimal spanning tree as "forest"
}

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

//Check for minimal spanning tree as "tree"
// with option of two same weight edge: Case 2
TEST(mst_Sample3_tree) {
    //Check for minimal spanning tree as "tree"
    WU_graph mst_original=  WU_graph(9);
    mst_original.add_edge(0,1,4);

    mst_original.add_edge(1,7,11);
    mst_original.add_edge(1,2,8);
    mst_original.add_edge(0,7,8);
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
  //  mst.add_edge(0,7,8);
    mst.add_edge(2,8,2);
    mst.add_edge(2,5,4);
    mst.add_edge(2,3,7);
    mst.add_edge(3,4,9);
    mst.add_edge(5,6,2);
    mst.add_edge(6,7,1);


    CHECK_EQUAL(true,mst_rst==mst);

}

//Check for minimal spanning tree as "forest"
TEST(mst_Sample1_forest) {

    WU_graph mst_original=  WU_graph(12);
    mst_original.add_edge(0,1,4);
    mst_original.add_edge(1,2,24);
    mst_original.add_edge(2,3,9);
    mst_original.add_edge(3,4,7);
    mst_original.add_edge(4,5,21);

    mst_original.add_edge(5,0,16);
    mst_original.add_edge(0,6,6);
    mst_original.add_edge(6,2,23);
    mst_original.add_edge(6,5,8);
    mst_original.add_edge(6,7,5);

    mst_original.add_edge(7,5,10);
    mst_original.add_edge(7,2,18);
    mst_original.add_edge(7,3,11);
    mst_original.add_edge(7,4,14);

    mst_original.add_edge(8,9,2);
    mst_original.add_edge(8,10,1);
    mst_original.add_edge(8,11,5);
    mst_original.add_edge(9,10,3);
    mst_original.add_edge(11,10,4);

    WU_graph mst_rst =kruskal(mst_original);

    WU_graph mst1 =  WU_graph(12);
    mst1.add_edge(3,4,7);
    mst1.add_edge(0,1,4);
    mst1.add_edge(0,6,6);
    mst1.add_edge(6,5,8);
    mst1.add_edge(6,7,5);
    mst1.add_edge(7,3,11);
    mst1.add_edge(2,3,9);

    mst1.add_edge(8,9,2);
    mst1.add_edge(8,10,1);
    mst1.add_edge(11,10,4);

    CHECK_EQUAL(true,mst_rst==mst1);




}


//Check for mst for graph made by isolated nodes only
TEST(mst_isolated_nodes) {
    //Check for minimal spanning tree as "tree"
    WU_graph mst_original=  WU_graph(9);
    WU_graph mst_rst =kruskal(mst_original);
    WU_graph mst =  WU_graph(9);

    CHECK_EQUAL(true,mst_rst==mst);
}


//Check for mst for graph made by a sample graph with an isolated node
TEST(mst_connected_graph_with_an_isolated_node) {
    //Check for minimal spanning tree as "tree"
    WU_graph mst_original=  WU_graph(5);
    mst_original.add_edge(0,1,2);
    mst_original.add_edge(0,2,1);
    mst_original.add_edge(0,3,5);
    mst_original.add_edge(1,2,3);
    mst_original.add_edge(2,3,4);

    WU_graph mst_rst =kruskal(mst_original);
    WU_graph mst =  WU_graph(5);
    mst.add_edge(2,3,4);
    mst.add_edge(2,0,1);
    mst.add_edge(1,0,2);

    CHECK_EQUAL(true,mst_rst==mst);
}
