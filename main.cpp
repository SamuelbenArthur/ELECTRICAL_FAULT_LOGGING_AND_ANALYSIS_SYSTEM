#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// ============================================================
// Class: FaultRecord
// Represents a single electrical fault entry with validation,
// classification, display, and file-saving capabilities.
// ============================================================
class FaultRecord {
private:
    string faultID;
    string location;
    string faultType;
    double voltageReading;
    double currentReading;
    string actionTaken;
    string severity;

public:
    // Constructor
    FaultRecord() : voltageReading(0.0), currentReading(0.0) {}

    // --------------------------------------------------------
    // setFaultDetails: Collects all fault information from user
    // --------------------------------------------------------
    void setFaultDetails() {
        cout << "\n----------------------------------------" << endl;
        cout << "Enter Fault ID: ";
        cin >> faultID;
        cin.ignore(); // clear buffer for getline

        cout << "Enter Location: ";
        getline(cin, location);

        cout << "Enter Fault Type (e.g., Short Circuit, Burning Smell, "
             << "Electric Shock, Loose Connection, Flickering Light, "
             << "Damaged Socket, Routine Complaint): ";
        getline(cin, faultType);

        cout << "Enter Voltage Reading (V): ";
        cin >> voltageReading;

        cout << "Enter Current Reading (A): ";
        cin >> currentReading;
        cin.ignore();

        cout << "Enter Action Taken: ";
        getline(cin, actionTaken);
    }

    // --------------------------------------------------------
    // validateReadings: Ensures voltage and current are non-negative
    // --------------------------------------------------------
    bool validateReadings() const {
        if (voltageReading < 0 || currentReading < 0) {
            return false;
        }
        return true;
    }

    // --------------------------------------------------------
    // classifyFault: Determines severity based on project rules
    // --------------------------------------------------------
    void classifyFault() {
        // Convert fault type to lowercase for robust comparison
        string lowerType = faultType;
        for (char &c : lowerType) {
            c = tolower(c);
        }

        // Rule 1: Critical faults — short circuit, burning smell, electric shock
        if (lowerType.find("short circuit") != string::npos ||
            lowerType.find("burning smell") != string::npos ||
            lowerType.find("electric shock") != string::npos) {
            severity = "Critical";
            return;
        }

        // Rule 2: Serious faults — voltage out of range OR current above safe limit (15A)
        if (voltageReading < 180.0 || voltageReading > 250.0 || currentReading > 15.0) {
            severity = "Serious";
            return;
        }

        // Rule 3: Moderate faults — loose connection, flickering light, damaged socket
        if (lowerType.find("loose connection") != string::npos ||
            lowerType.find("flickering light") != string::npos ||
            lowerType.find("damaged socket") != string::npos) {
            severity = "Moderate";
            return;
        }

        // Rule 4: Minor faults — routine complaint with normal readings
        if (lowerType.find("routine") != string::npos ||
            lowerType.find("complaint") != string::npos) {
            severity = "Minor";
            return;
        }

        // Default: if normal readings but not routine, classify as Moderate
        if (voltageReading >= 180.0 && voltageReading <= 250.0 && currentReading <= 15.0) {
            severity = "Moderate";
        } else {
            severity = "Serious";
        }
    }

    // --------------------------------------------------------
    // displayFaultReport: Shows formatted fault details
    // --------------------------------------------------------
    void displayFaultReport() const {
        cout << left << setw(20) << "Fault ID:" << faultID << endl;
        cout << left << setw(20) << "Location:" << location << endl;
        cout << left << setw(20) << "Fault Type:" << faultType << endl;
        cout << left << setw(20) << "Voltage Reading:" << voltageReading << " V" << endl;
        cout << left << setw(20) << "Current Reading:" << currentReading << " A" << endl;
        cout << left << setw(20) << "Action Taken:" << actionTaken << endl;
        cout << left << setw(20) << "Severity:" << severity << endl;
        cout << "----------------------------------------" << endl;
    }

    // --------------------------------------------------------
    // saveFaultReport: Writes fault details to output file
    // --------------------------------------------------------
    void saveFaultReport(ofstream &file) const {
        file << left << setw(20) << "Fault ID:" << faultID << endl;
        file << left << setw(20) << "Location:" << location << endl;
        file << left << setw(20) << "Fault Type:" << faultType << endl;
        file << left << setw(20) << "Voltage Reading:" << voltageReading << " V" << endl;
        file << left << setw(20) << "Current Reading:" << currentReading << " A" << endl;
        file << left << setw(20) << "Action Taken:" << actionTaken << endl;
        file << left << setw(20) << "Severity:" << severity << endl;
        file << "----------------------------------------" << endl;
    }

    // Getters for summary statistics
    string getSeverity() const { return severity; }
    string getFaultID() const { return faultID; }
};

// ============================================================
// Helper Functions
// ============================================================

void displayWelcomeMessage() {
    cout << "\n============================================================" << endl;
    cout << "    ELECTRICAL FAULT LOGGING AND ANALYSIS SYSTEM" << endl;
    cout << "    ACCRA TECHNICAL UNIVERSITY - BEE 208 C++ PROJECT" << endl;
    cout << "============================================================" << endl;
}

