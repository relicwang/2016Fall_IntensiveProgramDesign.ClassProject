#include "hexapawn.h"
#include <UnitTest++/UnitTest++.h>

//1. Test get_two_three_vector function
TEST(two_three_vector){
    //Assert the give vector is mutatable
  std::vector <std::vector <size_t>> vector1=get_two_three_vector();
    CHECK_EQUAL(0,vector1[0][0]);
    vector1[0][0]=1;
    CHECK_EQUAL(1,vector1[0][0]);

    //Assert the give vector is not connected with previous returned vector
    std::vector <std::vector <size_t>> vector2=get_two_three_vector();
    CHECK_EQUAL(0,vector2[0][0]);

    vector2[0][0]=2;
    CHECK_EQUAL(2,vector2[0][0]);
    CHECK_EQUAL(1,vector1[0][0]);

}

//2. Test get_case function for case 1
TEST(get_case_1){
    //Assert the give vector is mutatable
    std::vector <std::vector <size_t>> vector1=get_case(1);
    for(int i=0;i<vector1.size();i++){
          size_t column_size=vector1[i].size();
          CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            CHECK_EQUAL(0,vector1[i][j]);
        }
    }

}

//3. Test get_case function for case 2
TEST(get_case_2){
    //Assert the give vector is mutatable
    std::vector <std::vector <size_t>> vector1=get_case(2);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0&&j==0){
                CHECK_EQUAL(1,vector1[i][j]);
            }
           else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//4. Test get_case function for case 3
TEST(get_case_3){
    //Assert the give vector is mutatable
    std::vector <std::vector <size_t>> vector1=get_case(3);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0&&j==2){
                CHECK_EQUAL(1,vector1[i][j]);
            }
            else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//5. Test get_case function for case 4
TEST(get_case_4){

    std::vector <std::vector <size_t>> vector1=get_case(4);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0&&j==1){
                CHECK_EQUAL(1,vector1[i][j]);
            }
            else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//6. Test get_case function for case 5
TEST(get_case_5){

    std::vector <std::vector <size_t>> vector1=get_case(5);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0&&(j==0||j==1)){
                CHECK_EQUAL(1,vector1[i][j]);
            }
            else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//7. Test get_case function for case 6
TEST(get_case_6){

    std::vector <std::vector <size_t>> vector1=get_case(6);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0&&(j==0||j==2)){
                CHECK_EQUAL(1,vector1[i][j]);
            }
            else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//8. Test get_case function for case 7
TEST(get_case_7){

    std::vector <std::vector <size_t>> vector1=get_case(7);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0&&(j==1||j==2)){
                CHECK_EQUAL(1,vector1[i][j]);
            }
            else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//9. Test get_case function for case 8
TEST(get_case_8){

    std::vector <std::vector <size_t>> vector1=get_case(8);
    for(int i=0;i<vector1.size();i++){
        size_t column_size=vector1[i].size();
        CHECK_EQUAL(3,column_size);
        for(int j=0;j<column_size;j++){
            if(i==0){
                CHECK_EQUAL(1,vector1[i][j]);
            }
            else{ CHECK_EQUAL(0,vector1[i][j]);}
        }
    }
}

//10.Test initialize_board function
TEST(initialize_board){
    std::vector <std::vector <size_t>> board=initialize_board(8,8,PLAYER_B_);


    //Check board height
    CHECK_EQUAL(8,board.size());

    //Check the width of first row
    CHECK_EQUAL(10,board[0].size());

    //Check the correctness of the pawn except the last row
    for(int i=0;i<board.size()-1;++i){
        //Check board width in each row
        CHECK_EQUAL(10,board[i].size());
        for(int j=0;j<10;++j){
            CHECK_EQUAL(0, board[i][j] );
            }
    }

    //Check the correctness of the pawn in the last row
    for(int j=1;j<9;++j){
        CHECK_EQUAL(1, board[board.size()-1][j] );
    }
    CHECK_EQUAL(0, board[board.size()-1][0] );
    CHECK_EQUAL(0, board[board.size()-1][9] );

}

//11.Test the comparablity of the posn
TEST(posn){
    posn a;
    a.row_index=1;
    a.column_index=2;


    posn b;
    b.row_index=1;
    b.column_index=1;


    posn c;
    c.row_index=1;
    c.column_index=2;

    CHECK_EQUAL(false,a==b);
    CHECK_EQUAL(true,a==c);
}

//12. Case structure tests
TEST(cases){
    resultCase case1;

    CHECK_EQUAL(-1,case1.index);
    CHECK_EQUAL(false,case1.front);
    CHECK_EQUAL(false,case1.left);
    CHECK_EQUAL(false,case1.right);


    case1.index=1;
    CHECK_EQUAL(1,case1.index);

    case1.front=true;
    CHECK_EQUAL(true,case1.front);

    case1.left=true;
    CHECK_EQUAL(true,case1.left);

    case1.right=true;
    CHECK_EQUAL(true,case1.right);

}

