#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <list>
#include <ctime>
using namespace std;

struct StudyTask {
    string taskID;
    string taskName;
    int estimatedStudyTime; // Hours
    int importanceScore;    // 1 to 5
    int deadline;           // Days
    int difficultyLevel;    // 1 to 5
    string taskType;        
};

int createCustomScenario(StudyTask customArray[]);
list<StudyTask> runDynamicProgrammingModule(StudyTask scenario[], int numTasks);


int main() {
    int scenarioChoice;
    int algoChoice;
    int activeNumTasks = 12; // Default for your auto scenarios
    list<StudyTask> selectedTasks; // To hold the final chosen tasks after algorithm execution
    
    // Create a blank array of 15 (max allowed) to hold the chosen scenario
    StudyTask activeScenario[15]; 

    // =========================================================
    // THE MASTER TASK LIST (Grouped by your custom order)
    // T1, T2:   Lecture
    // T3-T5:    Practice
    // T6, T7:   Tutorial
    // T8-T10:   Assignment
    // T11, T12: Revision
    // Total Time Needed: 35 hours.
    // =========================================================
    cout << "========================================\n";
    cout << "      STUDYSMART AI - SYSTEM BOOT\n";
    cout << "========================================\n";
    cout << "1. Run Low-Pressure Scenario (Auto)\n";
    cout << "2. Run Deadline-Focused Scenario (Auto)\n";
    cout << "3. Run Importance-Focused Scenario (Auto)\n";
    cout << "4. Enter Custom Scenario (Manual)\n";
    cout << "========================================\n";
    cout << "Select a scenario (1-4): ";
    cin >> scenarioChoice;

    if (scenarioChoice == 1) {
        StudyTask temp[12] = {
            {"T1",  "Watch NLP Sentiment Lecture",        3, 2, 10, 3, "Lecture"},     
            {"T2",  "Read Dynamic Programming Chapter",   3, 1, 12, 4, "Lecture"},     
            {"T3",  "Train XGBoost Model",                3, 4,  8, 4, "Practice"},    
            {"T4",  "Practise 0/1 Knapsack Code",         2, 4,  9, 3, "Practice"},    
            {"T5",  "Debug C++ classwork issues",         3, 3, 10, 4, "Practice"},    
            {"T6",  "Complete Complexity Lab",            2, 3,  7, 3, "Tutorial"},    
            {"T7",  "Discuss FYP Architecture",           2, 3,  8, 2, "Tutorial"},    
            {"T8",  "Dynamic Prog. Assignment",           4, 4,  9, 4, "Assignment"},  
            {"T9",  "Write OS system Proposal",           4, 5, 10, 4, "Assignment"},  
            {"T10", "Submit Data Analysis Essay",         3, 4, 10, 3, "Assignment"},  
            {"T11", "Review Sorting Algorithms",          2, 4,  8, 2, "Revision"},    
            {"T12", "Midterm Algorithm Exam Prep",        4, 5,  8, 5, "Revision"}     
        };
        for(int i=0; i<12; i++) activeScenario[i] = temp[i]; 
        cout << "\n> Low-Pressure Scenario Loaded!\n";
    } 
    else if (scenarioChoice == 2) {
        StudyTask temp[12] = {
            {"T1",  "Watch NLP Sentiment Lecture",        3, 2, 10, 3, "Lecture"},
            {"T2",  "Read Dynamic Programming Chapter",   3, 1, 12, 4, "Lecture"},
            {"T3",  "Train XGBoost Model",                3, 4,  8, 4, "Practice"},
            {"T4",  "Practise 0/1 Knapsack Code",         2, 4,  9, 3, "Practice"},
            {"T5",  "Debug C++ classwork issues",         3, 3, 10, 4, "Practice"},
            {"T6",  "Complete Complexity Lab",            2, 3,  7, 3, "Tutorial"},
            {"T7",  "Discuss FYP Architecture",           2, 3,  8, 2, "Tutorial"},
            {"T8",  "Dynamic Prog. Assignment",           4, 4,  1, 4, "Assignment"}, 
            {"T9",  "Write OS system Proposal",           4, 5,  2, 4, "Assignment"}, 
            {"T10", "Submit Data Analysis Essay",         3, 4,  1, 3, "Assignment"}, 
            {"T11", "Review Sorting Algorithms",          2, 4,  2, 2, "Revision"},   
            {"T12", "Midterm Algorithm Exam Prep",        4, 5,  1, 5, "Revision"}    
        };
        for(int i=0; i<12; i++) activeScenario[i] = temp[i];
        cout << "\n> Deadline-Focused Scenario Loaded!\n";
    } 
    else if (scenarioChoice == 3) {
        StudyTask temp[12] = {
            {"T1",  "Watch NLP Sentiment Lecture",        3, 1, 10, 3, "Lecture"},    
            {"T2",  "Read Dynamic Programming Chapter",   3, 1, 12, 4, "Lecture"},    
            {"T3",  "Train XGBoost Model",                3, 2,  8, 4, "Practice"},   
            {"T4",  "Practise 0/1 Knapsack Code",         2, 2,  9, 3, "Practice"},   
            {"T5",  "Debug C++ classwork issues" ,        3, 1, 10, 4, "Practice"},   
            {"T6",  "Complete Complexity Lab",            2, 1,  7, 3, "Tutorial"},   
            {"T7",  "Discuss FYP Architecture",           2, 1,  8, 2, "Tutorial"},   
            {"T8",  "Dynamic Prog. Assignment",           4, 5,  9, 4, "Assignment"}, 
            {"T9",  "Write OS system Proposal",           4, 5, 10, 4, "Assignment"}, 
            {"T10", "Submit Data Analysis Essay",         3, 5, 10, 3, "Assignment"}, 
            {"T11", "Review Sorting Algorithms",          2, 4,  8, 2, "Revision"},   
            {"T12", "Midterm Algorithm Exam Prep",        4, 5,  8, 5, "Revision"}    
        };
        for(int i=0; i<12; i++) activeScenario[i] = temp[i];
        cout << "\n> Importance-Focused Scenario Loaded!\n";
    } 
    else if (scenarioChoice == 4) {
        activeNumTasks = createCustomScenario(activeScenario);
        cout << "\n> Custom Scenario Loaded!\n";
    } 
    else {
        cout << "Invalid choice. Exiting..." << endl;
        return 0;
    }

    // =========================================================
    // MENU 2: ALGORITHM SELECTION
    // =========================================================
    cout << "\n========================================\n";
    cout << "      SELECT ALGORITHMIC STRATEGY\n";
    cout << "========================================\n";
    cout << "1. Run AI/ML Recommendation (Module 5)\n";
    cout << "2. Run Sorting / Ranking (Module 2)\n";
    cout << "3. Run Greedy Planning (Module 3)\n";
    cout << "4. Run Dynamic Programming (Module 4)\n";
    cout << "5. Run ALL Modules (For Comparison)\n";
    cout << "========================================\n";
    cout << "Select a strategy (1-5): ";
    cin >> algoChoice;

    cout << "\n========================================\n";
    cout << "      EXECUTING MODULES...\n";
    cout << "========================================\n";

    // =========================================================
    // TEAMMATE HANDOFF ZONE
    // Teammates: Uncomment your function calls inside the correct block!
    // =========================================================

    if (algoChoice == 1) {
        // Student 5: Put your AI Module call here
        // runAIRecommendation(activeScenario, activeNumTasks);
    }
    else if (algoChoice == 2) {
        // Student 2: Put your Sorting Module call here
        // runSortingModule(activeScenario, activeNumTasks);
    }
    else if (algoChoice == 3) {
        // Student 3: Put your Greedy Module call here
        // Note: You will need to prompt the user for 'Available Time' inside your function!
        // runGreedyModule(activeScenario, activeNumTasks);
    }
    else if (algoChoice == 4) {
        selectedTasks = runDynamicProgrammingModule(activeScenario, activeNumTasks);
        cout << "\nOptimal Tasks Selected:" << endl;
        for (const auto& task : selectedTasks) {
            cout << "- " << task.taskID << " (" << task.taskName << ")" << endl;
        }
    }
    else if (algoChoice == 5){
        double startTime, duration;
        int totalImportance = 0, totalStudyTime = 0;

        // Dynamic Programming: Performance Measurement and Comparison
        startTime = clock();
        selectedTasks = runDynamicProgrammingModule(activeScenario, activeNumTasks);
        duration = double(clock() - startTime) / CLOCKS_PER_SEC;
        for (const auto& task : selectedTasks) {
            totalImportance += task.importanceScore;
            totalStudyTime += task.estimatedStudyTime;
        }
        string comment = "The DP algorithm identifies the optimal subset of tasks that maximizes the importance score within the given available time capacity. It considers all combinations of tasks and their respective study times and importance scores to find the best possible solution.";
        string tasks = "";
        for (const auto& task : selectedTasks) {
            tasks += task.taskID + ", ";
        }
        cout << "\nDynamic Programming: Selected Tasks: " << tasks << "\n";
        cout << "Dynamic Programming: Total Study Time: " << totalStudyTime << "\n";
        cout << "Dynamic Programming: Total Importance Score: " << totalImportance << "\n";
        cout << "Dynamic Programming: Execution Time: " << duration << " seconds\n";
        cout << "Dynamic Programming: Comment: " << comment << "\n";
    }
    else{
        cout << "Invalid strategy selected." << endl;
        return -1;
    }
    cout << "\nExecution Complete!" << endl;

    return 0;
}


