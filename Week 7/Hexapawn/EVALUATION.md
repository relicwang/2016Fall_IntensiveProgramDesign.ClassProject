
# IPD Homework 7: Hexapawn Submission Summary by Relic

  

## Summary

In this assignment an interactive two-player abstract strategy game (as Hexapawn) was implemented.
The main executable file is "hexapawn_main.cpp"


## Basic Strategy

The overall game situation could be decomposed into 8 simple cases as following:

Case 1:  
+---+---+---+               Possible movemnet: [front/up]
|   |   |   | 
+---+---+---+      
|   | A |   |
+---+---+---+

Case 2:   
+---+---+---+               Possible movemnet: [front, left]   
| B |   |   |  
+---+---+---+
|   | A |   |
+---+---+---+

Case 3:  
+---+---+---+               Possible movemnet: [front, right]   
|   |   | B | 
+---+---+---+
|   | A |   |
+---+---+---+

Case 4:  
+---+---+---+               Possible movemnet: []   
|   | B |   | 
+---+---+---+
|   | A |   |
+---+---+---+

Case 5:  
+---+---+---+              Possible movemnet: [left]   
| B | B |   | 
+---+---+---+
|   | A |   |
+---+---+---+

Case 6:   
+---+---+---+              Possible movemnet: [left,up,right]   
| B |   | B | 
+---+---+---+
|   | A |   |
+---+---+---+

Case 7:  
+---+---+---+               Possible movemnet: [right]        
|   | B | B | 
+---+---+---+
|   | A |   |
+---+---+---+
 
Case 8:  
+---+---+---+               Possible movemnet: [left, right]  
| B | B | B | 
+---+---+---+
|   | A |   |
+---+---+---+
 
And the above cases are the core idea to implement the game.

Also, the following steps are considered during the development, and are supposed to be appeared in test cases:
  1. Whether user entered input is valid;
  2. If input syntax is correct, is the movemnet valid?;
  3. If the movement is valid, the board and re-displayed update is expected to be executed;
  4. A simple strategy should be applied to judege whehter the game should be terminated, under situation either:
       a. All pawns are captured by the opponent;
       b. All pawns are blocked by the opponent;
       c. The opponent's pawn arrive the opposite home row.
  5. To allow the game back-and-forth, a simple finite state machine strategy is applied.
  