//13. Get bool test
TEST(get_bool){

    resultCase result1;
    CHECK_EQUAL(false,get_bool(result1));


    result1.index=1;
    result1.front= true;
    CHECK_EQUAL(true,get_bool(result1));
}

//14. Posn function test
TEST(posn1){
    posn posn1{1,2};
    CHECK_EQUAL(1,posn1.row_index);
    CHECK_EQUAL(2,posn1.column_index);
}

//15. Test match_expected_right_column function
TEST(match_expected_right_column){

    CHECK(match_expected_right_column( 1,  2,  PLAYER_B_));
    CHECK(match_expected_right_column( 1,  0,  PLAYER_A_));
}

//16. Test match_expected_left_column function
TEST(match_expected_left_column){

    CHECK(match_expected_left_column( 1,  0,  PLAYER_B_));
    CHECK(match_expected_left_column( 1,  2,  PLAYER_A_));
}

//17. Test match_expected_row function
TEST(match_expected_row){

    CHECK(match_expected_row( 2,  1,  PLAYER_B_));
    CHECK(match_expected_row( 2,  3,  PLAYER_A_));
}

//18. Test matrix_row_index_2_displayed function
TEST(matrix_row_index_2_displayed){
    CHECK_EQUAL(8,matrix_row_index_2_displayed( 10,  2));
}

//19. Test matrix_row_index_2_displayed function
TEST(exist_own_pawn){
    player_board pb;
    pb.playerB_board= initialize_board(4,4,PLAYER_B_);
    posn pos{3,1};
    CHECK(exist_own_pawn( pos,PLAYER_B_,pb));


    player_board pb1;
    pb1.playerA_board= initialize_board(4,4,PLAYER_A_);
    posn pos1{0,1};
    CHECK(exist_own_pawn( pos1,PLAYER_A_,pb1));
}

//20. Test displayed_row_index_2_matrix function
TEST(displayed_row_index_2_matrix){
    player_board pb;
    pb.playerB_board= initialize_board(4,4,PLAYER_B_);
    pb.playerA_board= initialize_board(4,4,PLAYER_A_);
    char a_C='1';
    CHECK_EQUAL(3,displayed_row_index_2_matrix(a_C,pb));
}

//21. Test get_lop function
TEST(get_lop){
    player_board pb;
    pb.playerB_board= initialize_board(4,4,PLAYER_B_);
    pb.playerA_board= initialize_board(4,4,PLAYER_A_);

   lop lop1= get_lop("a1-a2",pb);
    CHECK_EQUAL(3,lop1.start_posn.row_index);
    CHECK_EQUAL(2,lop1.end_posn.row_index);
    CHECK_EQUAL(1,lop1.start_posn.column_index);
    CHECK_EQUAL(1,lop1.end_posn.column_index);
}

