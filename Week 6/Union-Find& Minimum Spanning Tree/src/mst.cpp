#include "mst.h"
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_hea
#include <iostream>


namespace ipd
{
    // Computes a minimum spanning forest by Kruskal's algorithm.
    WU_graph kruskal(const WU_graph & wu_graph) {
        size_t size= wu_graph.size();
        Union_find union_find= Union_find(size);
        WU_graph mst=  WU_graph(size);
        std::vector<WU_edge> all_edge=get_all_edges(wu_graph);
        std::vector<WU_edge> sorted_edge=sort_edges(all_edge);

   /** TESTING PURPOSE
        for(int i=0;i<all_edge.size();++i){
            std::cout<<"( " <<all_edge.at(i).u<<" "<<all_edge.at(i).v<<" "<<all_edge.at(i).w<<" )"<<'\n';
        }
        std::cout<<"sorted"<<'\n';
        for(int i=0;i<sorted_edge.size();++i){
            std::cout<<"( " <<sorted_edge.at(i).u<<" "<<sorted_edge.at(i).v<<" "<<sorted_edge.at(i).w<<" )"<<'\n';
        }
     **/
         for(int i=0;i<sorted_edge.size();++i){
             WU_edge temp_edge=sorted_edge.at(i);
             if(union_find.find(temp_edge.v)!=union_find.find(temp_edge.u)){
                 mst.add_edge(temp_edge.u,temp_edge.v,temp_edge.w);
                 union_find.do_union(temp_edge.v,temp_edge.u);

             }
         }
        return mst;
    }


    //Sort the edges by weights in non-decreasing order through C++ integrated heap sort
    //     Ref:http://www.cplusplus.com/reference/algorithm/sort_heap/
    //         http://en.cppreference.com/w/cpp/algorithm/sort_heap
    std::vector<WU_edge> sort_edges(const  std::vector<WU_edge> & edges ){  //Try to use it without the reference

        std::vector<WU_edge> edges_copy=edges;
        std::make_heap (edges_copy.begin(), edges_copy.end(),cmp);
        std::sort_heap (edges_copy.begin(),edges_copy.end(),cmp);
        return  edges_copy;
    }

    //Define the comparision operation for heap sort
    bool cmp(const WU_edge &edge1, const WU_edge &edge2){
        return  (edge1.w<=edge2.w);
    }



}
