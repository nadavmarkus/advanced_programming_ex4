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
    
    struct BoardPiece {
    public:
        int player;
        std::unique_ptr<GAME_PIECE> piece;
    BoardPiece() : player(-1), piece(nullptr) {}
    BoardPiece(const BoardPiece &other): player(other.player),
                                         piece(nullptr == other.piece ? nullptr : std::make_unique<GAME_PIECE>(*other.piece)) {}
    BoardPiece(int player, const GAME_PIECE &piece): player(player), piece(std::make_unique<GAME_PIECE>(piece)) {}
    const BoardPiece& operator=(const BoardPiece& other)
    {
        if (this != &other) {
            player = other.player;
            if (nullptr != other.piece) {
                piece = std::make_unique<GAME_PIECE>(*other.piece);
            } else {
                piece = nullptr;
            }
        }
        
        return *this;
    }
    };
    
    BoardPiece board[ROWS][COLS];
    
public:
    typedef std::tuple<int, int, GAME_PIECE, int> iterated_value;
    class iterator {
    friend class GameBoard;
    private:
        int cur_row;
        int cur_col;
        const GameBoard &board;
        
        void getToNextPiece()
        {
            while (cur_row < ROWS && nullptr == board.board[cur_row][cur_col].piece) {
                cur_col = (cur_col + 1) % COLS;
                
                if (0 == cur_col) {
                    cur_row = cur_row + 1;
                }
            }
        }
        
        iterator(int cur_row, int cur_col, const GameBoard &board): cur_row(cur_row),
                                                                    cur_col(cur_col),
                                                                    board(board)
        {
            getToNextPiece();
        }
    public:
        /* Prefix increment */
        iterator operator++() {
            cur_col = (cur_col + 1) % COLS;
            
            if (0 == cur_col) {
                cur_row = cur_row + 1;
            }
            
            getToNextPiece();
            
            return *this;
        }
        
        /* Postfix increment */
        iterator operator++(int junk) {
            (void) junk;
            iterator temp = *this;
            ++*this;
            return temp;
        }
        
        iterated_value operator*() {
            return iterated_value(cur_row,
                                  cur_col,
                                  *board.board[cur_row][cur_col].piece,
                                  board.board[cur_row][cur_col].player);
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
        BoardPiece &board_piece = board[row][col];
        if (nullptr == board_piece.piece) {
            return nullptr;
        }
        
        return std::make_unique<const std::pair<int, GAME_PIECE>>(board_piece.player, *board_piece.piece);
    }
    
    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player)
    {
        BoardPiece previous = board[row][col];
        board[row][col] = BoardPiece(player, piece);
        
        if (nullptr == previous.piece) {
            return nullptr;
        }
        
        return std::make_unique<const std::pair<int, GAME_PIECE>>(previous.player, *previous.piece);
    }
};

#endif