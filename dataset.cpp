#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <ctime> 

using namespace std;

// =========================================================
// MODULE 1: THE BLUEPRINT
// =========================================================
struct StudyTask {
    string taskID;
    string taskName;
    int estimatedStudyTime; 
    int importanceScore;    
    int deadline;           
    int difficultyLevel;    
    string taskType;        
};

// ---------------------------------------------------------
// HELPER FUNCTION: Print Tasks Neatly
// ---------------------------------------------------------
void printTasks(StudyTask tasks[], int size) {
    cout << left << setw(5) << "ID" << setw(35) << "Task Name" 
         << setw(6) << "Time" << setw(7) << "Score" << setw(10) << "Deadline" << "\n";
    cout << "-----------------------------------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << left << setw(5) << tasks[i].taskID << setw(35) << tasks[i].taskName 
             << setw(6) << tasks[i].estimatedStudyTime << setw(7) << tasks[i].importanceScore 
             << setw(10) << tasks[i].deadline << "\n";
    }
}

// ---------------------------------------------------------
// FUNCTION: MANUAL INPUT (Module 1)
// ---------------------------------------------------------
int createCustomScenario(StudyTask customArray[], int &availableTime) {
    int numTasks;
    cout << "\n--- MANUAL INPUT MODE ---" << endl;
    do {
        cout << "How many tasks? (Must be between 8 and 15): ";
        cin >> numTasks;
    } while (numTasks < 8 || numTasks > 15);

    cout << "Enter the Total Available Time (Wallet in hours): ";
    cin >> availableTime;

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

// =========================================================
// MODULE 2: SORTING (Quick Sort by Urgent Deadline)
// =========================================================
// =========================================================
// MODULE 2: SORTING
// =========================================================
bool compareTasks(const StudyTask& a, const StudyTask& b, int mode) {
    if (mode == 1) { 
        // Mode 1: Highest Importance First (Tie-breaker: Closest Deadline)
        if (a.importanceScore != b.importanceScore) return a.importanceScore > b.importanceScore;
        return a.deadline < b.deadline;
    } 
    else if (mode == 2) { 
        // Mode 2: Closest Deadline First (Tie-breaker: Highest Importance)
        if (a.deadline != b.deadline) return a.deadline < b.deadline;
        return a.importanceScore > b.importanceScore;
    } 
    else if (mode == 3) { 
        // Mode 3: Shortest Study Time First (Quick wins)
        if (a.estimatedStudyTime != b.estimatedStudyTime) return a.estimatedStudyTime < b.estimatedStudyTime;
        return a.importanceScore > b.importanceScore;
    } 
    else if (mode == 4) { 
        // Mode 4: Highest Difficulty First (Tackle the hardest stuff first)
        if (a.difficultyLevel != b.difficultyLevel) return a.difficultyLevel > b.difficultyLevel;
        return a.importanceScore > b.importanceScore;
    }
    return false; // Default fallback
}
void merge(StudyTask arr[], int left, int mid, int right, int mode) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    StudyTask* L = new StudyTask[n1];
    StudyTask* R = new StudyTask[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareTasks(L[i], R[j], mode)) {
            arr[k] = L[i];
            i++;
        } else if (compareTasks(R[j], L[i], mode)) {
            arr[k] = R[j];
            j++;
        } else {
            arr[k] = L[i];//ensure stability by taking from left first
            i++;
        }
        k++;
    }
    while (i < n1) { 
        arr[k] = L[i]; i++; k++; 
    }
    while (j < n2) { 
        arr[k] = R[j]; j++; k++; 
    }
    delete[] L;
    delete[] R;
}
void mergeSort(StudyTask arr[], int left, int right, int mode) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, mode);
    mergeSort(arr, mid + 1, right, mode);
    merge(arr, left, mid, right, mode);
}
void runSortingModule(StudyTask tasks[], int size, int availableTime, int sortMode, int &outScore, int &outTime, string &outTasks) {
    cout << "\n>>> MODULE 2: MERGE SORT RANKING <<<\n";
    
    // We DELETED the menu from here! The user already picked their mode in main()!

    // 1. Execute the Merge Sort using the chosen mode
    mergeSort(tasks, 0, size - 1, sortMode);

    // 2. PHASE 1: PRINT EXACTLY LIKE TABLE 3
    cout << left 
         << setw(6)  << "Rank"
         << setw(6)  << "ID" 
         << setw(35) << "Task Name" 
         << setw(12) << "Importance" 
         << setw(12) << "Deadline" 
         << setw(12) << "StudyTime" << "\n";
    cout << string(80, '-') << "\n";
    
    for (int i = 0; i < size; i++) {
        cout << left 
             << setw(6)  << (i + 1)
             << setw(6)  << tasks[i].taskID 
             << setw(35) << tasks[i].taskName 
             << setw(12) << tasks[i].importanceScore 
             << setw(12) << to_string(tasks[i].deadline) + " days" 
             << setw(12) << to_string(tasks[i].estimatedStudyTime) + " hrs" << "\n";
    }
    cout << string(80, '-') << "\n";

    // 3. PHASE 2: SILENTLY CALCULATE DATA FOR MODULE 6
    outTime = 0;
    outScore = 0;
    outTasks = "";

    for (int i = 0; i < size; i++) {
        if (outTime + tasks[i].estimatedStudyTime <= availableTime) {
            outTime += tasks[i].estimatedStudyTime;
            outScore += tasks[i].importanceScore;
            outTasks += tasks[i].taskID + " "; 
        }
    }
}

