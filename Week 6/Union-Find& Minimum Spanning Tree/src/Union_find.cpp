#include "Union_find.h"
#include <iostream>

namespace ipd
{
    // Creates a new union-find of `n` objects.
    Union_find::Union_find(size_t size)
    {
        for (size_t i = 0; i < size; ++i){
            union_set_.emplace_back(i);
            union_ranking_.emplace_back(1);
        }
    }

    // Returns the number of objects in the union-find.
    size_t Union_find::size() const {
        return union_set_.size();
    }

    // Unions the sets specified by the two given objects.
    void Union_find::do_union(size_t object1, size_t object2) {
        if (find(object1) != find(object2)) {//To avoid union same pair of objects more than once
            size_t rank1 = union_ranking_.at(find(object1));
            size_t rank2 = union_ranking_.at(find(object2));

            //Initial version without considering ranking, just lazy union
            // union_set_.at(find(object1))=union_set_.at(find(object2));

            //"Maintain" tree balance
            if (rank1 ==rank2) {
                union_set_.at(find(object1)) = union_set_.at(find(object2));
                union_ranking_.at(find(object2)) = 1 + rank2;
            } else if (rank1 < rank2) {
                union_set_.at(find(object1)) = union_set_.at(find(object2));
            } else {
                union_set_.at(find(object2)) = union_set_.at(find(object1));
            }
        }
    }


    // Finds the set representative for a given object.
    size_t Union_find::find(size_t object) {
        //Vector applied to track the nodes in the path to the parent
        std::vector<size_t> track_set;

        size_t current_node=object;
        size_t parent_node=union_set_.at(object);

        while(parent_node!=current_node){
            track_set.emplace_back(current_node);
            current_node=parent_node;
            parent_node=union_set_.at(current_node);
        }

        for(size_t i=0;i<track_set .size();++i){
            union_set_.at(track_set.at(i))=parent_node;
        }


        return parent_node;
    }


    //Print the current ranking
    void Union_find::print_cur_ranking() const {
       for(int i=0;i< union_ranking_.size();++i){
           std::cout<<"The "<<i<<"th ranking is "<<union_ranking_.at(i)<<'\n';
       }

    }
    //Returns a vector contians current ranking
    const std::vector<size_t> &Union_find::get_curt_ranking() const {
        return union_ranking_;
    }

    //Returns a vector contians current union find set
    const std::vector<size_t> &Union_find::get_curt_unionfind() const {
        return union_set_;
    }
}
