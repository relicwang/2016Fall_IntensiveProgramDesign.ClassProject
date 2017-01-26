# IPD Homework 6 Submission Summary: Relic & Ishmael



## Summary

In this assignment, a ranked, path-compressing
union-find was implemented, and it is applied to implement Kruskal’s MST
algorithm.


## Testing

The testing section mainly divivided into two sections as union-find and MST.

### Part I: Union-Find

For Union-Find, the testing go through all applied methods/constructers that includes:
    
        // Creates a new union-find of `n` objects.
        Union_find(size_t n);

        // Returns the number of objects in the union-find.
        size_t size() const;

        // Unions the sets specified by the two given objects.
        void do_union(size_t, size_t);
        
        // Finds the set representative for a given object.
        size_t find(size_t);
        
Three helper functions are applied for assisting the testing:

        //Returns a vector contians current union find set
        const std::vector<size_t>& get_curt_unionfind()const;
        
        //Returns a vector contians current ranking
        const std::vector<size_t>& get_curt_ranking()const;

        //Print the current ranking
        void print_cur_ranking() const ;


#### Case 1: General Union Find Testing (uf_test.cpp, line 19) 
[The code lines mentioned in this section is all in uf_test.cpp]

Purpose: Testing the explicit functions as： 

    *  Union_find(size_t n);
    *  size_t size() const;
    *  void do_union(size_t, size_t);
     
The testing example is revised from the sample test case (see image below) offered in lecture 11b to ensure
the correctness.    
            

  ![Graph1](https://raw.githubusercontent.com/relicwang/vs/master/F1.png)
  
To be more specific:
* 1. Initialize two Union_find (line 20), and test the correctiness of Union_find(size_t n) (line 26-32).
* 2. Check the size() function, before (line 35, 36) and after manipulation (line 85, 86).
* 3. Check the do_union(size_t, size_t) function.
   * As following:
   * a. A simplist one to one (same ranking) node union is executed e.g. union 4 to 6; 2 to 0; 3 to 0; (line 39-51, 61-63)
   * b. Two ranking 2 (same ranking, different weights) tree were unioned (one is with weight 3, another is with weight 2)
   
     ![Graph2](https://raw.githubusercontent.com/relicwang/vs/master/F2.png)
     
   * c. One ranking 2 tree and one ranking 3 (different ranking, different weights）tree were unioned (one is with weight 2, another is with weight 5.
        
        
     ![Graph3](https://raw.githubusercontent.com/relicwang/vs/master/F3.png)
 
 Note: More testing examples were served as supplement cases in next two testing sections
 
#### Case 2: Repeated pair of nodes union ranking test (uf_test.cpp, line 91) 
[The code lines mentioned in this section is all in uf_test.cpp]

As describe in "Anything that surprised during the assignment," previously it is not expected
the do_union(size_t, size_t) function will be executed for same paired of nodes more than once, 
and leads to the "ranking" error. Unfortunately, it does happen. Hence, the supplment test cases
were added here after revising the code.

 * In test case (line 92-120), union node 0 and 1 were executed three times to verify the correctness.


#### Case 3: General ranking test(uf_test.cpp, line 135) 
[The code lines mentioned in this section is all in uf_test.cpp]

Purpose: Testing the implicitly information as： 
     union_ranking_ set
     
In this testing section, a union_find with size 10 is applied.

In order to examinate the correctness of ranking set, the following sample situations were 
considered:
* 1. Initialized Union_Find (line 140-444).
* 2. The most simple union, which is one-one union (line 146-178).
* 3. The union with the case that left node has higher height (line 189-196).
* 4. The union with the case that left node has lower height (line 200-207).
* 5. The union with the case that both "tree" have height the same height (but more complex than case 2) (line 212-220).
* 6. The union with the case that left node has higher height (but more complex thann case 3)(line 224-233).


  
   
### Part II: Minimum Spanning Tree
[The code lines mentioned in this section is all in mst_test.cpp]

For Union-Find, the testing go through three applied methods that includes:

         // Computes a minimum spanning forest by Kruskal's algorithm.
         WU_graph kruskal(const WU_graph &);

        //Sort the edges by weights in non-decreasing order through integrated heap sort
         std::vector<WU_edge> sort_edges(const std::vector<WU_edge> &);
         
        //Define the comparision operation in heap sorting
        bool cmp(const WU_edge &, const WU_edge &);


#### Case 1: compareOperation (line 8-23) 
 This test section is mainly for the comparision operation, three sample test situtaion were considered;
 * 1. firstEdge.weight==secondEdge.weight
 * 2. firstEdge.weight < secondEdge.weight
 * 3. firstEdge.weight > secondEdge.weight
 
 
#### Case 2: heapSort (line 24-90)
 This test section is mainly for the sort_edges operation, six sample test situtaion were considered;
 Given orginal edges where edge1.w < edge2.w < edge3.w
 They will have P(3,3) [is 6] possible permutation:
   * 1. edge[1,2,3]
   * 2. edge[1,3,2]
   * 3. edge[2,3,1]
   * 4. edge[2,1,3]
   * 5. edge[3,1,2]
   * 6. edge[3,2,1]
    
And their results after sort_edges operation were tested
 
#### Case 3: mst_Sample1_tree (line 161-199)

  Start from this section, the Kruskal algorithm was examinated.
  
  The first graph:(This test case is severed as an example of minimal spanning tree and the given graph is "tree")
   ![SampleGraph1](https://raw.githubusercontent.com/relicwang/vs/master/Graph1.jpg)
   
  The result is expected:
   ![SampleGraph1Result](https://raw.githubusercontent.com/relicwang/vs/master/Graph1_2.jpg)

#### Case 4: mst_Sample2_tree (line 203-239)

  The second graph:(This test case is severed as an example of minimal spanning tree and the given graph is "tree")
 
   ![SampleGraph1](https://raw.githubusercontent.com/relicwang/vs/master/Graph2.jpg)
 
#### Case 5: mst_Sample1_forest (line 283-328)

  The second graph:(This test case is severed as an example of minimal spanning "tree" and the given graph is "forest")
   ![SampleForestGraph1](https://raw.githubusercontent.com/relicwang/vs/master/Graph_Forest1.jpg)
 
#### Case 6: mst_isolated_nodes 

Check for mst for graph made by isolated nodes only

#### Case 7: mst_connected_graph_with_an_isolated_node

Check for mst for graph made by a sample graph with an isolated node


## Anything that surprised during the assignment.

    //Check the most simple union, which is one-one union
    //      for 0, 1 union
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[1]=2;
    for(int i=0;i<uf1.size();++i){
    CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }


    //Check the second union, which is one-one union
    //      for 0, 1 union
    uf1.do_union(0,1);;
    ranks=   uf1.get_curt_ranking();
    ranks_expected[1]=2;
    for(int i=0;i<uf1.size();++i){
    CHECK_EQUAL(ranks_expected[i],ranks[i]);
    }
 
   When test cases were written, union the identical pair of nodes was found to be allowed more than once (while the height increase)!!! As the above case,
   the height of node with index 1 will increase twice! Then, go back to revise the code for union.

   Also, how to testing the testing compressing works is another surprise, comparing the time complexity was tried.