// =========================================================
// MODULE 3: GREEDY PLANNING (Highest Importance First)
// =========================================================
void runGreedyModule(StudyTask tasks[], int size, int availableTime, int &outScore, int &outTime, string &outTasks) {
    cout << "\n>>> MODULE 3: GREEDY STRATEGY (Highest Importance First) <<<\n";

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tasks[j].importanceScore < tasks[j + 1].importanceScore) {
                swap(tasks[j], tasks[j + 1]);
            }
        }
    }

    outTime = 0;
    outScore = 0;
    outTasks = "";
    int selectedCount = 0;
    StudyTask selectedTasks[15]; 

    for (int i = 0; i < size; i++) {
        if (outTime + tasks[i].estimatedStudyTime <= availableTime) {
            selectedTasks[selectedCount] = tasks[i];
            outTime += tasks[i].estimatedStudyTime;
            outScore += tasks[i].importanceScore;
            outTasks += tasks[i].taskID + " "; // Add to string for Module 6
            selectedCount++;
        }
    }
    
    cout << "Selected Tasks (Budget: " << availableTime << " hrs):\n";
    printTasks(selectedTasks, selectedCount); 
    cout << "-> Greedy Total Score: " << outScore << " | Time Used: " << outTime << "/" << availableTime << " hours\n";
}

// =========================================================
// MODULE 4: DYNAMIC PROGRAMMING (0/1 Knapsack)
// =========================================================
void runDynamicProgrammingModule(StudyTask tasks[], int size, int availableTime, int &outScore, int &outTime, string &outTasks) {
    cout << "\n>>> MODULE 4: DYNAMIC PROGRAMMING (0/1 Knapsack Optimal Selection) <<<\n";

    vector<vector<int>> V(size + 1, vector<int>(availableTime + 1, 0));

    for (int i = 1; i <= size; i++) {
        int weight = tasks[i - 1].estimatedStudyTime;
        int value = tasks[i - 1].importanceScore;
        
        for (int w = 0; w <= availableTime; w++) {
            if (weight <= w) {
                V[i][w] = max(V[i - 1][w], V[i - 1][w - weight] + value);
            } else {
                V[i][w] = V[i - 1][w];
            }
        }
    }

    int res = V[size][availableTime];
    outScore = res; 
    int w = availableTime;
    outTime = 0;
    outTasks = "";
    int selectedCount = 0;
    StudyTask selectedTasks[15];
    
    for (int i = size; i > 0 && res > 0; i--) {
        if (res == V[i - 1][w]) continue; 
        else {
            selectedTasks[selectedCount] = tasks[i - 1]; 
            outTime += tasks[i - 1].estimatedStudyTime;
            res = res - tasks[i - 1].importanceScore;
            w = w - tasks[i - 1].estimatedStudyTime;
            outTasks += tasks[i - 1].taskID + " "; // Add to string for Module 6
            selectedCount++;
        }
    }
    
    cout << "Selected Tasks (Budget: " << availableTime << " hrs):\n";
    printTasks(selectedTasks, selectedCount); 
    cout << "-> DP Optimal Total Score: " << outScore << " | Time Used: " << outTime << "/" << availableTime << " hours\n";
}

