#include "hexapawn.h"

//Initialize players board
board initialize_board(size_t height, size_t width, size_t player_index){

    size_t container_width=width+2;
    board player_board;

    //Initialize the board for player B
    if(player_index==PLAYER_B_){
    //Initilize the hexapawn board without pawn
    for(int i=0;i<height-1;++i){
        player_board.emplace_back(container_width,0);
    }
    player_board.emplace_back(container_width,1);
        player_board.at(height-1).at(0)=0;
        player_board.at(height-1).at(container_width-1)=0;
    }
        //Initialize the board for player A
    else {
        player_board.emplace_back(container_width,1);

        player_board.at(0).at(0)=0;
        player_board.at(0).at(container_width-1)=0;

        //Initilize the hexapawn board without pawn
        for(int i=0;i<height-1;++i){
            player_board.emplace_back(container_width,0);
        }
    }


    return  player_board;
}

//Return the corresponding case
std::vector< std::vector<size_t>> get_case(size_t index){
   // std::vector< std::vector<size_t>> result;

    switch(index) {
        case 1 :{
            std::vector< std::vector<size_t>> case1= get_two_three_vector();
         //   case1[1][1]=1;
            return   case1;
            break;       // and exits the switch
             }
        case 2 :{
            std::vector< std::vector<size_t>> case2= get_two_three_vector();
            case2[0][0]=1;
            return  case2;
            break; }
        case 3 :{
            std::vector< std::vector<size_t>> case3= get_two_three_vector();
            case3[0][2]=1;
            return   case3;
            break; }
        case 4 :{
            std::vector< std::vector<size_t>> case4= get_two_three_vector();
            case4[0][1]=1;
            return   case4;
            break; }
        case 5 :{
            std::vector< std::vector<size_t>> case5= get_two_three_vector();
            case5[0][0]=1;
            case5[0][1]=1;
            return   case5;
            break; }
        case 6 :{
            std::vector< std::vector<size_t>> case6= get_two_three_vector();
            case6[0][0]=1;
            case6[0][2]=1;
            return   case6;
            break; }
        case 7 :{
            std::vector< std::vector<size_t>> case7= get_two_three_vector();
            case7[0][1]=1;
            case7[0][2]=1;
            return  case7;
            break; }
        case 8 :{
            std::vector< std::vector<size_t>> case8= get_two_three_vector();
            case8[0][0]=1;
            case8[0][1]=1;
            case8[0][2]=1;
            return  case8;
            break; }
    }
}



//Initialize a 2*3 vector filled with 0;
//  Solution Reference:
//   http://stackoverflow.com/questions/823562/multi-dimensional-vector
std::vector< std::vector<size_t>>  get_two_three_vector(){
    std::vector< std::vector<size_t>> two_three_vector;

    for(int i=0;i<2;++i){
            two_three_vector.emplace_back(3,0);
        }


 //   std::cout<<two_three_vector[0][0]<<'n';
 //   std::cout<<two_three_vector[1][2];
    return  two_three_vector;
}


// Compares two graphs for equality by comparing all edges and weights.
bool operator==(const posn a, const posn b){
    bool result= false;
    if(a.row_index==b.row_index){
        if(a.column_index==b.column_index){
            result=true;
        }
    }
    return result;
}


//Check whether the movement is valid, the invalid contains either:
//  1. There is no existance case matched, where the case index is -1
//  2. The case matched the current "board", but the movement might still not be allowed,
//     when "left" "right" "front" are all false. That includes the case 4.
bool get_bool(resultCase aCase) {
    bool result=true;

    if(aCase.index==(-1)){
        result= false;
    }
    if((!aCase.front)&&(!aCase.left)&&(!aCase.right)){
        result= false;
    }
    return result;
}

