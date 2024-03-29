
#include "headers/structs.h"
#include "headers/defs.h"
#include "headers/globals.h"
#include "headers/moves.h"
#include "headers/macros.h"
#include "headers/bll.h"
#include <string.h>
#include <stdio.h>
const char INPUT_PIECE_CHARS[6] = {'p','k','b','r','Q','K'};
const char X_CHARS[8] = {'a','b','c','d','e','f','g','h'};
const char Y_CHARS[8] = {'8','7','6','5','4','3','2','1'};

piece read_piece(){
     char p, x, y;
     piece ret;
     printf("Make your move: ");
     scanf("\n%c%c%c",&p,&x,&y);
     //printf("Received p: %c, x: %c, y: %c\n",p,x,y);
     for(int i = 0;i<NUM_PIECE_TYPES;i++){
          if(INPUT_PIECE_CHARS[i] == p){
               ret.type = i;
          }
     }
     for(int i = 0;i<BOARD_SIZE;i++){
          if(X_CHARS[i] == x){
               ret.x = i;
          }
     }
     for(int i = 0;i<BOARD_SIZE;i++){
          if(Y_CHARS[i] == y){
               ret.y = i;
          }
     }
     //printf("Moved to: %d, x: %d, y: %d\n",ret.type,ret.x,ret.y);
     
     return ret;
}

int human_move(board current){
     boardLinkedList *possibleMoves = getPossibleMovesFromBoard(current,COMPUTER_COLOR);
     if(possibleMoves->next == 0){
          freeBLL(possibleMoves);
          return 1;
     }
     while(true){ // repeat so players can retry if they make an illegal move
          boardLinkedList *head = possibleMoves;
          piece to_move = read_piece();
          if(to_move.x < 0 || to_move.x >= BOARD_SIZE || to_move.y < 0 || to_move.y >= 8 || to_move.type < 0 || to_move.type >= NUM_PIECE_TYPES || (GET_TYPE(current[to_move.y][to_move.x]) == to_move.type && GET_COLOR(current[to_move.y][to_move.x]) == HUMAN_COLOR)){
               printf("Error: illegal move - reading\n");
               continue;
          }
          while(head->next != 0){
               int piece_to_check = head->current[to_move.y][to_move.x];
               if(
                    GET_COLOR(piece_to_check) == COMPUTER_COLOR
                    &&
                    (
                         GET_TYPE(piece_to_check) == to_move.type 
                         || 
                         (GET_TYPE(piece_to_check) == PAWN && to_move.type == PAWN_M2) 
                         || 
                         (GET_TYPE(piece_to_check) == PAWN_M2 && to_move.type == PAWN) 
                         || 
                         (GET_TYPE(piece_to_check) == ROOK && to_move.type == U_ROOK) 
                         || 
                         (GET_TYPE(piece_to_check) == KING && to_move.type == U_KING)
                    )
               )
               {
                    memcpy(current,head->current,sizeof(board));
                    freeBLL(possibleMoves);
                    return 0;
               }else{
                    printf("%d %d %d\n",piece_to_check,GET_TYPE(piece_to_check), to_move.type);
               }
               head = head->next;
          }
          if(head->next == 0){
               printf("Error: illegal move - generating\n");
          }
     }
     freeBLL(possibleMoves);
     return 0;
}