// =========================================================
// MODULE 5: AI/ML RECOMMENDATION (k-Nearest Neighbours)
// =========================================================
struct TrainingExample {
    double timePressure;
    double avgImportance;
    double impVariance;
    double deadlineTightness;
    string predictedStrategy;
};

string runAIRecommendation(StudyTask tasks[], int size, int availableTime) {
    cout << "\n>>> MODULE 5: AI/ML STRATEGY RECOMMENDATION (k-NN Classifier) <<<\n";

    int tTime = 0, tImportance = 0, tDeadlineDays = 0;
    for (int i = 0; i < size; i++) {
        tTime += tasks[i].estimatedStudyTime;
        tImportance += tasks[i].importanceScore;
        tDeadlineDays += tasks[i].deadline;
    }

    double timePressureR = (double)tTime / availableTime;
    double aImportance = (double)tImportance / size;
    double deadHours = tDeadlineDays * 24.0; 
    double deadlineTightness = (double)tTime / deadHours;

    double squareDiff = 0;
    for (int i = 0; i < size; i++) {
        squareDiff += pow(tasks[i].importanceScore - aImportance, 2);
    }
    double varImportance = squareDiff / size;

    cout << "Extracted Scenario Features:\n";
    cout << fixed << setprecision(2);
    cout << "- Time Pressure Ratio: " << timePressureR << "\n";
    cout << "- Average Importance: " << aImportance << "\n";
    cout << "- Importance Variance: " << varImportance << "\n";
    cout << "- Deadline Tightness: " << deadlineTightness << "\n\n";

    TrainingExample dataset[12] = {
        {0.7, 3.5, 1.2, 0.01, "Greedy Strategy"},
        {0.8, 3.6, 1.3, 0.01, "Greedy Strategy"},
        {0.6, 3.4, 1.1, 0.01, "Greedy Strategy"},
        {0.9, 3.5, 1.2, 0.02, "Greedy Strategy"},
        {1.7, 3.5, 1.2, 0.02, "Sorting-based Ranking"},
        {1.8, 3.4, 1.3, 0.02, "Sorting-based Ranking"},
        {1.6, 3.6, 1.2, 0.03, "Sorting-based Ranking"},
        {1.9, 3.5, 1.1, 0.02, "Sorting-based Ranking"},
        {2.3, 2.7, 2.6, 0.01, "Dynamic Programming"},
        {2.4, 2.8, 2.7, 0.01, "Dynamic Programming"},
        {2.2, 2.6, 2.5, 0.02, "Dynamic Programming"},
        {2.5, 2.7, 2.8, 0.01, "Dynamic Programming"}
    };

    double minDistance = numeric_limits<double>::max();
    string bestStrategy = "";
    int nearestNeighborIndex = -1;

    for (int i = 0; i < 12; i++) {
        double distance = sqrt(
            pow(timePressureR - dataset[i].timePressure, 2) +
            pow(aImportance - dataset[i].avgImportance, 2) +
            pow(varImportance - dataset[i].impVariance, 2) +
            pow(deadlineTightness - dataset[i].deadlineTightness, 2)
        );

        if (distance < minDistance) {
            minDistance = distance;
            bestStrategy = dataset[i].predictedStrategy;
            nearestNeighborIndex = i + 1; 
        }
    }

    cout << "AI PREDICTION:\n";
    cout << "-> Recommended Strategy: " << bestStrategy << "\n";
    return bestStrategy; 
}

