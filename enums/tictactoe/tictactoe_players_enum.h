#ifndef TICTACTOE_PLAYERS_ENUM_H
#define TICTACTOE_PLAYERS_ENUM_H

enum class TicTacToePlayerEnum
{
    None = 0,
    Cross = 1 << 0,
    Circle = 1 << 1,
};

inline TicTacToePlayerEnum operator | (TicTacToePlayerEnum lhs, TicTacToePlayerEnum rhs)
{
    return static_cast<TicTacToePlayerEnum>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline TicTacToePlayerEnum operator & (TicTacToePlayerEnum lhs, TicTacToePlayerEnum rhs)
{
    return static_cast<TicTacToePlayerEnum>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

inline TicTacToePlayerEnum operator ! (TicTacToePlayerEnum value)
{
    if (value == TicTacToePlayerEnum::Circle) return TicTacToePlayerEnum::Cross;
    else if (value == TicTacToePlayerEnum::Cross) return TicTacToePlayerEnum::Circle;
    else return value;
}

inline bool isSet(TicTacToePlayerEnum flags, TicTacToePlayerEnum toCheck)
{
    return static_cast<int>(flags & toCheck) != 0;
}

inline void set(TicTacToePlayerEnum &flags, TicTacToePlayerEnum toSet)
{
    flags = static_cast<TicTacToePlayerEnum>(static_cast<int>(flags) | static_cast<int>(toSet));
}

inline void reset(TicTacToePlayerEnum &flags, TicTacToePlayerEnum toReset)
{
    flags = static_cast<TicTacToePlayerEnum>(static_cast<int>(flags) & ~static_cast<int>(toReset));
}

#endif // TICTACTOE_PLAYERS_ENUM_H