void displayMenu() {
    cout << "\n-------------------- MAIN MENU --------------------" << endl;
    cout << "1. Add New Fault Record(s)" << endl;
    cout << "2. View All Recorded Faults" << endl;
    cout << "3. Generate & Save Report" << endl;
    cout << "4. Exit System" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter your choice (1-4): ";
}

void displaySummary(const vector<FaultRecord> &records) {
    int total = records.size();
    int critical = 0, serious = 0, moderate = 0, minor = 0;

    for (const auto &rec : records) {
        string sev = rec.getSeverity();
        if (sev == "Critical") critical++;
        else if (sev == "Serious") serious++;
        else if (sev == "Moderate") moderate++;
        else if (sev == "Minor") minor++;
    }

    cout << "\n==================== FAULT SUMMARY ====================" << endl;
    cout << "Total Faults Recorded: " << total << endl;
    cout << "Critical Faults:       " << critical << endl;
    cout << "Serious Faults:        " << serious << endl;
    cout << "Moderate Faults:       " << moderate << endl;
    cout << "Minor Faults:          " << minor << endl;
    cout << "=======================================================" << endl;
}

void saveFullReport(const vector<FaultRecord> &records) {
    ofstream outFile("electrical_fault_report.txt");

    if (!outFile) {
        cout << "Error: Could not create output file!" << endl;
        return;
    }

    outFile << "============================================================" << endl;
    outFile << "       ELECTRICAL FAULT LOGGING AND ANALYSIS REPORT" << endl;
    outFile << "       ACCRA TECHNICAL UNIVERSITY - BEE 208 PROJECT" << endl;
    outFile << "============================================================" << endl;
    outFile << "\nGenerated Report" << endl;
    outFile << "Total Records: " << records.size() << endl;
    outFile << "\n-------------------- DETAILED FAULT RECORDS --------------------" << endl;

    int total = records.size();
    int critical = 0, serious = 0, moderate = 0, minor = 0;

    for (size_t i = 0; i < records.size(); ++i) {
        outFile << "\nFault " << (i + 1) << endl;
        records[i].saveFaultReport(outFile);

        string sev = records[i].getSeverity();
        if (sev == "Critical") critical++;
        else if (sev == "Serious") serious++;
        else if (sev == "Moderate") moderate++;
        else if (sev == "Minor") minor++;
    }

    outFile << "\n==================== FAULT SUMMARY ====================" << endl;
    outFile << "Total Faults Recorded: " << total << endl;
    outFile << "Critical Faults:       " << critical << endl;
    outFile << "Serious Faults:        " << serious << endl;
    outFile << "Moderate Faults:       " << moderate << endl;
    outFile << "Minor Faults:          " << minor << endl;
    outFile << "=======================================================" << endl;
    outFile << "\nEnd of Report" << endl;

    outFile.close();
    cout << "\n[SUCCESS] Report saved as 'electrical_fault_report.txt'" << endl;
}

// ============================================================
// Main Function
// ============================================================
int main() {
    vector<FaultRecord> faultRecords;
    int choice;
    bool running = true;

    displayWelcomeMessage();

    while (running) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[ERROR] Invalid input. Please enter a number (1-4)." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                int numFaults;
                cout << "\nEnter number of fault records to add: ";
                cin >> numFaults;

                if (cin.fail() || numFaults <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] Please enter a valid positive number." << endl;
                    break;
                }

                for (int i = 0; i < numFaults; ++i) {
                    cout << "\n>>> Fault " << (faultRecords.size() + 1) << " <<<" << endl;
                    FaultRecord newRecord;
                    newRecord.setFaultDetails();

                    if (!newRecord.validateReadings()) {
                        cout << "[INVALID] Voltage or current cannot be negative. Record rejected." << endl;
                        continue;
                    }

                    newRecord.classifyFault();
                    faultRecords.push_back(newRecord);

                    cout << "\n[SUCCESS] Fault recorded. Severity: ";
                    // We need a way to get severity after classification
                    // Since classifyFault sets it, we can display via a temporary trick
                    // Actually, let's just re-display the record
                    newRecord.displayFaultReport();
                }
                break;
            }

            case 2: {
                if (faultRecords.empty()) {
                    cout << "\n[INFO] No fault records found. Please add records first." << endl;
                } else {
                    cout << "\n================ ALL RECORDED FAULTS ================" << endl;
                    for (size_t i = 0; i < faultRecords.size(); ++i) {
                        cout << "\nFault " << (i + 1) << endl;
                        faultRecords[i].displayFaultReport();
                    }
                    displaySummary(faultRecords);
                }
                break;
            }

            case 3: {
                if (faultRecords.empty()) {
                    cout << "\n[INFO] No records to save. Please add fault records first." << endl;
                } else {
                    saveFullReport(faultRecords);
                }
                break;
            }

            case 4: {
                cout << "\nThank you for using the Electrical Fault Logging and Analysis System." << endl;
                cout << "Goodbye!" << endl;
                running = false;
                break;
            }

            default:
                cout << "\n[ERROR] Invalid choice. Please select 1-4." << endl;
        }
    }

    return 0;
}
