#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int NUM_TASKS = 12;

struct StudyTask {
    string taskID;
    string taskName;
    int estimatedStudyTime; // Hours
    int importanceScore;    // 1 to 5
    int deadline;           // Days
    int difficultyLevel;    // 1 to 5
    string taskType;        
};

void DynamicP(StudyTask scenario[], int capacity);

int main() {
    // =========================================================
    // THE MASTER TASK LIST (Grouped by your custom order)
    // T1, T2:   Lecture
    // T3-T5:    Practice
    // T6, T7:   Tutorial
    // T8-T10:   Assignment
    // T11, T12: Revision
    // Total Time Needed: 35 hours.
    // =========================================================

    // ---------------------------------------------------------
    // SCENARIO 1: LOW-PRESSURE (The Baseline)
    // Wallet: 45 hours. 
    // Logic: Importance follows your realistic student priority: 
    // Exam/Proposal (5) > Practice (4) > Discuss (3) > Lecture (1-2).
    // Deadlines are completely relaxed (7 to 14 days).
    // ---------------------------------------------------------
    int lowPressureAvailableTime = 45;
    StudyTask lowPressureScenario[12] = {
        {"T1",  "Watch NLP Sentiment Lecture",        3, 2, 10, 3, "Lecture"},     // LOW
        {"T2",  "Read Dynamic Programming Chapter",   3, 1, 12, 4, "Lecture"},     // LOW
        {"T3",  "Train XGBoost Model",                3, 4,  8, 4, "Practice"},    // MOD-HIGH
        {"T4",  "Practise 0/1 Knapsack Code",         2, 4,  9, 3, "Practice"},    // MOD-HIGH
        {"T5",  "Debug C++ classwork issues",         3, 3, 10, 4, "Practice"},    // MOD-HIGH
        {"T6",  "Complete Complexity Lab",            2, 3,  7, 3, "Tutorial"},    // MOD
        {"T7",  "Discuss FYP Architecture",           2, 3,  8, 2, "Tutorial"},    // MOD
        {"T8",  "Dynamic Prog. Assignment",           4, 4,  9, 4, "Assignment"},  // HIGH
        {"T9",  "Write OS system Proposal",           4, 5, 10, 4, "Assignment"},  // HIGHEST
        {"T10", "Submit Data Analysis Essay",         3, 4, 10, 3, "Assignment"},  // HIGH
        {"T11", "Review Sorting Algorithms",          2, 4,  8, 2, "Revision"},    // HIGH
        {"T12", "Midterm Algorithm Exam Prep",        4, 5,  8, 5, "Revision"}     // HIGHEST
    };

    // ---------------------------------------------------------
    // SCENARIO 2: DEADLINE-FOCUSED
    // Wallet: 20 hours.
    // Logic: We use the exact same realistic importance scores, 
    // but sabotage the deadlines. Assignments and Revisions are due in 1-2 days.
    // ---------------------------------------------------------
    int deadlineAvailableTime = 20;
    StudyTask deadlineScenario[12] = {
        {"T1",  "Watch NLP Sentiment Lecture",        3, 2, 10, 3, "Lecture"},
        {"T2",  "Read Dynamic Programming Chapter",   3, 1, 12, 4, "Lecture"},
        {"T3",  "Train XGBoost Model",                3, 4,  8, 4, "Practice"},
        {"T4",  "Practise 0/1 Knapsack Code",         2, 4,  9, 3, "Practice"},
        {"T5",  "Debug C++ classwork issues",         3, 3, 10, 4, "Practice"},
        {"T6",  "Complete Complexity Lab",            2, 3,  7, 3, "Tutorial"},
        {"T7",  "Discuss FYP Architecture",           2, 3,  8, 2, "Tutorial"},
        {"T8",  "Dynamic Prog. Assignment",           4, 4,  1, 4, "Assignment"}, // URGENT
        {"T9",  "Write OS system Proposal",           4, 5,  2, 4, "Assignment"}, // URGENT
        {"T10", "Submit Data Analysis Essay",         3, 4,  1, 3, "Assignment"}, // URGENT
        {"T11", "Review Sorting Algorithms",          2, 4,  2, 2, "Revision"},   // URGENT
        {"T12", "Midterm Algorithm Exam Prep",        4, 5,  1, 5, "Revision"}    // URGENT
    };

    // ---------------------------------------------------------
    // SCENARIO 3: IMPORTANCE-FOCUSED
    // Wallet: 15 hours.
    // Logic: We take your realistic student priority and polarize 
    // it to its extreme to test the Greedy and DP algorithms.
    // Lectures/Tutorials drop strictly to 1. Core items lock at 5.
    // ---------------------------------------------------------
    int importanceAvailableTime = 15;
    StudyTask importanceScenario[12] = {
        {"T1",  "Watch NLP Sentiment Lecture",        3, 1, 10, 3, "Lecture"},    // TANKED
        {"T2",  "Read Dynamic Programming Chapter",   3, 1, 12, 4, "Lecture"},    // TANKED
        {"T3",  "Train XGBoost Model",                3, 2,  8, 4, "Practice"},   
        {"T4",  "Practise 0/1 Knapsack Code",         2, 2,  9, 3, "Practice"},   
        {"T5",  "Debug C++ classwork issues" ,        3, 1, 10, 4, "Practice"},   // TANKED
        {"T6",  "Complete Complexity Lab",            2, 1,  7, 3, "Tutorial"},   // TANKED
        {"T7",  "Discuss FYP Architecture",           2, 1,  8, 2, "Tutorial"},   // TANKED
        {"T8",  "Dynamic Prog. Assignment",           4, 5,  9, 4, "Assignment"}, // MAX PRIORITY
        {"T9",  "Write OS system Proposal",           4, 5, 10, 4, "Assignment"}, // MAX PRIORITY
        {"T10", "Submit Data Analysis Essay",         3, 5, 10, 3, "Assignment"}, // MAX PRIORITY
        {"T11", "Review Sorting Algorithms",          2, 4,  8, 2, "Revision"},   
        {"T12", "Midterm Algorithm Exam Prep",        4, 5,  8, 5, "Revision"}    // MAX PRIORITY
    };

    DynamicP(importanceScenario, importanceAvailableTime);
    // Ready for integration!
    return 0;
}

