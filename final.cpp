#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <stdexcept>

using namespace std;

// Step 1
struct EmployeeData {
    int employeeID;
    string employeeName;
    string employeePosition;
    double employeeSalary;
    string employeeDepartment;
};

// Step 2
class Employee {
private:
    EmployeeData data;
public:
    Employee() : data{ 0, "", "", 0.0, "" } {} // Default constructor
    Employee(int id, string name, string position, double salary, string department)
        : data{ id, name, position, salary, department } {} // Parameterized constructor

    // Getters
    int getEmployeeID() const { return data.employeeID; }
    string getName() const { return data.employeeName; }
    string getPosition() const { return data.employeePosition; }
    double getSalary() const { return data.employeeSalary; }
    string getDepartment() const { return data.employeeDepartment; }

    // Setters
    void setEmployeeID(int id) { data.employeeID = id; }
    void setName(string name) { data.employeeName = name; }
    void setPosition(string position) { data.employeePosition = position; }
    void setSalary(double salary) { data.employeeSalary = salary; }
    void setDepartment(string department) { data.employeeDepartment = department; }

    // Display details
    virtual void displayDetails() const {
        cout << "Employee ID: " << data.employeeID << endl;
        cout << "Name: " << data.employeeName << endl;
        cout << "Position: " << data.employeePosition << endl;
        cout << "Salary: " << data.employeeSalary << endl;
        cout << "Department: " << data.employeeDepartment << endl;
    }
};

// Step 3: Define Manager class
class Manager : public Employee {
private:
    int teamSize;
    string projectName;

public:
    Manager() : Employee(), teamSize(0), projectName("") {}
    Manager(int id, string name, string position, double salary, string department, int tSize, string pName)
        : Employee(id, name, position, salary, department), teamSize(tSize), projectName(pName) {
    }

    int getTeamSize() const { return teamSize; }
    string getProjectName() const { return projectName; }

    void setTeamSize(int tSize) { teamSize = tSize; }
    void setProjectName(string pName) { projectName = pName; }

    // Override display function
    void displayDetails() const override {
        Employee::displayDetails();
        cout << "Team Size: " << teamSize << endl;
        cout << "Project Name: " << projectName << endl;
    }
};

// Step 4: Define Exception classes
class InvalidInputException : public exception {
    const char* what() const noexcept override {
        return "Invalid input provided.";
    }
};

class FileIOException : public exception {
    const char* what() const noexcept override {
        return "File I/O error.";
    }
};

// Step 5: Define EmployeeManager class
class EmployeeManager {
private:
    vector<Employee*> employeeList;

public:
    ~EmployeeManager() {
        for (auto emp : employeeList) {
            delete emp;
        }
    }

    void addEmployee(Employee* emp) {
        employeeList.push_back(emp);
    }

    void updateEmployee(int id, Employee* updatedEmp) {
        for (size_t i = 0; i < employeeList.size(); ++i) {
            if (employeeList[i]->getEmployeeID() == id) {
                delete employeeList[i];
                employeeList[i] = updatedEmp;
                return;
            }
        }
        throw InvalidInputException();
    }

    void deleteEmployee(int id) {
        for (size_t i = 0; i < employeeList.size(); ++i) {
            if (employeeList[i]->getEmployeeID() == id) {
                delete employeeList[i];
                employeeList.erase(employeeList.begin() + i);
                return;
            }
        }
        throw InvalidInputException();
    }

    Employee* getEmployeeByID(int id) const {
        for (const auto& emp : employeeList) {
            if (emp->getEmployeeID() == id) {
                return emp;
            }
        }
        throw InvalidInputException();
    }

    void displayAllEmployees() const {
        for (const auto& emp : employeeList) {
            emp->displayDetails();
            cout << "------------------------" << endl;
        }
    }

