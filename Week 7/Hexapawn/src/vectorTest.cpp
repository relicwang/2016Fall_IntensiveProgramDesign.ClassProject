#include <iostream>
#include <vector>

int main(){
//    //1. Test how to initilize a vector with certain value
//    std::vector <std::vector<int>> vector1 ;
//    vector1.emplace_back(2, 10);
//
//    std::cout<<"The vector height is : "<<vector1.size()<<'\n';
//
//    std::cout<<"The vector width is : "<<vector1[0].size()<<'\n';
//    std::cout<<"The vector value is : "<<vector1[0][0]<<'\n';
//
//   //2. Test default value -> and it is 0
//    std::vector <int> vector2 ;
//    vector2.resize(1);
//    std::cout<<"The vector2 default value is : "<<vector2[0]<<'\n';
//
//    //3. Test3
//    std::vector< std::vector<size_t>> two_three_vector;
//
//    for(int i=0;i<2;++i){
//        two_three_vector.emplace_back(3,0);
//    }
//
//
//    std::cout<<"The vector2 default [0][0]value is : "<<two_three_vector[0][0]<<'\n';
//    std::cout<<"The vector2 default [1][2]value is : "<<two_three_vector[1][2];


   //4. Test reset the value in certian position in "matrix"

    std::vector<std::vector<size_t >> vector_test1;

    for(int i=0;i<2;++i){
        vector_test1.emplace_back(3,0);
    }

    vector_test1.at(0).at(0)=1;
    vector_test1.at(1).at(2)=2;

    std::cout<<vector_test1[0][0]<<" "<<vector_test1[1][2];
    std::cout<<" \n"<<vector_test1[1].size();
    std::cout<<" \n"<<vector_test1.size();

}

/**
std::vector< std::vector<size_t>> get_case(int index){
    std::vector< std::vector<size_t>> result;

    switch(index) {
        case 1 :
            std::vector< std::vector<size_t>> case1= get_two_three_vector();
            //   case1[1][1]=1;
            result=  case1;
            break;       // and exits the switch
        case 2 :
            std::vector< std::vector<size_t>> case2= get_two_three_vector();
            case2[0][0]=1;
            result=   case2;
            break;
        case 3 :
            std::vector< std::vector<size_t>> case3= get_two_three_vector();
            case3[0][2]=1;
            result=   case3;
            break;
        case 4 :
            std::vector< std::vector<size_t>> case4= get_two_three_vector();
            case4[0][1]=1;
            result=   case4;
            break;
        case 5 :
            std::vector< std::vector<size_t>> case5= get_two_three_vector();
            case5[0][0]=1;
            case5[0][1]=1;
            result=   case5;
            break;
        case 6 :
            std::vector< std::vector<size_t>> case6= get_two_three_vector();
            case6[0][0]=1;
            case6[0][2]=1;
            result=   case6;
            break;
        case 7 :
            std::vector< std::vector<size_t>> case7= get_two_three_vector();
            case7[0][1]=1;
            case7[0][2]=1;
            result=   case7;
            break;
        case 8 :
            std::vector< std::vector<size_t>> case8= get_two_three_vector();
            case8[0][0]=1;
            case8[0][1]=1;
            case8[0][2]=1;
            result=   case8;
            break;
    }

    return  result;


}
**/
