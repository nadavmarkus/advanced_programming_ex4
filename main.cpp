#include <iostream>
#include <tuple>

#include "GameBoard.h"

int main()
{
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
}