// ---------------------------------------------------------
// FUNCTION: MANUAL INPUT (Module 1)
// ---------------------------------------------------------
int createCustomScenario(StudyTask customArray[]) {
    int numTasks;
    
    cout << "\n--- MANUAL INPUT MODE ---" << endl;
    do {
        cout << "How many tasks? (Must be between 8 and 15): ";
        cin >> numTasks;
    } while (numTasks < 8 || numTasks > 15);

    for (int i = 0; i < numTasks; i++) {
        cout << "\n--- Task " << (i + 1) << " ---" << endl;
        cout << "ID (e.g., T1): ";
        cin >> customArray[i].taskID;
        
        cin.ignore(); 
        cout << "Name: ";
        getline(cin, customArray[i].taskName);
        
        cout << "Estimated Time (Hours): ";
        cin >> customArray[i].estimatedStudyTime;
        
        cout << "Importance Score (1-5): ";
        cin >> customArray[i].importanceScore;
        
        cout << "Deadline (Days): ";
        cin >> customArray[i].deadline;
        
        cout << "Difficulty (1-5): ";
        cin >> customArray[i].difficultyLevel;
        
        cout << "Type (Lecture/Tutorial/Practice/Assignment/Revision): ";
        cin >> customArray[i].taskType;
    }
    return numTasks; 
}