//Print player's board according to index
void print_board(const board& playerA_board, const board& playerB_board,size_t player_index) {

    //Assure both playerA and playerB board are valid to each other, e.g. must have same size
    board_valid_check(playerA_board,playerB_board);

    size_t num_of_rows=playerA_board.size();
    size_t num_of_act_columns=playerA_board.at(0).size()-2;



    std::string row_index=get_index_row(num_of_act_columns);
    std::string seperate_line=get_seperate_line(num_of_act_columns);

    std::cout << row_index;
    std::cout << seperate_line;
if(player_index==PLAYER_B_){
    for(int i=0;i<num_of_rows;++i){
        std::cout <<get_row(playerA_board,playerB_board,i);
        std::cout << seperate_line;
    }
}
    else{
    for(int i=num_of_rows-1;i>=0;--i){
        std::cout <<get_row(playerA_board,playerB_board,i);
        std::cout << seperate_line;
    }

}
    std::cout << row_index;



}

//Get the index row
const std::string get_index_row(size_t width){
    std::vector<std::string>output;//(width,"   ");
    for(int i=0;i<width;++i){
        output.emplace_back(" "+ROW_INDEX.at(i)+" ");
    }
    std::string result= "   "+add_seperator(output);
    result+='\n';
    return  result;
}

//Ensure the consistency between two players' board
void board_valid_check(const board& playerA, const board& playerB) {
    assert(playerA.size() ==playerB.size());
    assert(playerA.at(0).size() ==playerB.at(0).size());
}

//Get row for the whole playing board
const std::string get_row(const board& playerA, const board& playerB, size_t index){

    size_t height=playerA.size();
    size_t width=playerA.at(0).size()-2;//We extend out width in the beginning

    //  size_t row_index_4_display=height-index;

    size_t row_index_4_display=matrix_row_index_2_displayed(height,index);



    //size_t row_index_4_playerA=height-1-index;
    size_t row_index_4_playerA=index;
    size_t row_index_4_playerB=index;

    std::vector<std::string>output(width,"   ");

    //Add playerA's pawn (aka, black pawns)
    for(int i=1;i<width+1;++i){
        if(playerA.at(row_index_4_playerA).at(i)==1){
            output.at(i-1)=" B "; //Align the index
        }
    }


    //Add playerB's pawn (aka, white pawns)
    for(int i=1;i<width+1;++i){
        if(playerB.at(row_index_4_playerB).at(i)==1){
            output.at(i-1)=" W "; //Align the index
        }
    }



    std::string s=add_seperator(output);
    std::string row_index =std::to_string(row_index_4_display);
    std::string result    = "  "+row_index+s+row_index+" \n";


    return result;
}

//Map the matrix row index to displayed format
size_t matrix_row_index_2_displayed(size_t height, size_t index) {
    return (height-index);
}

//Add the seperator for each spawn
const std::string add_seperator(const std::vector<std::string>& vector_string){
    //Add seperators into the vector string
    //Ref:http://stackoverflow.com/questions/1430757/c-vector-to-string
    std::stringstream ss;
    for(size_t i = 0; i < vector_string.size(); ++i)
    {
        if(i != 0)
            ss << "|";
        ss << vector_string[i];
    }
    std::string result = ss.str();
    result=" |"+result+"| ";

    return result;
}

//Return the seperate line
const std::string get_seperate_line(size_t width){


    std::string result=" "+SEPERATE_UNIT;

    for(int i=0;i<width;++i){
        result+=SEPERATE_UNIT;
    }
    result+=SEPERATE_UNIT_END;

    return result;

}

//Check the input syntax, and whether is exceed the range
bool move_sytax_check(const std::string& movement,player_board& a_board) {

    //Guarantee the given string size is 5
    if(movement.size()!=5){
        //   std::cout<<"I am in size";
        return  false;
    }


    //Check the type of five characters in the input
    if(!check_format_match(movement)){
        // std::cout<<"I am in format";
        return  false;
    }

    //Check whether the input movement is fitting the board range
    if(!check_range(movement,a_board)){
        //std::cout<<"I am in range\n";
        return false;
    }
    //  std::cout<<"I am in THE END\n";
    return true;
}

//Check whether the movement exceeds the board range
bool check_range(const std::string &movement,player_board& a_board) {
    if(!check_column_range(movement,a_board)){
        //  std::cout<<"I am in column\n";
        return false;
    }
    if(!check_row_range(movement,a_board)){
        //   std::cout<<"I am in row\n";
        return false;
    }
    return true;
}