## Testing
   The testing is mainly based on following funtions: (due to the time constrain, 
   the majority core functions have been tested). And testing mainly designed based on the conditions reflected in each functions.

    //Check whether the movement is valid, the invalid contains either:
    //  1. There is no existance case matched, where the case index is -1
    //  2. The case matched the current "board", but the movement might still not be allowed,
    //     when "left" "right" "front" are all false. That includes the case 4.
    bool get_bool(resultCase aCase);

    //Initialize the hexapawn board
    board initialize_board(size_t height, size_t width,size_t player_index);

    //Print player's board according to index
    void print_board(const board& playerA_board, const board& playerB_board,size_t player_index);

    //Ensure the consistency between two players' board
    void board_valid_check(const board& playA, const board& playB);

    //Get row for the whole playing board
    const std::string get_row(const board& playA, const board& playB, size_t index);

    //Get the index row
    const std::string get_index_row(size_t width);

    //Add the seperator for each spawn
    const std::string add_seperator(const std::vector<std::string>& vector_string);

    //Return the seperate line
    const std::string get_seperate_line(size_t width);

    //Check the input syntax, and whether is exceed the range
    bool move_sytax_check(const std::string& movement,player_board& a_board);

    //Check the validation of the movement.
    //  1. If the start pown is not exist, return default resultCase, that has index -1
    //  2. Otherwise, return corresponding case of the given player
    resultCase verify_movement(const std::string& movement, size_t player_index,player_board& a_board);

    //Map column index from alphabetic to numeric,
    // if if exceed max range, which is 8, return -1 to indicate error
    // The initial index starts from 1
    int column_index_2_integer(const char &alp_index);

    //Translate the row index from char to int
    //Ref: http://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int
    int row_index_2_integer(const char &row_index_char);

    //Check whether the input match the format syntax
    bool check_format_match(const std::string& movement);

    //Check whether the movement exceeds the board range
    bool check_range(const std::string &movement,player_board& a_board);

    //Check whether the given two column index are in valid range.
    //It protentially excludes the possibility of moving the pawn out of the range
    bool check_column_range(const std::string &movement,player_board& a_board);

    //Check whether the given two row index are in valid range.
    //It protentially excludes the possibility of moving the pawn out of the range
    bool check_row_range(const std::string &movement,player_board& a_board);

    //Check whether the opponent reach the end of hte board
    //  Basic idea is to check whether the player B reach the first row, player A reach the last row respectively
    bool is_opponent_reach_end(const size_t player_index,player_board& a_board);

    // HELPER FUNCTION FOR check_original_pawn_exist
    bool is_original_pawn_exist(size_t row_index, size_t column_index, size_t player_index,player_board& a_board);

    //Check whether the player A movement is valid
    resultCase check_playerA_movement(const std::string &movement, size_t player_index,player_board& a_board);

    //Check whether the player B movement is valid
    resultCase check_playerB_movement(const std::string &movement, size_t player_index,player_board& a_board);

    //Check whether the start pawn exist
    bool check_original_pawn_exist(const std::string &movement, size_t player_index,player_board& a_board) ;

    //The game is ending either:
    //  1. The pawn reaches opponent's home row;
    //  2. All opponent's pawns are captured;
    //  3. All opponent's pawns are blocked.
    bool should_game_end(const size_t player_index,player_board& a_board);

    //Check whether the pawns of the given player all captured by the opponent
    bool is_all_pawns_captured(const size_t player_index,player_board& a_board);

    //Check whether the pawns of the given player all blocked by the opponent
    bool is_all_pawns_blocked(const size_t player_index,player_board& a_board);

    //Return the coresponding board to the given index
    //ASSUMPTION: the player_index should be either PLAYER_A_ or PLAYER_B_
    const board get_player_board(const size_t player_index,const player_board& a_board);

    //Get the 2*3 board situation for the coresponding player
    //ASSUMPTION: the player_index is either PLAYER_B_ or PLAYER_A_
    const board get_current_2_3_board(const posn center_pawn, const size_t player_index,player_board& a_board);

    //Return the "resultCase" that contains:
    //  1. Case index
    //  2. start -> end direction (by boolean variable: front, left, right)
    //Basic idea, is to judge by the surrounding oppenent's pawns and own pawns
    const resultCase get_result_case(const board& board_, const posn start, const posn end,size_t player_index,player_board& a_board);

    //Return the matched case id
    const resultCase get_result_case_id(const board& board_,size_t player_index,player_board& a_board);

    //Check whether the pawn is blocked(no other valid movement)
    //  As long as one case is neither case 4 or case 8, it still has valid movemnt(assure no current player side pawn is no the way
    bool is_not_blocked(resultCase aCase, posn center_pawn,const size_t player_index,player_board& a_board);

    //Update board based on player's movement
    void update_board(const std::string& movement, const size_t player_index,const resultCase result,player_board& a_board);

    //Get the pair of posns that contains start point and end point
    lop get_lop(const std::string & input,player_board& a_board) ;

    //Map displayed row index to matrix index
    size_t displayed_row_index_2_matrix(char& aChar,player_board& a_board);

    //Map the matrix row index to displayed format
    size_t matrix_row_index_2_displayed(size_t height, size_t index);

    //Check whether  the end position of the pawn is occupied by own side pawn
    bool exist_own_pawn(const posn position, size_t player_index,player_board& a_board);

    //Check whether the row of end movement fits the projected value of the start position
    //ASSUMPTION: player_index is either PLAYER_B_ or PLAYER_A_
    bool match_expected_row(size_t start_row_index, size_t end_row_index, size_t player_index);

    //Check whether the end column matches expect "ideal" left movement column value
    bool match_expected_left_column(size_t start_column_index, size_t end_column_index, size_t player_index);

    //Check whether the end column matches expect "ideal" right movement column value
    bool match_expected_right_column(size_t start_column_index, size_t end_column_index, size_t player_index);

    //Check whether the entered input is digit
    int is_entered_digit(std::string& input);
    