// ---------------------------------------------------------
// FUNCTION: Dynamic Programming (Module 4)
// ---------------------------------------------------------
list<StudyTask> runDynamicProgrammingModule(StudyTask scenario[], int numTasks){
    unsigned int AvailableTime = 0;                         // Capacity of Knapsack
    // Input validation loop to ensure a valid integer for AvailableTime
    do{
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your available study time in hours: ";
    } while (!(cin >> AvailableTime));

    // Create empty DP table: V[i][j] = max importance score using first i tasks with j hours available
    int V[numTasks][AvailableTime+1] = {};
    for (int i = 0; i < numTasks; i++) {
        V[i][0] = 0;
    }
    for (int j = 0; j <= AvailableTime; j++) {
        V[0][j] = 0;
    }
    for (int i = 0; i < numTasks; i++) {
        for (int j = 0; j <= AvailableTime; j++) {
            V[i][j] = (i > 0 ? V[i-1][j] : 0);
            int s_i = scenario[i].estimatedStudyTime;
            if (s_i <= j) {
                V[i][j] = max(scenario[i].importanceScore + (i > 0 ? V[i-1][j - s_i] : 0), V[i][j]);
            }
        }
    }
    // // Print DP table for debugging
    // for (int i = 0; i < numTasks; i++) {
    //     for (int j = 0; j <= AvailableTime; j++) {
    //         cout << setw(3) << V[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // Backtracking to find optimal solution tasks
    int currentScore = V[numTasks - 1][AvailableTime];
    int remainingTime = AvailableTime;
    list<StudyTask> selectedTasks;

    for (int i = numTasks - 1; i > 0 && currentScore > 0; i--) {
        // If the value is not the same as the row above it, we included this task
        if (currentScore != V[i - 1][remainingTime]) {
            selectedTasks.push_front(scenario[i]);
            currentScore -= scenario[i].importanceScore;
            remainingTime -= scenario[i].estimatedStudyTime;
        }
    }
    
    // Check the very first item (Row 0)
    if (currentScore > 0) {
        selectedTasks.push_front(scenario[0]);
    }

    return selectedTasks;
}