//Check whether the given two column index are in valid range.
//It protentially excludes the possibility of moving the pawn out of the range
bool check_column_range(const std::string &movement,player_board& a_board) {


    char first_char =movement.at(0);
    char second_char=movement.at(1);
    char third_char =movement.at(2);
    char forth_char =movement.at(3);
    char fifth_char =movement.at(4);

    size_t board_width=a_board.playerA_board.at(0).size()-2;//Retrieve the original board width

    int column_index_before=column_index_2_integer(first_char);
    int column_index_after=column_index_2_integer(forth_char);

    //If the given column index is not valid
    if((column_index_before==(-1))||(column_index_after==(-1))){
        return false;
    }

    if(column_index_before>=1&&column_index_before<=board_width){
        if((column_index_after>=1&&column_index_after<=board_width)){
            return true;
        }
    }

    return false;
}

//Check whether the given two row index are in valid range.
//It protentially excludes the possibility of moving the pawn out of the range
bool check_row_range(const std::string &movement,player_board& a_board) {

    bool result= false;

    char first_char =movement.at(0);
    char second_char=movement.at(1);
    char third_char =movement.at(2);
    char forth_char =movement.at(3);
    char fifth_char =movement.at(4);

    size_t board_height=a_board.playerA_board.size();





    int row_index_before=row_index_2_integer(second_char);
    int row_index_after =row_index_2_integer(fifth_char);


    if(row_index_before>=1&&row_index_before<=board_height){
        if((row_index_after>=1&&row_index_after<=board_height)){
            result= true;
        }
    }

    return result;
}

//Check whether the input match the format syntax
bool check_format_match(const std::string& movement) {

    //bool result=true;

    char first_char =movement.at(0);
    char second_char=movement.at(1);
    char third_char =movement.at(2);
    char forth_char =movement.at(3);
    char fifth_char =movement.at(4);

    //Guarantee the first character is a alphabetic
    // Ref:http://www.cplusplus.com/reference/cctype/isalpha/
    if(!isalpha(first_char)){
        return false;
    }

    //Guarantee the second character is a number
    // Ref: http://www.cplusplus.com/reference/cctype/isdigit/
    if(!isdigit(second_char)){
        return false;
    }

    if(!(third_char=='-')){
        return false;
    }

    //Guarantee the forth character is a alphabetic
    if(!isalpha(forth_char)){
        return false;
    }

    //Guarantee the fifth character is a number
    if(!isdigit(fifth_char)){
        return false;
    }

    return true;
}

//Map column index from alphabetic to numeric,
// if if exceed max range, which is 8, return -1 to indicate error
// The initial index starts from 1
int column_index_2_integer(const char &alp_index) {
    int result = -1;
    switch (alp_index) {
        case 'A':
        case 'a':
            result = 1;
            break;
        case 'B':
        case 'b':
            result = 2;
            break;
        case 'C':
        case 'c':
            result = 3;
            break;
        case 'D':
        case 'd':
            result = 4;
            break;
        case 'E':
        case 'e':
            result = 5;
            break;
        case 'F':
        case 'f':
            result = 6;
            break;
        case 'G':
        case 'g':
            result = 7;
            break;
        case 'H':
        case 'h':
            result = 8;
            break;
    }

    return result;
}

//Translate the row index from char to int
//Ref: http://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int
int row_index_2_integer(const char &row_index_char){
    int row_index_int =(int)row_index_char-48;
    return  row_index_int;
}

// HELPER FUNCTION FOR check_original_pawn_exist
bool is_original_pawn_exist(size_t row_index, size_t column_index, size_t player_index,player_board& a_board) {

    bool result= false;
    if(player_index==PLAYER_A_){
        if( a_board.playerA_board.at(row_index).at(column_index)==1){
            result=true;
        }
    }

    if(player_index==PLAYER_B_){
        if( a_board.playerB_board.at(row_index).at(column_index)==1){
            result=true;
        }
    }

    return result;
}

