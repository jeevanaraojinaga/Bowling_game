#include <iostream>
#include <vector>
using namespace std;

/* Macros */
#define TOTAL_FRAMES 10
#define STRIKE_SCORE 10
#define SPARE_SCORE 10

class BowlingGame {
public:
    /* Constructor */
    BowlingGame(const vector<int>& allRolls) {
        rolls = allRolls;
    }

    // Function to calculate the total score of the game
    int getTotalScore() {
        int totalScore = 0;
        int index = 0; // Index to track position in rolls vector

        for (int frame = 1; frame <= TOTAL_FRAMES; ++frame) {
            if (isStrike(index)) {
                // Strike: 10 + next two rolls as bonus
                totalScore += STRIKE_SCORE + strikeBonus(index);
                index += 1; // Strike consumes 1 roll
            } else if (isSpare(index)) {
                // Spare: 10 + next roll as bonus
                totalScore += SPARE_SCORE + spareBonus(index);
                index += 2; // Spare consumes 2 rolls
            } else {
                // Open frame: just sum the two rolls
                totalScore += rolls[index] + rolls[index + 1];
                index += 2;
            }
        }

        return totalScore;
    }

private:
    vector<int> rolls;

    // Check if the current roll is a strike
    bool isStrike(int idx) {
        return rolls[idx] == STRIKE_SCORE;
    }

    // Check if the two rolls make a spare
    bool isSpare(int idx) {
        return (rolls[idx] + rolls[idx + 1]) == SPARE_SCORE;
    }

    // Get bonus for a strike (next two rolls)
    int strikeBonus(int idx) {
        return rolls[idx + 1] + rolls[idx + 2];
    }

    // Get bonus for a spare (next one roll)
    int spareBonus(int idx) {
        return rolls[idx + 2];
    }
};

int main() {
    // Test game rolls: each number represents pins knocked down in a roll
    vector<int> gameRolls = {4, 1, 5, 4, 6, 4, 10, 9, 1, 
                             10, 10, 7, 2, 10, 2, 6};

    BowlingGame game(gameRolls);
    int finalScore = game.getTotalScore();

    cout << "Final Score: " << finalScore << endl;
    return 0;
}
