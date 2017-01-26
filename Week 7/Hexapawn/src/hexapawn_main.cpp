#include "hexapawn.h"
//#include "hexapawn.cpp"
#include<limits>

bool is_playerA= false;
bool is_playerB= true;
bool is_end=false;

bool is_playerA_name_entered= false;
bool is_playerB_name_entered= false;

std::string playerA_name;
std::string playerB_name;
std::string playerA_movement;
std::string playerB_movement;

size_t height;
size_t width;

int main()
{
    /** BOARD SET UP **/
    std::cout << "Welcome to Hexapawn!\n\n";
    std::cout << "Please enter the size of your board!\n";
    std::cout << "What's the height do you prefer (from 3 to 8)? \n";
    std::string temp_input;
    std::cin >> temp_input;

    while((height=is_entered_digit(temp_input))==-1){
        std::cout << "Umm... Please try a proper height \n";
        std::cin >> temp_input;
    }

    std::cout << "And what's the width do you prefer (from 3 to 8)? \n";
    std::cin >> temp_input;
    while((width=is_entered_digit(temp_input))==-1){
        std::cout << "Umm... Please try a proper width \n";
        std::cin >> temp_input;
    }

    std::cout << "We are all set! \n\n\n\n";

    player_board a_player_board;
    a_player_board.playerA_board=initialize_board(height,width,PLAYER_A_);
    a_player_board.playerB_board=initialize_board(height,width,PLAYER_B_);




     /** HANDLING USERS' ACTION **/
    while(!is_end){

       //Player A's turn
        if(is_playerA){
            print_board(a_player_board.playerA_board,a_player_board.playerB_board,PLAYER_A_);
          //Enure both player A and player B have identical size of board
            board_valid_check(a_player_board.playerA_board,a_player_board.playerB_board);

            is_playerA= false;
            is_playerB= true;

              //When the game satisfies the ending situation, the game should stop
               is_end=should_game_end(PLAYER_A_,a_player_board);

             if(is_end){
                  break;
               }

               bool is_correct_movement_syntax=false;
               bool is_valid_movement= false;

            if(!is_playerA_name_entered){
               std::cout << "\n\nWelcome to join BLACK of EVIL,warrior!\n";
               std::cout << "Please enter your name!\n";
               std::cin >>playerA_name;
                is_playerA_name_entered=true;
            }
               std::cout << "\n\nWelcome to "<<playerA_name<<"!"<<" Please select your movement :\n";
               std::cout <<"e.g. typing     a3-a2   to indicate moving the pawn from a3 to a2 \n ";

               std::cin>>playerA_movement;
               // std::cin >> first_name >> age;

               //Initilize a flag to ensure the correctness of entered movement syntax
               is_correct_movement_syntax=move_sytax_check(playerA_movement,a_player_board);

               //Initilize a flage to ensure the validness of entered movement
               resultCase result;
               is_valid_movement=get_bool(result);

               //The correctness of the input syntax will be the pre-condition for the validation of the movement.
               while ((!is_correct_movement_syntax) || (!is_valid_movement)) {
                   if (!is_correct_movement_syntax) {
                       std::cout << "The entered command syntax is invalid, please re-enter: \n";
                       std::cin >> playerA_movement;
                       is_correct_movement_syntax = move_sytax_check(playerA_movement,a_player_board);

                   }
                   else {
                       result = verify_movement(playerA_movement, PLAYER_A_,a_player_board);
                       is_valid_movement = get_bool(result);

                       if (!is_valid_movement) {
                           std::cout << "Sorry the movement is invalid, please re-enter: \n";
                           std::cin >> playerA_movement;
                           is_correct_movement_syntax = move_sytax_check(playerA_movement,a_player_board);
                           if(!is_correct_movement_syntax){is_valid_movement= false; }
                       }
                   }

               }


               update_board(playerA_movement,PLAYER_A_,result,a_player_board);

           //    print_board(a_player_board.playerA_board,a_player_board.playerB_board,PLAYER_A_);


        }

       //Player B's turn
        if(is_playerB){

            print_board(a_player_board.playerA_board,a_player_board.playerB_board,PLAYER_B_);

            //Enure both player A and player B have identical size of board
            board_valid_check(a_player_board.playerA_board,a_player_board.playerB_board);

            //Next turn is player A
            is_playerA= true;
            is_playerB= false;

            //When the game satisfies the ending situation, the game should stop
            is_end=should_game_end(PLAYER_B_,a_player_board);

            if(is_end){
                break;
            }

            bool is_correct_movement_syntax=false;
            bool is_valid_movement= false;

            if(!is_playerB_name_entered){
            std::cout << "\n\nWelcome to join WHITE of JUSTICE,warrior!\n";
            std::cout << "Please enter your name !\n";
            //Get playerB's name
            std::cin >>playerB_name;
                is_playerB_name_entered=true;
            }

            std::cout << "\nWelcome "<<playerB_name<<"!"<<" Please select your movement :\n";
            std::cout <<"(e.g. typing a1-a2 to move the pawn from a1 to a2) \n ";

            //Get playerB's mmovement
            std::cin>>playerB_movement;

            //Initilize a flag to ensure the correctness of entered movement syntax
            is_correct_movement_syntax=move_sytax_check(playerB_movement,a_player_board);

            //Initilize a flage to ensure the validness of entered movement
            resultCase result;
            is_valid_movement=get_bool(result);

            //The correctness of the input syntax will be the pre-condition for the validation of the movement.
            while ((!is_correct_movement_syntax) || (!is_valid_movement)) {
                if (!is_correct_movement_syntax) {
                    std::cout << "The entered command syntax is invalid, please re-enter: \n";
                    std::cin >> playerB_movement;
                    is_correct_movement_syntax = move_sytax_check(playerB_movement,a_player_board);

                }
                else {
                    result = verify_movement(playerB_movement, PLAYER_B_,a_player_board);
                    is_valid_movement = get_bool(result);

                    if (!is_valid_movement) {
                        std::cout << "Sorry the movement is invalid, please re-enter: \n";
                        std::cin >> playerB_movement;

                       // result = check_movement(playerB_movement, PLAYER_B_);
                      //  is_valid_movement = get_bool(result);

                        is_correct_movement_syntax = move_sytax_check(playerB_movement,a_player_board);
                        if(!is_correct_movement_syntax){is_valid_movement= false; }
                    }
                }

            }


            update_board(playerB_movement,PLAYER_B_,result,a_player_board);

          //  print_board(a_player_board.playerA_board,a_player_board.playerB_board,PLAYER_B_);
        }

    }


   if(is_playerA){
       std::cout<<"Player A BLACK of EVIL: "<<playerA_name<<" wins the game! Congratulation!!!";
   }
    if(is_playerB){
        std::cout<<"Player B WHITE of JUSTICE: "<<playerB_name<<" wins the game! Congratulation!!!";
    }

    std::getchar();
}