//Get the 2*3 board situation for the coresponding player
//ASSUMPTION: the player_index is either PLAYER_B_ or PLAYER_A_
const board get_current_2_3_board(const posn center_pawn, const size_t player_index, player_board& a_board){


    size_t target_adjacent_column_index1=center_pawn.column_index-1;
    size_t target_adjacent_column_index2=center_pawn.column_index;
    size_t target_adjacent_column_index3=center_pawn.column_index+1;

    board curt_2_3_board=get_two_three_vector();

    //Get the situation for player B
    if(player_index==PLAYER_B_){
        //Get the three adjancent points from the opponent board
        size_t target_adjacent_row_index = center_pawn.row_index - 1;
        //Retrieve the row index of player A as eneymy for B
        // size_t target_adjacent_row_index_in_container = map_row_index(target_adjacent_row_index);

        size_t target_adjacent_row_index_in_container = target_adjacent_row_index;

        curt_2_3_board[0][0] = a_board.playerA_board.at(target_adjacent_row_index_in_container).at(
                target_adjacent_column_index1);
        curt_2_3_board[0][1] = a_board.playerA_board.at(target_adjacent_row_index_in_container).at(
                target_adjacent_column_index2);
        curt_2_3_board[0][2] = a_board.playerA_board.at(target_adjacent_row_index_in_container).at(target_adjacent_column_index3);
    }
        //Get the situation for player A
    else {
        //Get the three adjancent points from the opponent board
        size_t target_adjacent_row_index = center_pawn.row_index + 1;

        //Retrieve the row index of player B as enermy for A
        size_t target_adjacent_row_index_in_container = target_adjacent_row_index;

        curt_2_3_board[0][0] = a_board.playerB_board.at(target_adjacent_row_index_in_container).at(
                target_adjacent_column_index3);
        curt_2_3_board[0][1] = a_board.playerB_board.at(target_adjacent_row_index_in_container).at(
                target_adjacent_column_index2);
        curt_2_3_board[0][2] = a_board.playerB_board.at(target_adjacent_row_index_in_container).at(
                 target_adjacent_column_index1);
    }
    return curt_2_3_board;
}

//Map displayed row index to matrix index
size_t displayed_row_index_2_matrix(char& aChar, player_board& a_board) {
    size_t displayed_index_in_int=row_index_2_integer(aChar);
    return (a_board.playerA_board.size()-displayed_index_in_int);
}

//Return the matched case id
const resultCase get_result_case_id(const board& board_, size_t player_index,player_board& a_board){
    posn start{1,1};
    posn end  {1,1};
    return  get_result_case(board_,start,end,player_index,a_board);
}

