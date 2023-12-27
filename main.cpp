#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
    string caseNumber;
    string incidentPrimary;
    string gunshotInjury;
    string homicideVictimFirstName;
    string homicideVictimLastName;
    Node(string caseNum, string incPrimary, string gunInjury, string firstName, string lastName)
            :caseNumber(caseNum),
            incidentPrimary(incPrimary),
            gunshotInjury(gunInjury),
            homicideVictimFirstName(firstName),
            homicideVictimLastName(lastName),
            left(nullptr),
            right(nullptr){}
    Node* left;
    Node* right;
};

void insert(Node*& root, string caseNum, string incPrimary, string gunInjury, string firstName, string lastName) {
    if (!root) {
        root = new Node(caseNum, incPrimary, gunInjury, firstName, lastName);
        return;
    }
    if (caseNum < root->caseNumber) {
        insert(root->left, caseNum, incPrimary, gunInjury, firstName, lastName);
    } else {
        insert(root->right, caseNum, incPrimary, gunInjury, firstName, lastName);
    }
}

void printCaseNumbers(Node* root) {
    if (root) {
        printCaseNumbers(root->left);
        cout << root->caseNumber << endl;
        printCaseNumbers(root->right);
    }
}

Node* search(Node* root, string key) {
    if (!root || root->caseNumber == key) {
        return root;
    }
    if (key < root->caseNumber) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

int main() {
    string filename = "C:\\Users\\quarl\\CLionProjects\\CSE_320_projectPart2\\projectDataset.csv";
    ifstream file(filename);
    string header;
    getline(file, header);
    Node* root = nullptr;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string caseNum;
        string incPrimary;
        string gunInjury;
        string firstName;
        string lastName;
        getline(iss, caseNum, ',');
        getline(iss, incPrimary, ',');
        getline(iss, gunInjury, ',');
        getline(iss, firstName, ',');
        getline(iss, lastName, ',');
        insert(root, caseNum, incPrimary, gunInjury, firstName, lastName);
    }
    cout << "Case Numbers: " << endl;
    printCaseNumbers(root);
    file.close();
    cout << "Enter a Case Number to search: ";
    string searchKey;
    cin >> searchKey;
    Node* result = search(root, searchKey);
    if (result) {
        cout << "Case Number: " << result->caseNumber << ", "
             << "Incident Primary: " << result->incidentPrimary << ", "
             << "Gunshot Injury: " << result->gunshotInjury << ", "
             << "Victim Name: " << result->homicideVictimFirstName << " " << result->homicideVictimLastName
             << endl;
    } else {
        cout << "Case Number not found." << endl;
    }
    return 0;
}