// =========================================================
// MODULE 6: PERFORMANCE MEASUREMENT & COMPARISON
// =========================================================
void printModule6Comparison(double sortTimeMs, int sortScore, int sortTimeUsed, string sortTasks,
                            double greedTimeMs, int greedScore, int greedTimeUsed, string greedTasks,
                            double dpTimeMs, int dpScore, int dpTimeUsed, string dpTasks,
                            double aiTimeMs, string aiPrediction, int wallet) {
    cout << "\n========================================================================================================================\n";
    cout << "                                      MODULE 6: PERFORMANCE COMPARISON TABLE (TABLE 7)\n";
    cout << "========================================================================================================================\n";
    cout << left << setw(23) << "Strategy" 
         << setw(35) << "Selected Tasks" 
         << setw(13) << "Time Used" 
         << setw(13) << "Total Score" 
         << setw(15) << "Exec Time(ms)" 
         << "Comment\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";

    cout << left << setw(23) << "Sorting-based Ranking" 
         << setw(35) << sortTasks.substr(0, 33) // Truncate slightly if it overflows, keeps table neat
         << to_string(sortTimeUsed) + "/" + to_string(wallet) + " hrs" << setw(4) << ""
         << setw(13) << sortScore 
         << fixed << setprecision(3) << setw(15) << sortTimeMs 
         << "Safest for tight deadlines.\n";

    cout << left << setw(23) << "Greedy Strategy" 
         << setw(35) << greedTasks.substr(0, 33) 
         << to_string(greedTimeUsed) + "/" + to_string(wallet) + " hrs" << setw(4) << ""
         << setw(13) << greedScore 
         << fixed << setprecision(3) << setw(15) << greedTimeMs 
         << "Fastest, grabs obvious high values.\n";

    cout << left << setw(23) << "Dynamic Programming" 
         << setw(35) << dpTasks.substr(0, 33) 
         << to_string(dpTimeUsed) + "/" + to_string(wallet) + " hrs" << setw(4) << ""
         << setw(13) << dpScore 
         << fixed << setprecision(3) << setw(15) << dpTimeMs 
         << "Mathematically maximizes score.\n";

    cout << left << setw(23) << "AI/ML Recommendation" 
         << setw(35) << "N/A" 
         << setw(13) << "--" 
         << setw(13) << "--" 
         << fixed << setprecision(3) << setw(15) << aiTimeMs 
         << "Predicted: " << aiPrediction << "\n";
    
    cout << "========================================================================================================================\n";
}