//Return the "resultCase" that contains:
//  1. Case index
//  2. start -> end direction (by boolean variable: front, left, right)
//Basic idea, is to judge by the surrounding oppenent's pawns and own pawns
const resultCase get_result_case(const board& board_, const posn start, const posn end,size_t player_index,player_board& a_board) {

    size_t start_row_index=start.row_index;
    size_t start_column_index=start.column_index;

    size_t end_row_index=end.row_index;
    size_t end_column_index=end.column_index;
    resultCase result;

    //Case 1
    if(board_== get_case(1)){
        result.index=1;//Assign the case index
        if(!exist_own_pawn(end,player_index,a_board)){
           // std::cout<<"I am in exist_own_pawn \n";
           //if(start_row_index==(end_row_index+1) match_expected_row(start_row_index,end_row_index,player_index)){
                if(match_expected_row(start_row_index,end_row_index,player_index)){
               // std::cout<<"I am in start_row_index \n";
                if(end_column_index==start_column_index){
                    {
                       // std::cout<<"I am in end_column_index \n";
                        result.front=true;
                    }
                }
            }
        }
    }
        //Case 2
    else if(board_== get_case(2)){
        result.index=2;

        if(!exist_own_pawn(end,player_index,a_board)) {
           // if (start_row_index == (end_row_index + 1)) {
                if(match_expected_row(start_row_index,end_row_index,player_index)){
                if (end_column_index == start_column_index) {
                    //result.index=2;
                    result.front = true;
               // } else if ((end_column_index + 1) == start_column_index) {
                } else if (match_expected_left_column(start_column_index,end_column_index,player_index)) {
                    //result.index=2;
                    result.left = true;
                }
            }
        }
    }
        //Case 3
    else if(board_== get_case(3)){
        result.index=3;
        if(!exist_own_pawn(end,player_index,a_board)) {
            //if (start_row_index == (end_row_index + 1)) {
            if(match_expected_row(start_row_index,end_row_index,player_index)){
                if (end_column_index == start_column_index) {
                    //result.index=3;
                    result.front = true;
              //  } else if ((end_column_index - 1) == start_column_index) {
                } else if (match_expected_right_column(start_column_index,end_column_index,player_index)) {
                    //result.index=3;
                    result.right = true;
                }
            }
        }
    }
//Case 4
    else if(board_== get_case(4)){
        result.index=4;
        //if(ctr_orgn_row_idx==(moved_row_index+1)){

        //  }
    }
//Case 5
    else if(board_== get_case(5)){
        result.index=5;
        if(!exist_own_pawn(end,player_index,a_board)) {
           // if (start_row_index == (end_row_index + 1)) {
                if(match_expected_row(start_row_index,end_row_index,player_index)){
                //if ((end_column_index + 1) == start_column_index) {
                    if(match_expected_left_column(start_column_index,end_column_index,player_index)){
                    //result.index=5;
                    result.left = true;
                }
            }
        }
    }
//Case 6
    else if(board_== get_case(6)){
        result.index=6;

        if(!exist_own_pawn(end,player_index,a_board)) {
            //if (start_row_index == (end_row_index + 1)) {
                if(match_expected_row(start_row_index,end_row_index,player_index)){
               // if ((end_column_index + 1) == start_column_index) {
                    if ( match_expected_left_column(start_column_index,end_column_index,player_index)) {
                    // result.index=6;
                    result.left = true;
                } else if (end_column_index == start_column_index) {
                    // result.index=6;
                    result.front = true;

             //   } else if ((end_column_index - 1) == start_column_index) {
                    } else if ( match_expected_right_column(start_column_index,end_column_index,player_index)) {
                    // result.index=6;
                    result.right = true;
                }
            }
        }
    }
//Case 7
    else if(board_== get_case(7)){
        result.index=7;
        if(!exist_own_pawn(end,player_index,a_board)) {
          //  if (start_row_index == (end_row_index + 1)) {
                if(match_expected_row(start_row_index,end_row_index,player_index)){
                if (match_expected_right_column(start_column_index,end_column_index,player_index)) {
                    //result.index=7;
                    result.right = true;
                }
            }
        }
    }
//Case 8
    else if(board_== get_case(8)){
        result.index=8;
        if(!exist_own_pawn(end,player_index,a_board)) {
            //if (start_row_index == (end_row_index + 1)) {
            if(match_expected_row(start_row_index,end_row_index,player_index)){
                // if ((end_column_index + 1) == start_column_index) {
                if ( match_expected_left_column(start_column_index,end_column_index,player_index)) {
                    // result.index=6;
                    result.left = true;
                } else if ( match_expected_right_column(start_column_index,end_column_index,player_index)) {
                    // result.index=6;
                    result.right = true;
                }
            }
        }

    }

    return  result;
}

//Check whether the end column matches expect "ideal" left movement column value
bool match_expected_left_column(size_t start_column_index, size_t end_column_index, size_t player_index) {
    if(player_index==PLAYER_B_){
        if(start_column_index==(end_column_index+1)){
            return true;
        }
    }
    else if(player_index==PLAYER_A_){
        if(start_column_index==(end_column_index-1)){
            return true;
        }
    }
    return false;
}

//Check whether the end column matches expect "ideal" right movement column value
bool match_expected_right_column(size_t start_column_index, size_t end_column_index, size_t player_index) {
    if(player_index==PLAYER_B_){
        if(start_column_index==(end_column_index-1)){
            return true;
        }
    }
    else if(player_index==PLAYER_A_){
        if(start_column_index==(end_column_index+1)){
            return true;
        }
    }
    return false;
}

//Check whether the row of end movement fits the projected value of the start position
//ASSUMPTION: player_index is either PLAYER_B_ or PLAYER_A_
bool match_expected_row(size_t start_row_index, size_t end_row_index, size_t player_index) {
    if(player_index==PLAYER_B_){
        if(start_row_index==(end_row_index+1)){
            return true;
        }
    }
    else if(player_index==PLAYER_A_){
        if(start_row_index==(end_row_index-1)){
            return true;
        }
    }
    return false;
}