    // File handling
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            throw FileIOException();
        }
        for (const auto& emp : employeeList) {
            outFile << emp->getEmployeeID() << "," << emp->getName() << "," << emp->getPosition() << ","
                << emp->getSalary() << "," << emp->getDepartment() << endl;
        }
        outFile.close();
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            throw FileIOException();
        }
        employeeList.clear();
        string line;
        while (getline(inFile, line)) {
            size_t pos = 0;
            string token;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // Add the last token

            if (tokens.size() == 5) {
                int id = stoi(tokens[0]);
                string name = tokens[1];
                string position = tokens[2];
                double salary = stod(tokens[3]);
                string department = tokens[4];
                employeeList.push_back(new Employee(id, name, position, salary, department));
            }
        }
        inFile.close();
    }
};

// Step 6: Define multithreading functions
void addMultipleEmployees(EmployeeManager& manager, const vector<Employee*>& newEmployees) {
    for (const auto& emp : newEmployees) {
        manager.addEmployee(emp);
    }
}

void concurrentOperations(EmployeeManager& manager) {
    vector<Employee*> newEmployees = {
        new Employee(1, "Carlos Zabala", "Programmer", 80000, "IT"),
        new Employee(2, "Carolina Lerma", "Designer", 65000, "Design")
    };

    thread t1(addMultipleEmployees, ref(manager), newEmployees);
    thread t2(&EmployeeManager::updateEmployee, &manager, 1, new Employee(1, "Carlos Zabala", "Senior Developer", 100000, "IT"));

    t1.join();
    t2.join();
}

// Step 7: Define main menu function
void mainMenu(EmployeeManager& manager) {
    bool isRunning = true;
    while (isRunning) {
        cout << "1. Add Employee" << endl;
        cout << "2. Update Employee" << endl;
        cout << "3. Delete Employee" << endl;
        cout << "4. Display All Employees" << endl;
        cout << "5. Save to File" << endl;
        cout << "6. Load from File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        int inputChoice;
        cin >> inputChoice;

        // Validate user input
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cerr << "Invalid input. Please enter a number between 1 and 7." << endl;
            continue;
        }

        try {
            switch (inputChoice) {
            case 1: {
                int id;
                string name, position, department;
                double salary;
                cout << "Enter Employee ID: ";
                cin >> id;
                if (id < 0) throw InvalidInputException();
                cout << "Enter Name: ";
                cin.ignore(); // Ignore newline character left in the buffer
                getline(cin, name);
                cout << "Enter Position: ";
                getline(cin, position);
                cout << "Enter Salary: ";
                cin >> salary;
                if (salary < 0) throw InvalidInputException();
                cout << "Enter Department: ";
                cin.ignore(); // Ignore newline character left in the buffer
                getline(cin, department);
                manager.addEmployee(new Employee(id, name, position, salary, department));
                break;
            }
            case 2: {
                int id;
                cout << "Enter Employee ID to update: ";
                cin >> id;
                int newID;
                string name, position, department;
                double salary;
                cout << "Enter New Employee ID: ";
                cin >> newID;
                if (newID < 0) throw InvalidInputException();
                cout << "Enter Name: ";
                cin.ignore(); // Ignore newline character left in the buffer
                getline(cin, name);
                cout << "Enter Position: ";
                getline(cin, position);
                cout << "Enter Salary: ";
                cin >> salary;
                if (salary < 0) throw InvalidInputException();
                cout << "Enter Department: ";
                cin.ignore(); // Ignore newline character left in the buffer
                getline(cin, department);
                manager.updateEmployee(id, new Employee(newID, name, position, salary, department));
                break;
            }
            case 3: {
                int id;
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                manager.deleteEmployee(id);
                break;
            }
            case 4:
                manager.displayAllEmployees();
                break;
            case 5:
                manager.saveToFile("employees.txt");
                break;
            case 6:
                manager.loadFromFile("employees.txt");
                break;
            case 7:
                isRunning = false;
                break;
            default:
                throw InvalidInputException();
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
}

// Step 8: Define main function
int main() {
    EmployeeManager manager;
    try {
        manager.loadFromFile("employees.txt");
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    mainMenu(manager);

    return 0;
}