//22. Test is_not_blocked function
TEST(is_not_blocked){

    player_board pb;
    pb.playerA_board= initialize_board(4,4,PLAYER_A_);
    pb.playerB_board= initialize_board(4,4,PLAYER_B_);


    pb.playerB_board.at(2).at(1)=1;
    pb.playerA_board.at(1).at(3)=1;

    posn centerA1{0,3};
    posn centerA2{0,4};


    posn centerB1{3,1};
    posn centerB2{3,2};

    resultCase case1;
    resultCase case2;
    resultCase case3;
    resultCase case4;
    resultCase case5;
    resultCase case6;
    resultCase case7;
    resultCase case8;

    case1.index=1;
    case2.index=2;
    case3.index=3;
    case4.index=4;
    case5.index=5;
    case6.index=6;
    case7.index=7;
    case8.index=8;
//    std::vector<resultCase>cases{case1,case2,case3,case4,case5,case6,case7,case8};
//    for(int i=0;i<cases.size();++i){
//        cases.at(i).index=i+1;
//    }


    CHECK(!is_not_blocked(case1,centerA1,PLAYER_A_,pb));
    CHECK( is_not_blocked(case1,centerA2,PLAYER_A_,pb));

    CHECK(!is_not_blocked(case1,centerB1,PLAYER_B_,pb));
    CHECK( is_not_blocked(case1,centerB2,PLAYER_B_,pb));


    CHECK( is_not_blocked(case2,centerA2,PLAYER_A_,pb));
    CHECK( is_not_blocked(case3,centerA2,PLAYER_A_,pb));
    CHECK( !is_not_blocked(case4,centerA2,PLAYER_A_,pb));
    CHECK( is_not_blocked(case5,centerA2,PLAYER_A_,pb));
    CHECK( is_not_blocked(case6,centerA2,PLAYER_A_,pb));
    CHECK( is_not_blocked(case7,centerA2,PLAYER_A_,pb));
    CHECK( is_not_blocked(case8,centerA2,PLAYER_A_,pb));

    CHECK( is_not_blocked(case2,centerB2,PLAYER_B_,pb));
    CHECK( is_not_blocked(case3,centerB2,PLAYER_B_,pb));
    CHECK( !is_not_blocked(case4,centerB2,PLAYER_B_,pb));
    CHECK( is_not_blocked(case5,centerB2,PLAYER_B_,pb));
    CHECK( is_not_blocked(case6,centerB2,PLAYER_B_,pb));
    CHECK( is_not_blocked(case7,centerB2,PLAYER_B_,pb));
    CHECK( is_not_blocked(case8,centerB2,PLAYER_B_,pb));






}
TEST(is_not_blocked2){
    player_board pb;
    pb.playerB_board = initialize_board(8, 8, PLAYER_B_);
    pb.playerA_board = initialize_board(8, 8, PLAYER_A_);

    pb.playerB_board.at(1).at(3) = 1;
    pb.playerB_board.at(1).at(4) = 1;
    pb.playerB_board.at(1).at(6) = 1;
    pb.playerB_board.at(3).at(2) = 1;
    pb.playerB_board.at(3).at(3) = 1;

    pb.playerB_board.at(3).at(4) = 1;
    pb.playerB_board.at(3).at(5) = 1;
    pb.playerB_board.at(5).at(3) = 1;
    pb.playerB_board.at(5).at(5) = 1;
    pb.playerB_board.at(5).at(7) = 1;


    pb.playerA_board.at(2).at(1) = 1;
    pb.playerA_board.at(2).at(3) = 1;
    pb.playerA_board.at(2).at(5) = 1;
    pb.playerA_board.at(4).at(3) = 1;
    pb.playerA_board.at(4).at(4) = 1;

    pb.playerA_board.at(4).at(6) = 1;
    pb.playerA_board.at(4).at(7) = 1;
    pb.playerA_board.at(4).at(8) = 1;
    pb.playerA_board.at(6).at(3) = 1;
    pb.playerA_board.at(6).at(5) = 1;

    pb.playerA_board.at(6).at(6) = 1;

    posn posB1{7, 1};
    posn posB1_M{6, 1};
    posn posB1_L{6, 0};
    posn posB1_R{6, 2};
    posn posB1_ARBT{0, 1};
    posn posB1_ARBT1{1, 1};

    posn posB2{7, 7};
    posn posB2_M{6, 7};
    posn posB2_L{6, 6};
    posn posB2_R{6, 8};

    posn posB3{7, 2};
    posn posB3_M{6, 2};
    posn posB3_L{6, 1};
    posn posB3_R{6, 3};

    posn posB4{7, 3};
    posn posB4_M{6, 3};
    posn posB4_L{6, 2};
    posn posB4_R{6, 4};

    posn posB5{7, 6};
    posn posB5_M{6, 6};
    posn posB5_L{6, 5};
    posn posB5_R{6, 7};


    posn posB6{5, 5};
    posn posB6_M{4, 5};
    posn posB6_L{4, 4};
    posn posB6_R{4, 6};


    posn posB7{5, 3};
    posn posB7_M{4, 3};
    posn posB7_L{4, 2};
    posn posB7_R{4, 4};


    posn posB8{5, 7};
    posn posB8_M{4, 7};
    posn posB8_L{4, 6};
    posn posB8_R{4, 8};


    posn posA1{0, 8};
    posn posA1_M{1, 8};
    posn posA1_L{1, 9};
    posn posA1_R{1, 7};
    posn posA1_ARBT{7, 1};


    posn posA2{2, 1};
    posn posA2_M{3, 1};
    posn posA2_L{3, 2};
    posn posA2_R{3, 0};


    posn posA3{0, 7};
    posn posA3_M{1, 7};
    posn posA3_L{1, 8};
    posn posA3_R{1, 6};


    posn posA4{0, 6};
    posn posA4_M{1, 6};
    posn posA4_L{1, 7};
    posn posA4_R{1, 5};

    posn posA5{0, 3};
    posn posA5_M{1, 3};
    posn posA5_L{1, 4};
    posn posA5_R{1, 2};


    posn posA6{0, 5};
    posn posA6_M{1, 5};
    posn posA6_L{1, 6};
    posn posA6_R{1, 4};


    posn posA7{2, 5};
    posn posA7_M{3, 5};
    posn posA7_L{3, 6};
    posn posA7_R{3, 4};


    posn posA8{2, 3};
    posn posA8_M{3, 3};
    posn posA8_L{3, 4};
    posn posA8_R{3, 2};

    resultCase case1;
    case1.index=1;

    CHECK( is_not_blocked(case1,posB1,PLAYER_B_,pb));

    //For palyer B:
    //Case 1
    pb.playerB_board.at(6).at(1) = 1;
    CHECK( !is_not_blocked(case1,posB1,PLAYER_B_,pb));
}