//Check whether  the end position of the pawn is occupied by own side pawn
bool exist_own_pawn(const posn position, size_t player_index, player_board& a_board) {
    bool result = false;
    if(player_index==PLAYER_B_){
        if( a_board.playerB_board.at(position.row_index).at(position.column_index)==1){
            result= true;
        }
    }
    else if(player_index==PLAYER_A_){
        if( a_board.playerA_board.at(position.row_index).at(position.column_index)==1){
            result= true;
        }
    }
    return result;
}

//Get the pair of posns that contains start point and end point
lop get_lop(const std::string & input,player_board& a_board) {


    char first_char =input.at(0);//a
    char second_char=input.at(1);//1
    //  char third_char =input.at(2);//-
    char forth_char =input.at(3);//a
    char fifth_char =input.at(4);//2


    size_t start_row_index;
    size_t start_column_index;

    size_t end_row_index;
    size_t end_column_index;

    //Start from 1, is not consistent with the "board" index, minus 1 is required
    start_row_index     = displayed_row_index_2_matrix(second_char,a_board);
    end_row_index       = displayed_row_index_2_matrix(fifth_char,a_board);

    //Start from 1, is consistent with the "board" index
    start_column_index  = column_index_2_integer(first_char);
    end_column_index    = column_index_2_integer(forth_char);



    posn start{start_row_index,start_column_index};
    posn end{end_row_index,end_column_index};

    lop pair{start,end};

    return pair;
}

//Check whether the player A movement is valid
resultCase check_playerA_movement(const std::string &movement, size_t player_index,player_board& a_board) {

    lop pair =get_lop(movement,a_board);

   // std::cout<<"pair: (" << pair.start_posn.row_index<< ","<< pair.start_posn.column_index<<")" <<'\n';
   // std::cout<<"pair: (" << pair.end_posn.row_index<< ","<< pair.end_posn.column_index<<")" <<'\n';

    posn center_pawn =pair.start_posn;

    //Get the 2*3 board where the center_pawn is center
    board curt_2_3_board=get_current_2_3_board(center_pawn,player_index,a_board);

    //TEST
   // std::cout<<"play A's current 2 3 board"<<'\n';
   // print_board(curt_2_3_board);

    //Get the corresponding case of the given 2*3 board
    resultCase result =get_result_case(curt_2_3_board,pair.start_posn,pair.end_posn,player_index,a_board);

    return  result;
}

//Check whether the player B movement is valid
resultCase check_playerB_movement(const std::string &movement, size_t player_index,player_board& a_board) {

    lop pair =get_lop(movement,a_board);

//    std::cout<<"pair: (" << pair.start_posn.row_index<< ","<< pair.start_posn.column_index<<")" <<'\n';
//    std::cout<<"pair: (" << pair.end_posn.row_index<< ","<< pair.end_posn.column_index<<")" <<'\n';

    posn center_pawn =pair.start_posn;

    //Get the 2*3 board where the center_pawn is center
    board curt_2_3_board=get_current_2_3_board(center_pawn,player_index,a_board);

    //TEST
  //  print_board(curt_2_3_board);

    //Get the corresponding case of the given 2*3 board
    resultCase result =get_result_case(curt_2_3_board,pair.start_posn,pair.end_posn,player_index,a_board);

    //TEST
  //  print_result_case(result);

    return  result;

}

//Check whether the start pawn exist
bool check_original_pawn_exist(const std::string &movement, size_t player_index,player_board& a_board) {

    lop input=get_lop(movement,a_board);

    //Check the pawn in original/start position is existed.
    bool original_pawn_exist=is_original_pawn_exist(input.start_posn.row_index,input.start_posn.column_index, player_index,a_board);

    return original_pawn_exist;
}

