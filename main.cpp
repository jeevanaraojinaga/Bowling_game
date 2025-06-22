#include <iostream>
#include <vector>
using namespace std;

class BowlingGame {
public:
    BowlingGame(const vector<int>& allRolls) {
        rolls = allRolls;
    }

    int getTotalScore() {
        int totalScore = 0;
        int index = 0;

        for (int frame = 1; frame <= 10; ++frame) {
            if (isStrike(index)) {
                totalScore += 10 + strikeBonus(index);
                index += 1;  // Only one roll in a strike frame
            } else if (isSpare(index)) {
                totalScore += 10 + spareBonus(index);
                index += 2;  // Two rolls in a spare
            } else {
                totalScore += rolls[index] + rolls[index + 1];
                index += 2;
            }
        }

        return totalScore;
    }

private:
    vector<int> rolls;

    bool isStrike(int idx) {
        return rolls[idx] == 10;
    }

    bool isSpare(int idx) {
        return (rolls[idx] + rolls[idx + 1]) == 10;
    }

    int strikeBonus(int idx) {
        return rolls[idx + 1] + rolls[idx + 2];
    }

    int spareBonus(int idx) {
        return rolls[idx + 2];
    }
};

int main() {

    vector<int> gameRolls = {4, 1, 5, 4, 6, 4, 10, 9, 1, 10, 10, 7, 2, 10, 2, 6};

    BowlingGame game(gameRolls);
    int finalScore = game.getTotalScore();

    cout << "Final Score: " << finalScore << endl;
    return 0;
}
