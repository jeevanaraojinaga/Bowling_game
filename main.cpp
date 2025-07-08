#include <iostream>
#include <vector>
using namespace std;

/* Constants */
#define TOTAL_FRAMES 10
#define TOTAL_PINS 10

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
                totalScore += TOTAL_PINS + strikeBonus(index);
                index += 1;
            } else if (isSpare(index)) {
                totalScore += TOTAL_PINS + spareBonus(index);
                index += 2;
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
        return (idx < rolls.size()) && (rolls[idx] == TOTAL_PINS);
    }

    // Check if the two rolls make a spare
    bool isSpare(int idx) {
        return (idx + 1 < rolls.size()) && ((rolls[idx] + rolls[idx + 1]) == TOTAL_PINS);
    }

    // Get bonus for a strike (next two rolls)
    int strikeBonus(int idx) {
        if (idx + 2 < rolls.size()) {
            return rolls[idx + 1] + rolls[idx + 2];
        }
        return 0;
    }

    // Get bonus for a spare (next one roll)
    int spareBonus(int idx) {
        if (idx + 2 < rolls.size()) {
            return rolls[idx + 2];
        }
        return 0;
    }
};

int readValidRoll(int maxPins) {
    int pins;
    while (true) {
        cin >> pins;
        if (pins < 0 || pins > maxPins) {
            cout << "Invalid input. Enter a number between 0 and " << maxPins << ": ";
        } else {
            return pins;
        }
    }
}

int main() {
    vector<int> gameRolls;

    for (int frame = 1; frame <= TOTAL_FRAMES; ++frame) {
        cout << "Frame " << frame << endl;
        int firstRoll = readValidRoll(TOTAL_PINS);
        gameRolls.push_back(firstRoll);

        int secondRoll = 0;
        bool isStrike = (firstRoll == TOTAL_PINS);

        if (frame < 10) {
            if (!isStrike) {
                secondRoll = readValidRoll(TOTAL_PINS - firstRoll);
                gameRolls.push_back(secondRoll);
            }
        } else {
            // 10th frame logic
            if (isStrike) {
                secondRoll = readValidRoll(TOTAL_PINS);
                gameRolls.push_back(secondRoll);
                int thirdRoll = readValidRoll(TOTAL_PINS);
                gameRolls.push_back(thirdRoll);
            } else {
                secondRoll = readValidRoll(TOTAL_PINS - firstRoll);
                gameRolls.push_back(secondRoll);
                if (firstRoll + secondRoll == TOTAL_PINS) {
                    int thirdRoll = readValidRoll(TOTAL_PINS);
                    gameRolls.push_back(thirdRoll);
                }
            }
        }
    }

    BowlingGame game(gameRolls);
    int finalScore = game.getTotalScore();

    cout << "Final Score: " << finalScore << endl;
    return 0;
}