//Check the validation of the movement.
//  1. If the start pown is not exist, return default resultCase, that has index -1
//  2. Otherwise, return corresponding case of the given player
resultCase verify_movement(const std::string& movement, size_t player_index,player_board& a_board) {

    //To ensure the original pawn is existed
    if(!check_original_pawn_exist(movement,player_index,a_board)){
     //   std::cout<<player_index<<" "<<"I am in check_original_pawn_exist\n";
        resultCase result;//The default value of index in result is -1
        return result;
    }

    //Ensure the pawn movement is valid
    if(player_index==PLAYER_A_){
     //   std::cout<<"I am in PlayerA\n";
        return  check_playerA_movement( movement,  player_index,a_board);

    }

    if(player_index==PLAYER_B_){
       // std::cout<<"I am in PlayerB\n";
        return  check_playerB_movement( movement,  player_index,a_board);
    }

}

//Check whether the opponent reach the end of hte board
//  Basic idea is to check whether the player B reach the first row, player A reach the last row respectively
bool is_opponent_reach_end(const size_t player_index, player_board& a_board) {
    bool result =false;
    size_t max_row_index=a_board.playerA_board.size()-1;

    //If the player B reaches the player A side (where the row index is 0), player B wins
    if(player_index==PLAYER_A_){
        for(size_t element : a_board.playerB_board.at(0)){
            if(element==1){
                result=true;
            }
        }
    }
    //If the player A reaches the player B side (where the row index is max_row_index), player B wins
    if(player_index==PLAYER_B_){
        for(size_t element : a_board.playerA_board.at(max_row_index)){
            if(element==1){
                result=true;
            }
        }
    }

    return result;
}

//Check whether the pawns of the given player all captured by the opponent
bool is_all_pawns_captured(const size_t player_index,player_board& a_board) {
    //  bool result=true;
    board player_board=get_player_board(player_index,a_board);

    size_t max_column_index=a_board.playerB_board.at(0).size()-1;//but not reachable

    for(auto row : player_board){
        for(int i=1;i<max_column_index;++i){
            if(row.at(i)==1){
                return false;
            }
        }
    }

    return true;
}

//Check whether the pawns of the given player all blocked by the opponent
bool is_all_pawns_blocked(const size_t player_index,player_board& a_board) {
    board player_board=get_player_board(player_index,a_board);

    //TEST
//  std::cout<<"Player "<<player_index<< "board \n";
 // print_board(player_board);

    size_t max_column_index=player_board.at(0).size()-1;//But not reachable

    for(size_t i=0;i< player_board.size();++i){
        for(size_t j=1;j<max_column_index;++j){
            //Where [i][j] position has pawn
            if(player_board.at(i).at(j)==1){
                posn center_pawn{i,j};

                auto board=get_current_2_3_board(center_pawn,player_index,a_board);

                //TEST
               //  std::cout<<i<<j<<"this is test in is_all_pawns_blocked \n";
              //  print_board(board);

              //  get_result_case(const board& board_, const posn start, const posn end,size_t player_index,player_board& a_board)

               // auto return_case= get_result_case(board,)


                auto returned_case=get_result_case_id(board,player_index,a_board);
                //If one pawn is not block, then the player is still movable
                if(is_not_blocked(returned_case, center_pawn,player_index,a_board)){
                    return false;
                }
            }
        }
    }
    return true;
}

//Check whether the pawn is blocked(no other valid movement)
//  As long as one case is neither case 4 or case 8, it still has valid movemnt(assure no current player side pawn is no the way
bool is_not_blocked(resultCase aCase, posn center_pawn,const size_t player_index,player_board& a_board) {
     int case_id=aCase.index;

     board playA_bd =a_board.playerA_board;
     board playB_bd =a_board.playerB_board;

    if(case_id==4){
        return false;
    }

    //Actual this check is redudant, but here is applied to ensure the correctness
    if(case_id==1){
        if(player_index==PLAYER_A_){
            int row_index=center_pawn.row_index+1;
            int column_index=center_pawn.column_index;

            //std::cout<<row_index<<column_index;

            if(playA_bd.at(row_index).at(column_index)==0){
                return true;
            }
        }
        else if(player_index==PLAYER_B_){
            int row_index=center_pawn.row_index-1;
            int column_index=center_pawn.column_index;
            if(playB_bd.at(row_index).at(column_index)==0){
                return true;
            }
        }
    }

    if(case_id==2||case_id==3||case_id==5||case_id==6||case_id==7||case_id==8){
        return true;
    }
        return false;

}