// =========================================================
// MAIN PROGRAM
// =========================================================
int main() {
    bool isRunning = true; 

    while (isRunning) {
        int scenarioChoice;
        int algoChoice;
        int activeNumTasks = 12; 
        int activeAvailableTime = 0; 
        StudyTask activeScenario[15]; 

        cout << "\n========================================\n";
        cout << "      STUDYSMART AI - SYSTEM BOOT\n";
        cout << "========================================\n";
        cout << "1. Run Low-Pressure Scenario (Auto)\n";
        cout << "2. Run Deadline-Focused Scenario (Auto)\n";
        cout << "3. Run Importance-Focused Scenario (Auto)\n";
        cout << "4. Enter Custom Scenario (Manual)\n";
        cout << "5. Exit Program\n";
        cout << "========================================\n";
        cout << "Select an option (1-5): ";
        cin >> scenarioChoice;

        if (scenarioChoice == 5) {
            cout << "\nShutting down StudySmart AI. Goodbye!\n";
            isRunning = false;
            break; 
        }
        else if (scenarioChoice == 1) {
            activeAvailableTime = 45; 
            StudyTask temp[12] = {
                {"T1",  "Watch NLP Lecture",                  3, 2, 10, 3, "Lecture"},     
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
            cout << "\n> Low-Pressure Scenario Loaded! (Wallet: " << activeAvailableTime << " hrs)\n";
        } 
        else if (scenarioChoice == 2) {
            activeAvailableTime = 20; 
            StudyTask temp[12] = {
                {"T1",  "Watch NLP Lecture",                  3, 2, 10, 3, "Lecture"},
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
            cout << "\n> Deadline-Focused Scenario Loaded! (Wallet: " << activeAvailableTime << " hrs)\n";
        } 
        else if (scenarioChoice == 3) {
            activeAvailableTime = 15; 
            StudyTask temp[12] = {
                {"T1",  "Watch NLP Lecture",                  3, 1, 10, 3, "Lecture"},    
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
            cout << "\n> Importance-Focused Scenario Loaded! (Wallet: " << activeAvailableTime << " hrs)\n";
        } 
        else if (scenarioChoice == 4) {
            activeNumTasks = createCustomScenario(activeScenario, activeAvailableTime);
            cout << "\n> Custom Scenario Loaded! (Wallet: " << activeAvailableTime << " hrs)\n";
        } 
        else {
            cout << "Invalid scenario choice. Please try again.\n";
            continue; 
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
        cout << "5. Run ALL Modules & Compare (Module 6)\n";
        cout << "6. Go Back to Scenario Menu\n";
        cout << "7. Exit Program\n";
        cout << "========================================\n";
        cout << "Select a strategy (1-7): ";
        cin >> algoChoice;

        if (algoChoice == 7) {
            cout << "\nShutting down StudySmart AI. Goodbye!\n";
            break; 
        }
        if (algoChoice == 6) {
            continue; 
        }
        // --- NEW BLOCK: Ask for Sorting Mode early! ---
        int activeSortMode = 1; 
        if (algoChoice == 2 || algoChoice == 5) {
            cout << "\n========================================\n";
            cout << "      MODULE 2 SETTINGS\n";
            cout << "========================================\n";
            cout << "Select your primary sorting criterion:\n";
            cout << "1. Highest Importance First\n";
            cout << "2. Closest Deadline First (Urgency)\n";
            cout << "3. Shortest Study Time First (Quick Wins)\n";
            cout << "4. Highest Difficulty First\n";
            cout << "Choice (1-4): ";
            cin >> activeSortMode;
            if (activeSortMode < 1 || activeSortMode > 4) activeSortMode = 1;
        }

        cout << "\n========================================\n";
        cout << "      EXECUTING MODULES...\n";
        cout << "========================================\n";

        StudyTask copyArr[15]; 
        int dummyScore = 0, dummyTime = 0; string dummyTasks = "";

        // Variables for Module 6
        int sortScore=0, sortTimeUsed=0; double sortTimeMs=0.0; string sortTasks = "";
        int greedScore=0, greedTimeUsed=0; double greedTimeMs=0.0; string greedTasks = "";
        int dpScore=0, dpTimeUsed=0; double dpTimeMs=0.0; string dpTasks = "";
        string aiPrediction = ""; double aiTimeMs=0.0;

        clock_t start, end;

        // Note: AI needs to run before the arrays get sorted/shuffled by other algorithms
        if (algoChoice == 1 || algoChoice == 5) {
            for(int i=0; i<activeNumTasks; i++) copyArr[i] = activeScenario[i];
            start = clock();
            aiPrediction = runAIRecommendation(copyArr, activeNumTasks, activeAvailableTime);
            end = clock();
            aiTimeMs = double(end - start) / CLOCKS_PER_SEC * 1000.0;
        }
        if (algoChoice == 2 || algoChoice == 5) {
            
            for(int i=0; i<activeNumTasks; i++) copyArr[i] = activeScenario[i];
            start = clock();
            runSortingModule(copyArr, activeNumTasks, activeAvailableTime,activeSortMode,sortScore, sortTimeUsed, sortTasks);
            end = clock();
            sortTimeMs = double(end - start) / CLOCKS_PER_SEC * 1000.0;
        }
        if (algoChoice == 3 || algoChoice == 5) {
            for(int i=0; i<activeNumTasks; i++) copyArr[i] = activeScenario[i];
            start = clock();
            runGreedyModule(copyArr, activeNumTasks, activeAvailableTime, greedScore, greedTimeUsed, greedTasks);
            end = clock();
            greedTimeMs = double(end - start) / CLOCKS_PER_SEC * 1000.0;
        }
        if (algoChoice == 4 || algoChoice == 5) {
            for(int i=0; i<activeNumTasks; i++) copyArr[i] = activeScenario[i];
            start = clock();
            runDynamicProgrammingModule(copyArr, activeNumTasks, activeAvailableTime, dpScore, dpTimeUsed, dpTasks);
            end = clock();
            dpTimeMs = double(end - start) / CLOCKS_PER_SEC * 1000.0;
        }

        if (algoChoice == 5) {
            printModule6Comparison(sortTimeMs, sortScore, sortTimeUsed, sortTasks,
                                   greedTimeMs, greedScore, greedTimeUsed, greedTasks,
                                   dpTimeMs, dpScore, dpTimeUsed, dpTasks,
                                   aiTimeMs, aiPrediction, activeAvailableTime);
        }

        if (algoChoice < 1 || algoChoice > 5) {
            cout << "Invalid strategy selected.\n";
        } 

        cout << "\n========================================\n";
        cout << "Execution Complete. Press Enter to return to the Main Menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cin.get();    
    }
    return 0;
}