#ifndef __GAME_BOARD_H_
#define __GAME_BOARD_H_

#include <memory>
#include <tuple>

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template <int ROWS, int COLS, class GAME_PIECE, int PLAYER_COUNT = 2>
class GameBoard
{
private:
    using BoardPiece = std::pair<int, GAME_PIECE>;
    BoardPiece board[ROWS][COLS];
    
public:
    class iterator {
    friend class GameBoard;
    private:
        int cur_row;
        int cur_col;
        const GameBoard &board;
        iterator(int cur_row, int cur_col, const GameBoard &board): cur_row(cur_row),
                                                                    cur_col(cur_col),
                                                                    board(board) {}
    public:
        /* Prefix increment */
        iterator operator++() {
            cur_col = (cur_col + 1) % COLS;
            
            if (0 == cur_col) {
                cur_row = cur_row + 1;
            }
            
            return *this;
        }
        
        /* Postfix increment */
        iterator operator++(int junk) {
            (void) junk;
            iterator temp = *this;
            ++*this;
            return temp;
        }
        
        GAME_PIECE operator*() {
            return std::get<1>(board.board[cur_row][cur_col]);
        }
        
        bool operator==(const iterator &other) {
            return cur_row == other.cur_row && cur_col == other.cur_col && (&board == &other.board);
        }
        
        bool operator!=(const iterator &other) {
            return !(*this == other);
        }
    
    };
    
    iterator begin() {
        return iterator(0, 0, *this);
    }

    iterator end() {
        return iterator(ROWS, 0, *this);
    }

    PieceInfo<GAME_PIECE> getPiece(int row, int col)
    {
        return std::make_unique<BoardPiece>(board[row][col]);
    }
    
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player)
    {
        BoardPiece previous = board[row][col];
        board[row][col] = BoardPiece(player, piece);
        return std::make_unique<BoardPiece>(previous);
    }
};

#endif