To give more intuitive view, the following presents an example for testing 
   TEST(get_result_case_without_interfer_by_own_pawn)   (line 604 -1017 in hexapawn).
   
    1. A sample 8*8 board were sketched to illustrated the 8 cases in both player A and player B;
       (Actually, they have more pawns then the acutal game should, here is only applied for testing purpose).
    2. Then a initial 8*8 board was instantiated, and we customize it based on graph;
    3. Manually pick up these pawns fits the cases drawed in the beginning;
    4. Inject above pawns to the get_result_case function to see whether the expect result is retrieved;
    5. Also, this graph is further extended to test these situtaion whether the moved position is already occupied by the own pawn.
    
    | a | b | c | d | e | f | g | h |
 ---+---+---+---+---+---+---+---+---+---
  8 | B | B | B | B | B | B | B | B | 8
 ---+---+---+---+---+---+---+---+---+---
  7 |   |   | W | W |   | W |   |   | 7
 ---+---+---+---+---+---+---+---+---+---
  6 | B |   | B |   | B |   |   |   | 6
 ---+---+---+---+---+---+---+---+---+---
  5 |   | W | W | W | W |   |   |   | 5
 ---+---+---+---+---+---+---+---+---+---
  4 |   |   | B | B |   | B | B | B | 4
 ---+---+---+---+---+---+---+---+---+---
  3 |   |   | W |   | W |   | W |   | 3
 ---+---+---+---+---+---+---+---+---+---
  2 |   |   | B |   | B | B |   |   | 2
 ---+---+---+---+---+---+---+---+---+---
  1 | W | W | W | W | W | W | W | W | 1
 ---+---+---+---+---+---+---+---+---+---
    | a | b | c | d | e | f | g | h |
    
    Graph 1: Displayed Board
    
    
    | a | b | c | d | e | f | g | h |
 ---+---+---+---+---+---+---+---+---+---
  8 | B | B | 5 | B | 6 | 4 | 3 | 1 | 8      A1,A3,A4,A5,A6
 ---+---+---+---+---+---+---+---+---+---
  7 |   |   | W | W |   | W |   |   | 7
 ---+---+---+---+---+---+---+---+---+---
  6 | 2 |   | 8 |   | 7 |   |   |   | 6      A2, A8, A7
 ---+---+---+---+---+---+---+---+---+---
  5 |   | W | W | W | W |   |   |   | 5
 ---+---+---+---+---+---+---+---+---+---  --------------------------
  4 |   |   | B | B |   | B | B | B | 4
 ---+---+---+---+---+---+---+---+---+---
  3 |   |   | 7 |   | 6 |   | 8 |   | 3      B6, B7, B8
 ---+---+---+---+---+---+---+---+---+---
  2 |   |   | B |   | B | B |   |   | 2
 ---+---+---+---+---+---+---+---+---+---
  1 | 1 | 3 | 4 | W | W | 5 | 2 | W | 1      B1, B3, B4, B4, B2
 ---+---+---+---+---+---+---+---+---+---
    | a | b | c | d | e | f | g | h |
    
    Graph 2: The Board mared by cases 
    (it is identical to the Graph 1,  but some pawns that were replaced by case id)
  
  
 Similarly, all other testing cases are designed based on graphs/other sample cases dereivated from the conditions appeared in the functions. 
 
## Anything that surprised during the assignment.

  The debugging really take times, as well as writing good and adaquate test cases. Also, it is quite important to select a well representation to store the board.
  After struggling a long time, I start to revise my original data representation and have to revise all existing method to achieve the goal.