//23. Test get_current_2_3_board function
TEST(get_current_2_3_board) {

    player_board pb;
    pb.playerB_board = initialize_board(8, 8, PLAYER_B_);
    pb.playerA_board = initialize_board(8, 8, PLAYER_A_);

    pb.playerB_board.at(1).at(3) = 1;
    pb.playerB_board.at(1).at(4) = 1;
    pb.playerB_board.at(1).at(6) = 1;
    pb.playerB_board.at(3).at(2) = 1;
    pb.playerB_board.at(3).at(3) = 1;

    pb.playerB_board.at(3).at(4) = 1;
    pb.playerB_board.at(3).at(5) = 1;
    pb.playerB_board.at(5).at(3) = 1;
    pb.playerB_board.at(5).at(5) = 1;
    pb.playerB_board.at(5).at(7) = 1;


    pb.playerA_board.at(2).at(1) = 1;
    pb.playerA_board.at(2).at(3) = 1;
    pb.playerA_board.at(2).at(5) = 1;
    pb.playerA_board.at(4).at(3) = 1;
    pb.playerA_board.at(4).at(4) = 1;

    pb.playerA_board.at(4).at(6) = 1;
    pb.playerA_board.at(4).at(7) = 1;
    pb.playerA_board.at(4).at(8) = 1;
    pb.playerA_board.at(6).at(3) = 1;
    pb.playerA_board.at(6).at(5) = 1;

    pb.playerA_board.at(6).at(6) = 1;

    posn posB1{7, 1};
    posn posB2{7, 7};
    posn posB3{7, 2};
    posn posB4{7, 3};
    posn posB5{7, 6};
    posn posB6{5, 5};
    posn posB7{5, 3};
    posn posB8{5, 7};


    posn posA1{0, 8};
    posn posA2{2, 1};
    posn posA3{0, 7};
    posn posA4{0, 6};
    posn posA5{0, 3};
    posn posA6{0, 5};
    posn posA7{2, 5};
    posn posA8{2, 3};

    CHECK(get_case(1)==get_current_2_3_board(posB1,PLAYER_B_,pb));
    CHECK(get_case(2)==get_current_2_3_board(posB2,PLAYER_B_,pb));
    CHECK(get_case(3)==get_current_2_3_board(posB3,PLAYER_B_,pb));
    CHECK(get_case(4)==get_current_2_3_board(posB4,PLAYER_B_,pb));
    CHECK(get_case(5)==get_current_2_3_board(posB5,PLAYER_B_,pb));
    CHECK(get_case(6)==get_current_2_3_board(posB6,PLAYER_B_,pb));
    CHECK(get_case(7)==get_current_2_3_board(posB7,PLAYER_B_,pb));
    CHECK(get_case(8)==get_current_2_3_board(posB8,PLAYER_B_,pb));

    CHECK(get_case(1)==get_current_2_3_board(posA1,PLAYER_A_,pb));
    CHECK(get_case(2)==get_current_2_3_board(posA2,PLAYER_A_,pb));
    CHECK(get_case(3)==get_current_2_3_board(posA3,PLAYER_A_,pb));
    CHECK(get_case(4)==get_current_2_3_board(posA4,PLAYER_A_,pb));
    CHECK(get_case(5)==get_current_2_3_board(posA5,PLAYER_A_,pb));
    CHECK(get_case(6)==get_current_2_3_board(posA6,PLAYER_A_,pb));
    CHECK(get_case(7)==get_current_2_3_board(posA7,PLAYER_A_,pb));
    CHECK(get_case(8)==get_current_2_3_board(posA8,PLAYER_A_,pb));
    //std::cout<<'\n';
    // print_board( pb.playerA_board,  pb.playerB_board);
}

//  | a | b | c | d | e | f | g | h |
//---+---+---+---+---+---+---+---+---+---
//8 | B | B | B | B | B | B | B | B | 8
//---+---+---+---+---+---+---+---+---+---
//7 |   |   | W | W |   | W |   |   | 7
//---+---+---+---+---+---+---+---+---+---
//6 | B |   | B |   | B |   |   |   | 6
//---+---+---+---+---+---+---+---+---+---
//5 |   | W | W | W | W |   |   |   | 5
//---+---+---+---+---+---+---+---+---+---
//4 |   |   | B | B |   | B | B | B | 4
//---+---+---+---+---+---+---+---+---+---
//3 |   |   | W |   | W |   | W |   | 3
//---+---+---+---+---+---+---+---+---+---
//2 |   |   | B |   | B | B |   |   | 2
//---+---+---+---+---+---+---+---+---+---
//1 | W | W | W | W | W | W | W | W | 1
//---+---+---+---+---+---+---+---+---+---
//   | a | b | c | d | e | f | g | h |

