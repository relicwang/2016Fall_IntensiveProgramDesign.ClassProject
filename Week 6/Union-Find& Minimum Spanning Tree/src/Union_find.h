#pragma once

#include <cstddef>
#include <vector>

namespace ipd {

    // A union-find object representing disjoint sets of `size()` objects.
    class Union_find {
    public:
        // Creates a new union-find of `n` objects.
        Union_find(size_t n);

        // Returns the number of objects in the union-find.
        size_t size() const;

        // Unions the sets specified by the two given objects.
        void do_union(size_t, size_t);

        // Finds the set representative for a given object.
        size_t find(size_t);

        //Returns a vector contians current union find set
        const std::vector<size_t>& get_curt_unionfind()const;

        //Returns a vector contians current ranking
        const std::vector<size_t>& get_curt_ranking()const;

        //Print the current ranking
        void print_cur_ranking() const;

    private:
        std::vector<size_t> union_set_;
        std::vector<size_t> union_ranking_;
    };

}
