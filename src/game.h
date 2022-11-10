#include <vector>
#include <string>

#ifndef GAME_H
#define GAME_H

class Game{
private:

    std::vector<class Board> positions;

public:

    std::string playTurn(std::string FEN);

};

#endif
