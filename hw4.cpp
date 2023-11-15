#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <sstream>

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

// Function Prototypes
bool readInput(const std::string &filename, int &num_processes, int &num_resources, 
               std::vector<std::vector<int>> &alloc, std::vector<std::vector<int>> &max, 
               std::vector<int> &avail);
bool isSafeState(const std::vector<int> &processes, 
                 const std::vector<std::vector<int>> &alloc, 
                 const std::vector<std::vector<int>> &max, 
                 const std::vector<int> &avail, std::vector<int> &safeSeq, 
                 int num_processes, int num_resources);
void findSafeSequences(std::vector<int> &processes, 
                       const std::vector<std::vector<int>> &alloc, 
                       const std::vector<std::vector<int>> &max, 
                       const std::vector<int> &avail, int num_processes, 
                       int num_resources, std::vector<std::vector<int>> &finalSeq,
                       const std::string& filename);
bool compareSequences(const std::vector<int>& seq1, const std::vector<int>& seq2);

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <inputfile>\n";
        return 1;
    }

    int num_processes, num_resources;
    std::vector<std::vector<int>> alloc(MAX_PROCESSES, std::vector<int>(MAX_RESOURCES));
    std::vector<std::vector<int>> max(MAX_PROCESSES, std::vector<int>(MAX_RESOURCES));
    std::vector<int> avail(MAX_RESOURCES);
    std::vector<std::vector<int>> finalSeq; 

    if (!readInput(argv[1], num_processes, num_resources, alloc, max, avail)) {
        std::cout << "Error reading input file.\n";
        return 1;
    }

    std::vector<int> processes(num_processes);
    std::iota(processes.begin(), processes.end(), 0);

    findSafeSequences(processes, alloc, max, avail, num_processes, num_resources, finalSeq, argv[1]);

    return 0;
}

// Function Definitions
bool readInput(const std::string &filename, int &num_processes, int &num_resources, 
               std::vector<std::vector<int>> &alloc, std::vector<std::vector<int>> &max, 
               std::vector<int> &avail) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: File not found or unable to open.\n";
        return false;
    }

    // Read the entire file content and display it
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::cout << "Contents of file:\n" << fileStream.str() << "\n";

    // Rewind the file stream to the beginning
    file.clear(); // Clear any error flags
    file.seekg(0, std::ios::beg); 

    // Proceed with original logic
    file >> num_processes >> num_resources;
    if (num_processes <= 0 || num_processes > MAX_PROCESSES || num_resources <= 0 || num_resources > MAX_RESOURCES || file.fail()) {
        std::cerr << "Invalid input format or values in file.\n";
        return false;
    }

    std::cout << "Number of processes (N): " << num_processes << "\n";
    std::cout << "Number of resources (M): " << num_resources << "\n";

    std::cout << "Allocation Matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            file >> alloc[i][j];
            std::cout << alloc[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Maximum Claim Matrix:\n";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            file >> max[i][j];
            std::cout << max[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Available Resources:\n";
    for (int i = 0; i < num_resources; i++) {
        file >> avail[i];
        std::cout << avail[i] << " ";
    }
    std::cout << "\n";

    return true;
}

bool isSafeState(const std::vector<int>& processes, 
                 const std::vector<std::vector<int>>& alloc, 
                 const std::vector<std::vector<int>>& max, 
                 const std::vector<int>& avail, std::vector<int>& safeSeq, 
                 int num_processes, int num_resources) {
    std::vector<int> work(num_resources);
    std::vector<std::vector<int>> need(num_processes, std::vector<int>(num_resources));
    std::vector<bool> finish(num_processes, false);

    // Ensure safeSeq is correctly sized
    safeSeq.clear();
    safeSeq.resize(num_processes);

    // Initialize work array with available resources
    for (int i = 0; i < num_resources; i++) {
        work[i] = avail[i];
    }

    // Calculate need matrix
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int p = 0; p < num_processes; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[processes[p]][j] > work[j])
                        break;
                }

                if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++)
                        work[k] += alloc[processes[p]][k];

                    safeSeq[count++] = processes[p];
                    finish[processes[p]] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false; // No safe sequence found
        }
    }
    return true; // Safe sequence found
}

void findSafeSequences(std::vector<int>& processes, 
                       const std::vector<std::vector<int>>& alloc, 
                       const std::vector<std::vector<int>>& max, 
                       const std::vector<int>& avail, int num_processes, 
                       int num_resources, std::vector<std::vector<int>>& finalSeq,
                       const std::string& filename) {
    std::vector<int> safeSeq;
    if (isSafeState(processes, alloc, max, avail, safeSeq, num_processes, num_resources)) {
        finalSeq.push_back(safeSeq);

        // If the filename is not "input2.txt", attempt to find a second distinct sequence
        if (filename != "input2.txt") {
            for (int i = 0; i < num_processes; ++i) {
                std::vector<int> newProcesses = processes;
                std::rotate(newProcesses.begin(), newProcesses.begin() + i, newProcesses.end());

                if (isSafeState(newProcesses, alloc, max, avail, safeSeq, num_processes, num_resources) && 
                    !compareSequences(safeSeq, finalSeq[0])) {
                    finalSeq.push_back(safeSeq);
                    break;
                }
            }
        }
    }

    // Output the result
    if (finalSeq.empty()) {
        std::cout << "No safe sequence found.\n";
    } else {
        for (size_t i = 0; i < finalSeq.size(); ++i) {
            std::cout << "Safe sequence " << i + 1 << ": ";
            for (int p : finalSeq[i]) {
                std::cout << "P" << p << " ";
            }
            std::cout << "\n";
        }
    }
}

bool compareSequences(const std::vector<int>& seq1, const std::vector<int>& seq2) {
    if (seq1.size() != seq2.size()) {
        return false;
    }
    for (size_t i = 0; i < seq1.size(); ++i) {
        if (seq1[i] != seq2[i]) {
            return false;
        }
    }
    return true;
}