void DynamicP(StudyTask scenario[], int capacity){
    int V[NUM_TASKS][capacity+1] = {};
    for (int i = 0; i < NUM_TASKS; i++) {
        V[i][0] = 0;
    }
    for (int j = 0; j <= capacity; j++) {
        V[0][j] = 0;
    }
    for (int i = 0; i < NUM_TASKS; i++) {
        for (int j = 0; j <= capacity; j++) {
            cout << setw(3) << V[i][j] << " ";
        }
        cout << endl;
    }
    cout << "=====================" << endl;
    for (int i = 0; i < NUM_TASKS; i++) {
        for (int j = 0; j <= capacity; j++) {
            V[i][j] = (i > 0 ? V[i-1][j] : 0);
            int s_i = scenario[i].estimatedStudyTime;
            if (s_i <= j) {
                V[i][j] = max(scenario[i].importanceScore + (i > 0 ? V[i-1][j - s_i] : 0), V[i][j]);
            }
        }
    }
    for (int i = 0; i < NUM_TASKS; i++) {
        for (int j = 0; j <= capacity; j++) {
            cout << setw(3) << V[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nOptimal Tasks Selected:" << endl;
    
    int currentScore = V[NUM_TASKS - 1][capacity];
    int remainingTime = capacity;

    for (int i = NUM_TASKS - 1; i > 0 && currentScore > 0; i--) {
        // If the value is not the same as the row above it, we included this task
        if (currentScore != V[i - 1][remainingTime]) {
            cout << "- " << scenario[i].taskID << " (" << scenario[i].taskName << ")" << endl;
            
            // Subtract the score and time
            currentScore -= scenario[i].importanceScore;
            remainingTime -= scenario[i].estimatedStudyTime;
        }
    }
    
    // Check the very first item (Row 0)
    if (currentScore > 0) {
        cout << "- " << scenario[0].taskID << " (" << scenario[0].taskName << ")" << endl;
    }
}