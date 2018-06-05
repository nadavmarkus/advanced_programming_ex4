#include <iostream>
#include <tuple>

#include "GameBoard.h"

int main()
{
    GameBoard<3,3, char> gameboard;
    gameboard.setPiece(0,0, 'A', 1);
    
    int i = 0;
    for (auto it: gameboard) {
        std::cout << i << ":" << it << " ";
        ++i;
        
        if (i % 3 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}