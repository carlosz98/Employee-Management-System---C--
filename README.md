# Employee Management System
[![Ask DeepWiki](https://devin.ai/assets/askdeepwiki.png)](https://deepwiki.com/carlosz98/Employee-Management-System---C--)

## Overview
This is a comprehensive command-line Employee Management System written in C++. It allows users to perform standard CRUD (Create, Read, Update, Delete) operations on employee records. The project demonstrates a wide range of C++ concepts, including object-oriented programming, file handling, exception handling, and multithreading.

## Features
- **Add, Update, & Delete Employees**: Perform essential management tasks on employee records.
- **Display All Records**: View a list of all employees currently in the system.
- **Data Persistence**: Save the employee database to a comma-separated text file (`employees.txt`) and load it on startup.
- **Object-Oriented Design**: Utilizes classes (`Employee`, `Manager`), inheritance (`Manager` inherits from `Employee`), and polymorphism (virtual `displayDetails` function).
- **Custom Exception Handling**: Implements `InvalidInputException` and `FileIOException` for robust error management.
- **Multithreading Support**: Includes functions to demonstrate concurrent employee additions and updates.
- **Interactive CLI**: A simple and intuitive menu-driven command-line interface for ease of use.

## Technologies & Concepts Demonstrated
- **Language**: C++
- **Core Concepts**:
  - Pointers and References
  - Structures (`struct`) and Classes (`class`)
  - Constructors and Destructors
  - Encapsulation and Access Modifiers
  - Inheritance and Polymorphism
  - Standard Template Library (STL), specifically `std::vector`
  - Exception Handling (`try`, `catch`, custom exception classes)
  - Multithreading (`std::thread`)
  - File I/O (`fstream`)

## Getting Started

### Prerequisites
- A C++ compiler that supports the C++11 standard or later (e.g., GCC/g++).
- The pthreads library for multithreading support (usually included with GCC/g++ on Linux).

### Compilation
1.  Clone the repository or download the `final.cpp` file.
2.  Open your terminal or command prompt and navigate to the directory containing the file.
3.  Compile the program using the following command. The `-pthread` flag is necessary for the multithreading features.
    ```bash
    g++ final.cpp -o employee_management -std=c++11 -pthread
    ```

### Execution
Run the compiled application from your terminal:
```bash
./employee_management
```
The program will automatically attempt to load existing records from `employees.txt` if the file exists in the same directory.

## Usage
Once the program is running, you will be presented with the main menu. Enter the number corresponding to the action you wish to perform.

```
1. Add Employee
2. Update Employee
3. Delete Employee
4. Display All Employees
5. Save to File
6. Load from File
7. Exit
Enter your choice:
```

- **Add Employee**: Prompts for Employee ID, Name, Position, Salary, and Department to create a new employee record.
- **Update Employee**: Asks for the ID of an existing employee and then prompts for the new details to update the record.
- **Delete Employee**: Deletes an employee record based on the provided Employee ID.
- **Display All Employees**: Prints the details of all employees currently stored in memory.
- **Save to File**: Saves all current employee records to `employees.txt`.
- **Load from File**: Clears current records and loads them from `employees.txt`.
- **Exit**: Terminates the application.