//Return the coresponding board to the given index
//ASSUMPTION: the player_index should be either PLAYER_A_ or PLAYER_B_
const board get_player_board(const size_t player_index, const player_board& a_board) {
    if(player_index==PLAYER_A_){
        return a_board.playerA_board;
    }
    else{
        return a_board.playerB_board;
    }
}

//The game is ending either:
//  1. The pawn reaches opponent's home row;
//  2. All opponent's pawns are captured;
//  3. All opponent's pawns are blocked.
bool should_game_end(const size_t player_index,player_board& a_board) {
    bool result= false;

    //1. Check whether the opponent reaches the end
    if(is_opponent_reach_end(player_index,a_board)){
     //   std::cout<<"I am in is_opponent_reach_end \n ";
        return true; //It should terminate immediately, if the pawn reachs end, other wise it will cause index out of range
    }

    //2. Check whether all pawns of given player are captured
    if(is_all_pawns_captured(player_index,a_board)){
        //std::cout<<"I am in is_all_pawns_captured \n ";
        return true;
    }

    //3. Check whether all pawns of given player are blocked
   if(is_all_pawns_blocked(player_index,a_board)){
      //  std::cout<<"I am in is_all_pawns_blocked \n ";
        return true;
    }

    return false;
}

//Update board based on player's movement
void update_board(const std::string& movement, const size_t player_index,const resultCase result,player_board& a_board) {
    lop pair= get_lop(movement,a_board);


    if(player_index==PLAYER_A_){
        //Not capture action, solo moving
        if(result.front==true){
            a_board. playerA_board.at(pair.end_posn.row_index).at(pair.end_posn.column_index)=1;
            a_board.playerA_board.at(pair.start_posn.row_index).at(pair.start_posn.column_index)=0;
        }

        //Capture action with moving
        if(result.left==true||result.right==true){
            //The pawn in end position from Player A is captured
            a_board.playerB_board.at(pair.end_posn.row_index).at(pair.end_posn.column_index)=0;

            //Moving the panw in playerB
            a_board.playerA_board.at(pair.end_posn.row_index).at(pair.end_posn.column_index)=1;
            a_board.playerA_board.at(pair.start_posn.row_index).at(pair.start_posn.column_index)=0;
        }

    }


    if(player_index==PLAYER_B_){
        //Not capture action, solo moving
        if(result.front==true){
            a_board.playerB_board.at(pair.end_posn.row_index).at(pair.end_posn.column_index)=1;
            a_board.playerB_board.at(pair.start_posn.row_index).at(pair.start_posn.column_index)=0;
        }

        //Capture action with moving
        if(result.left==true||result.right==true){
            //The pawn in end position from Player A is captured
            a_board.playerA_board.at(pair.end_posn.row_index).at(pair.end_posn.column_index)=0;

            //Moving the panw in playerB
            a_board.playerB_board.at(pair.end_posn.row_index).at(pair.end_posn.column_index)=1;
            a_board.playerB_board.at(pair.start_posn.row_index).at(pair.start_posn.column_index)=0;
        }

    }

}

//Check whether the entered input is digit
int is_entered_digit(std::string& input) {

    int result = -1;
    if (input.size() == 1) {
        char temp = input.at(0);
        int row_index_int = (int) temp - 48;
        if (row_index_int >= 3) {
            if (row_index_int <= 8) {
                result =row_index_int;
            }
        }
    }

    return result;
}

//Print the "board"
void print_board(board a_board){
    for(int i=0;i<a_board.size();++i){
        for(int j=0;j<a_board.at(0).size();++j){
            std::cout<<a_board.at(i).at(j)<<" ";
        }
        std::cout<<'\n';
    }
}

//Print the result case
void print_result_case(resultCase a_case){

        std::cout<<"( "<<a_case.index<<" , "  <<(bool)a_case.front<<" , "  <<(bool)a_case.left<<" , "<<
                                                                                                     (bool) a_case.right<<" ) " <<   '\n';
      //       a_case.front=true;
  //  std::cout<<"front: "<< a_case.front<<" and ture is :"<< true<<   '\n';
}

