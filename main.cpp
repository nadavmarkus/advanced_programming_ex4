#include <string>
#include <utility>
#include <iostream>

#include "ex4_header.h"
#include "unit_test_util.h"

using std::string;
using std::get;

static bool test1(){
	GameBoard<12, 7, string, 4> board;
	int i = 0;
	for (int row = 0; row < 12; row++){
		for(int col =0; col < 7; col++){
			board.setPiece(row, col, "Piece", i);
			i = (i+1)%4;
		}
	}
	int occurence[4]= {0,0,0,0};
	for(auto pieceInfo : board){
		occurence[get<3>(pieceInfo)]++;
	}
	for(int i = 0;i<4;i++){
		if (occurence[i] != 21){
			return false;
		}
	}
	return true;
}

int main(){
	RUN_TEST(test1);
    
    GameBoard<3,3, char> gameboard;
    gameboard.setPiece(0,0, 'A', 1);
    
    gameboard.setPiece(2,0, 'A', 2);
    
    gameboard.setPiece(0,1, 'C', 2);
    
    gameboard.setPiece(2,2, 'D', 2);
    
    for (auto element: gameboard) {
        std::cout << std::get<0>(element) << "," << std::get<1>(element) << ": " << std::get<2>(element) << "-" << std::get<3>(element) << std::endl;
    }
    std::cout << std::endl;
    
    for (auto element: gameboard.allPiecesOfPlayer(2)) {
        std::cout << std::get<0>(element) << "," << std::get<1>(element) << ": " << std::get<2>(element) << "-" << std::get<3>(element) << std::endl;
    }
    
    std::cout << "Searching by piece" << std::endl;
    for (auto element: gameboard.allOccureneceOfPiece('A')) {
        std::cout << std::get<0>(element) << "," << std::get<1>(element) << ": " << std::get<2>(element) << "-" << std::get<3>(element) << std::endl;
    }
    
    std::cout << "Searching by piece and player" << std::endl;
    for (auto element: gameboard.allOccureneceOfPieceForPlayer('C', 2)) {
        std::cout << std::get<0>(element) << "," << std::get<1>(element) << ": " << std::get<2>(element) << "-" << std::get<3>(element) << std::endl;
    }
    
	return 0;
}