//24. Test get_result_case_without_interfer_by_own_pawn function, this implicitly testing
//   the check_playerA_movement and check_playerB_movement
TEST(get_result_case_without_interfer_by_own_pawn){

    player_board pb;
    pb.playerB_board= initialize_board(8,8,PLAYER_B_);
    pb.playerA_board= initialize_board(8,8,PLAYER_A_);

    pb.playerB_board.at(1).at(3)=1;
    pb.playerB_board.at(1).at(4)=1;
    pb.playerB_board.at(1).at(6)=1;
    pb.playerB_board.at(3).at(2)=1;
    pb.playerB_board.at(3).at(3)=1;

    pb.playerB_board.at(3).at(4)=1;
    pb.playerB_board.at(3).at(5)=1;
    pb.playerB_board.at(5).at(3)=1;
    pb.playerB_board.at(5).at(5)=1;
    pb.playerB_board.at(5).at(7)=1;


    pb.playerA_board.at(2).at(1)=1;
    pb.playerA_board.at(2).at(3)=1;
    pb.playerA_board.at(2).at(5)=1;
    pb.playerA_board.at(4).at(3)=1;
    pb.playerA_board.at(4).at(4)=1;

    pb.playerA_board.at(4).at(6)=1;
    pb.playerA_board.at(4).at(7)=1;
    pb.playerA_board.at(4).at(8)=1;
    pb.playerA_board.at(6).at(3)=1;
    pb.playerA_board.at(6).at(5)=1;

    pb.playerA_board.at(6).at(6)=1;

    posn posB1{7, 1};
    posn posB1_M{6, 1};
    posn posB1_L{6, 0};
    posn posB1_R{6, 2};
    posn posB1_ARBT{0, 1};
    posn posB1_ARBT1{1, 1};

    posn posB2{7, 7};
    posn posB2_M{6, 7};
    posn posB2_L{6, 6};
    posn posB2_R{6, 8};

    posn posB3{7, 2};
    posn posB3_M{6, 2};
    posn posB3_L{6, 1};
    posn posB3_R{6, 3};

    posn posB4{7, 3};
    posn posB4_M{6, 3};
    posn posB4_L{6, 2};
    posn posB4_R{6, 4};

    posn posB5{7, 6};
    posn posB5_M{6, 6};
    posn posB5_L{6, 5};
    posn posB5_R{6, 7};



    posn posB6{5, 5};
    posn posB6_M{4, 5};
    posn posB6_L{4, 4};
    posn posB6_R{4, 6};


    posn posB7{5, 3};
    posn posB7_M{4, 3};
    posn posB7_L{4, 2};
    posn posB7_R{4, 4};


    posn posB8{5, 7};
    posn posB8_M{4, 7};
    posn posB8_L{4, 6};
    posn posB8_R{4, 8};



    posn posA1{0, 8};
    posn posA1_M{1, 8};
    posn posA1_L{1, 9};
    posn posA1_R{1, 7};
    posn posA1_ARBT{7, 1};


    posn posA2{2, 1};
    posn posA2_M{3, 1};
    posn posA2_L{3, 2};
    posn posA2_R{3, 0};


    posn posA3{0, 7};
    posn posA3_M{1, 7};
    posn posA3_L{1, 8};
    posn posA3_R{1, 6};



    posn posA4{0, 6};
    posn posA4_M{1, 6};
    posn posA4_L{1, 7};
    posn posA4_R{1, 5};

    posn posA5{0, 3};
    posn posA5_M{1, 3};
    posn posA5_L{1, 4};
    posn posA5_R{1, 2};


    posn posA6{0, 5};
    posn posA6_M{1, 5};
    posn posA6_L{1, 6};
    posn posA6_R{1, 4};


    posn posA7{2, 5};
    posn posA7_M{3, 5};
    posn posA7_L{3, 6};
    posn posA7_R{3, 4};


    posn posA8{2, 3};
    posn posA8_M{3, 3};
    posn posA8_L{3, 4};
    posn posA8_R{3, 2};


    //For palyer B:
    //Case 1
    CHECK_EQUAL(1,get_result_case(get_case(1),posB1,posB1_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(1),posB1,posB1_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posB1,posB1_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posB1,posB1_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_R,PLAYER_B_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posB1,posB1_ARBT,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_ARBT,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_ARBT,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_ARBT,PLAYER_B_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posB1,posB1_ARBT1,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_ARBT1,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_ARBT1,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posB1,posB1_ARBT1,PLAYER_B_,pb).right);


    //Case 2
    CHECK_EQUAL(2,get_result_case(get_case(2),posB2,posB2_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(2),posB2,posB2_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(2,get_result_case(get_case(2),posB2,posB2_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(2),posB2,posB2_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(2,get_result_case(get_case(2),posB2,posB2_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(2),posB2,posB2_R,PLAYER_B_,pb).right);

    //Case 3
    CHECK_EQUAL(3,get_result_case(get_case(3),posB3,posB3_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(3),posB3,posB3_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(3,get_result_case(get_case(3),posB3,posB3_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(3,get_result_case(get_case(3),posB3,posB3_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(3),posB3,posB3_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(3),posB3,posB3_R,PLAYER_B_,pb).right);

    //Case 4
    CHECK_EQUAL(4,get_result_case(get_case(4),posB4,posB4_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(4,get_result_case(get_case(4),posB4,posB4_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(4,get_result_case(get_case(4),posB4,posB4_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(4),posB4,posB4_R,PLAYER_B_,pb).right);


    //Case 5
    CHECK_EQUAL(5,get_result_case(get_case(5),posB5,posB5_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(5,get_result_case(get_case(5),posB5,posB5_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(5),posB5,posB5_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(5,get_result_case(get_case(5),posB5,posB5_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(5),posB5,posB5_R,PLAYER_B_,pb).right);


    //Case 6
    CHECK_EQUAL(6,get_result_case(get_case(6),posB6,posB6_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(6),posB6,posB6_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(6),posB6,posB6_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(6),posB6,posB6_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(6,get_result_case(get_case(6),posB6,posB6_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(6),posB6,posB6_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(6),posB6,posB6_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(6),posB6,posB6_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(6,get_result_case(get_case(6),posB6,posB6_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(6),posB6,posB6_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(6),posB6,posB6_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(6),posB6,posB6_R,PLAYER_B_,pb).right);

    //Case 7
    CHECK_EQUAL(7,get_result_case(get_case(7),posB7,posB7_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(7,get_result_case(get_case(7),posB7,posB7_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(7,get_result_case(get_case(7),posB7,posB7_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(7),posB7,posB7_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(7),posB7,posB7_R,PLAYER_B_,pb).right);

    //Case 8
    CHECK_EQUAL(8,get_result_case(get_case(8),posB8,posB8_M,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_M,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_M,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_M,PLAYER_B_,pb).right);

    CHECK_EQUAL(8,get_result_case(get_case(8),posB8,posB8_L,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_L,PLAYER_B_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(8),posB8,posB8_L,PLAYER_B_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_L,PLAYER_B_,pb).right);

    CHECK_EQUAL(8,get_result_case(get_case(8),posB8,posB8_R,PLAYER_B_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_R,PLAYER_B_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(8),posB8,posB8_R,PLAYER_B_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(8),posB8,posB8_R,PLAYER_B_,pb).right);



    //For palyer A:
    //Case 1
    CHECK_EQUAL(1,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posA1,posA1_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posA1,posA1_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_R,PLAYER_A_,pb).right);

    CHECK_EQUAL(1,get_result_case(get_case(1),posA1,posA1_ARBT,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_ARBT,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_ARBT,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_ARBT,PLAYER_A_,pb).right);




    //Case 2
    CHECK_EQUAL(2,get_result_case(get_case(2),posA2,posA2_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(2),posA2,posA2_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(2,get_result_case(get_case(2),posA2,posA2_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(2),posA2,posA2_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(2,get_result_case(get_case(2),posA2,posA2_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(2),posA2,posA2_R,PLAYER_A_,pb).right);

    //Case 3
    CHECK_EQUAL(3,get_result_case(get_case(3),posA3,posA3_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(3),posA3,posA3_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(3,get_result_case(get_case(3),posA3,posA3_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(3,get_result_case(get_case(3),posA3,posA3_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(3),posA3,posA3_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(3),posA3,posA3_R,PLAYER_A_,pb).right);

    //Case 4
    CHECK_EQUAL(4,get_result_case(get_case(4),posA4,posA4_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(4,get_result_case(get_case(4),posA4,posA4_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(4,get_result_case(get_case(4),posA4,posA4_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(4),posA4,posA4_R,PLAYER_A_,pb).right);


    //Case 5
    CHECK_EQUAL(5,get_result_case(get_case(5),posA5,posA5_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(5,get_result_case(get_case(5),posA5,posA5_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(5),posA5,posA5_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(5,get_result_case(get_case(5),posA5,posA5_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(5),posA5,posA5_R,PLAYER_A_,pb).right);


    //Case 6
    CHECK_EQUAL(6,get_result_case(get_case(6),posA6,posA6_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(true,get_result_case(get_case(6),posA6,posA6_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(6),posA6,posA6_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(6),posA6,posA6_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(6,get_result_case(get_case(6),posA6,posA6_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(6),posA6,posA6_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(6),posA6,posA6_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(6),posA6,posA6_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(6,get_result_case(get_case(6),posA6,posA6_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(6),posA6,posA6_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(6),posA6,posA6_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(6),posA6,posA6_R,PLAYER_A_,pb).right);

    //Case 7
    CHECK_EQUAL(7,get_result_case(get_case(7),posA7,posA7_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(7,get_result_case(get_case(7),posA7,posA7_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(7,get_result_case(get_case(7),posA7,posA7_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(7),posA7,posA7_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(7),posA7,posA7_R,PLAYER_A_,pb).right);

    //Case 8
    CHECK_EQUAL(8,get_result_case(get_case(8),posA8,posA8_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_M,PLAYER_A_,pb).right);

    CHECK_EQUAL(8,get_result_case(get_case(8),posA8,posA8_L,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_L,PLAYER_A_,pb).front);
    CHECK_EQUAL(true,get_result_case(get_case(8),posA8,posA8_L,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_L,PLAYER_A_,pb).right);

    CHECK_EQUAL(8,get_result_case(get_case(8),posA8,posA8_R,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_R,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(8),posA8,posA8_R,PLAYER_A_,pb).left);
    CHECK_EQUAL(true,get_result_case(get_case(8),posA8,posA8_R,PLAYER_A_,pb).right);

}


TEST(get_result_case_with_interfer_by_own_pawn) {

    player_board pb;
    pb.playerB_board = initialize_board(8, 8, PLAYER_B_);
    pb.playerA_board = initialize_board(8, 8, PLAYER_A_);

    pb.playerB_board.at(1).at(3) = 1;
    pb.playerB_board.at(1).at(4) = 1;
    pb.playerB_board.at(1).at(6) = 1;
    pb.playerB_board.at(3).at(2) = 1;
    pb.playerB_board.at(3).at(3) = 1;

    pb.playerB_board.at(3).at(4) = 1;
    pb.playerB_board.at(3).at(5) = 1;
    pb.playerB_board.at(5).at(3) = 1;
    pb.playerB_board.at(5).at(5) = 1;
    pb.playerB_board.at(5).at(7) = 1;


    pb.playerA_board.at(2).at(1) = 1;
    pb.playerA_board.at(2).at(3) = 1;
    pb.playerA_board.at(2).at(5) = 1;
    pb.playerA_board.at(4).at(3) = 1;
    pb.playerA_board.at(4).at(4) = 1;

    pb.playerA_board.at(4).at(6) = 1;
    pb.playerA_board.at(4).at(7) = 1;
    pb.playerA_board.at(4).at(8) = 1;
    pb.playerA_board.at(6).at(3) = 1;
    pb.playerA_board.at(6).at(5) = 1;

    pb.playerA_board.at(6).at(6) = 1;

    posn posB1{7, 1};
    posn posB1_M{6, 1};
    posn posB1_L{6, 0};
    posn posB1_R{6, 2};
    posn posB1_ARBT{0, 1};
    posn posB1_ARBT1{1, 1};

    posn posB2{7, 7};
    posn posB2_M{6, 7};
    posn posB2_L{6, 6};
    posn posB2_R{6, 8};

    posn posB3{7, 2};
    posn posB3_M{6, 2};
    posn posB3_L{6, 1};
    posn posB3_R{6, 3};

    posn posB4{7, 3};
    posn posB4_M{6, 3};
    posn posB4_L{6, 2};
    posn posB4_R{6, 4};

    posn posB5{7, 6};
    posn posB5_M{6, 6};
    posn posB5_L{6, 5};
    posn posB5_R{6, 7};


    posn posB6{5, 5};
    posn posB6_M{4, 5};
    posn posB6_L{4, 4};
    posn posB6_R{4, 6};


    posn posB7{5, 3};
    posn posB7_M{4, 3};
    posn posB7_L{4, 2};
    posn posB7_R{4, 4};


    posn posB8{5, 7};
    posn posB8_M{4, 7};
    posn posB8_L{4, 6};
    posn posB8_R{4, 8};


    posn posA1{0, 8};
    posn posA1_M{1, 8};
    posn posA1_L{1, 9};
    posn posA1_R{1, 7};
    posn posA1_ARBT{7, 1};


    posn posA2{2, 1};
    posn posA2_M{3, 1};
    posn posA2_L{3, 2};
    posn posA2_R{3, 0};


    posn posA3{0, 7};
    posn posA3_M{1, 7};
    posn posA3_L{1, 8};
    posn posA3_R{1, 6};


    posn posA4{0, 6};
    posn posA4_M{1, 6};
    posn posA4_L{1, 7};
    posn posA4_R{1, 5};

    posn posA5{0, 3};
    posn posA5_M{1, 3};
    posn posA5_L{1, 4};
    posn posA5_R{1, 2};


    posn posA6{0, 5};
    posn posA6_M{1, 5};
    posn posA6_L{1, 6};
    posn posA6_R{1, 4};


    posn posA7{2, 5};
    posn posA7_M{3, 5};
    posn posA7_L{3, 6};
    posn posA7_R{3, 4};


    posn posA8{2, 3};
    posn posA8_M{3, 3};
    posn posA8_L{3, 4};
    posn posA8_R{3, 2};





    //For palyer B:
    //Case 1
    pb.playerB_board.at(6).at(1) = 1;
    CHECK_EQUAL(1, get_result_case(get_case(1), posB1, posB1_M, PLAYER_B_, pb).index);
    CHECK_EQUAL(false, get_result_case(get_case(1), posB1, posB1_M, PLAYER_B_, pb).front);
    CHECK_EQUAL(false, get_result_case(get_case(1), posB1, posB1_M, PLAYER_B_, pb).left);
    CHECK_EQUAL(false, get_result_case(get_case(1), posB1, posB1_M, PLAYER_B_, pb).right);


    //For palyer A:
    //Case 1
    pb.playerA_board.at(1).at(8) = 1;
    CHECK_EQUAL(1,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).index);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).front);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).left);
    CHECK_EQUAL(false,get_result_case(get_case(1),posA1,posA1_M,PLAYER_A_,pb).right);


}

//25. Test is_opponent_reach_end function
TEST(is_opponent_reach_end){

    player_board pb;

    pb.playerB_board = initialize_board(8, 8, PLAYER_B_);
    pb.playerA_board = initialize_board(8, 8, PLAYER_A_);
    //pb.playerB_board.at(1).at(3) = 1;
  //  pb.playerB_board.at(1).at(4) = 1;

    CHECK(!is_opponent_reach_end(PLAYER_B_,pb));
    CHECK(!is_opponent_reach_end(PLAYER_A_,pb));

    pb.playerB_board = initialize_board(8, 8, PLAYER_A_);
    pb.playerA_board = initialize_board(8, 8, PLAYER_B_);

    CHECK(is_opponent_reach_end(PLAYER_B_,pb));
    CHECK(is_opponent_reach_end(PLAYER_A_,pb));

    pb.playerB_board = initialize_board(8, 8, PLAYER_B_);
    pb.playerA_board = initialize_board(8, 8, PLAYER_A_);
    pb.playerB_board[0][3]=1;
    CHECK(!is_opponent_reach_end(PLAYER_B_,pb));
    CHECK(is_opponent_reach_end(PLAYER_A_,pb));

    pb.playerA_board[7][3]=1;
    CHECK(is_opponent_reach_end(PLAYER_B_,pb));
    CHECK(is_opponent_reach_end(PLAYER_A_,pb));


    pb.playerB_board[0][3]=0;

    CHECK(is_opponent_reach_end(PLAYER_B_,pb));
    CHECK(!is_opponent_reach_end(PLAYER_A_,pb));
}

//26. Test is_all_pawns_captured function
TEST(is_all_pawns_captured){

        player_board pb;

        pb.playerB_board = initialize_board(8, 8, PLAYER_B_);
        pb.playerA_board = initialize_board(8, 8, PLAYER_A_);

    CHECK(!is_all_pawns_captured(PLAYER_B_,pb));
    CHECK(!is_all_pawns_captured(PLAYER_B_,pb));

    for(int i=0;i<pb.playerB_board.size();++i){
        for(int j=0;j<pb.playerB_board.at(0).size();++j){
            pb.playerB_board.at(i).at(j)=0;
        }
    }
        CHECK(is_all_pawns_captured(PLAYER_B_,pb));
    for(int i=0;i<pb.playerB_board.size();++i){
        for(int j=0;j<pb.playerB_board.at(0).size();++j){
            pb.playerA_board.at(i).at(j)=0;
        }
    }
    CHECK(is_all_pawns_captured(PLAYER_A_,pb));
    CHECK(is_all_pawns_captured(PLAYER_B_,pb));


    pb.playerB_board.at(3).at(2)=1;
    CHECK(!is_all_pawns_captured(PLAYER_B_,pb));
    CHECK(is_all_pawns_captured(PLAYER_A_,pb));



    pb.playerA_board.at(3).at(3)=1;
    CHECK(!is_all_pawns_captured(PLAYER_B_,pb));
    CHECK(!is_all_pawns_captured(PLAYER_A_,pb));


}

//27. Test is_all_pawns_blocked function
TEST(is_all_pawns_blocked){

    //The situation where blocked all by opponent
    player_board pb;
    pb.playerB_board = initialize_board(3, 3, PLAYER_B_);
    pb.playerA_board = initialize_board(3, 3, PLAYER_A_);
    pb.playerA_board[0][2]=0;
    pb.playerA_board[0][3]=0;
    pb.playerA_board[1][3]=1;

    pb.playerB_board[2][1]=0;
    pb.playerB_board[2][2]=0;
    pb.playerB_board[1][1]=1;
            ;
    CHECK(is_all_pawns_blocked(PLAYER_B_,pb));
    CHECK(is_all_pawns_blocked(PLAYER_A_,pb));

    //Some pawns are blocked by own pawn
    pb.playerB_board[1][1]=0;
    pb.playerA_board[1][1]=1;
    CHECK(is_all_pawns_blocked(PLAYER_B_,pb));
    CHECK(!is_all_pawns_blocked(PLAYER_A_,pb));

     pb.playerB_board[2][1]=1;

    CHECK(is_all_pawns_blocked(PLAYER_B_,pb));
    CHECK(is_all_pawns_blocked(PLAYER_A_,pb));
}

//28. Test move_sytax_check function
TEST(move_sytax_check){
    player_board pb;
    pb.playerB_board = initialize_board(3, 3, PLAYER_B_);
    pb.playerA_board = initialize_board(3, 3, PLAYER_A_);
    CHECK(!move_sytax_check("abc",pb));
    CHECK(move_sytax_check("a1-a2",pb));

}

//29. Print all size of board (from 3*3 to 8*8)
/*
TEST(print_board){
    for(int i=3;i<9;++i){
        for(int j=3;j<9;++j){
            player_board a_player_board;
            a_player_board.playerA_board=initialize_board(i,j,PLAYER_A_);
            a_player_board.playerB_board=initialize_board(i,j,PLAYER_B_);

            print_board(a_player_board.playerA_board,a_player_board.playerB_board);
        }
    }
}

*/







