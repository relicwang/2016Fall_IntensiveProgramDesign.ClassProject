#pragma once

#include "WU_graph.h"
#include "Union_find.h"

namespace ipd {

    // Computes a minimum spanning forest by Kruskal's algorithm.
    WU_graph kruskal(const WU_graph &);

    //Sort the edges by weights in non-decreasing order through integrated heap sort
    std::vector<WU_edge> sort_edges(const std::vector<WU_edge> &);

    //Define the comparision operation for heap sort
    bool cmp(const WU_edge &, const WU_edge &);


}
