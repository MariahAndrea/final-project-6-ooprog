#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>
#include <map>
using namespace std;
// Function to handle user input for a positive integer
int getValidIntegerInput(const string& prompt) {
    string input;
    int value;

    while (true) {
        cout << prompt;
        getline(cin, input);

        try {
            // Ensure the input contains only digits
            bool isValid = true;
            for (char ch : input) {
                if (!isdigit(ch)) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid || input.empty()) {
                throw invalid_argument("\t\033[31mInvalid input. Please enter a valid integer.\033[0m");
            }

            value = stoi(input); // Convert input to integer
            return value;
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

// Function to handle user input for a string 
string getValidStringInput(const string& prompt) {
    string input;
    while (true) {
        try {
            cout << prompt;
            getline(cin, input);

            // Check if the input is empty
            if (input.empty()) {
                throw invalid_argument("\t\033[31mInput cannot be empty. Please enter a valid value.\033[0m");
            }
            return input; // Return the valid input
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
}

string convertToUpper(const string& input) {
    string result;
    for (char c : input) {
        result += toupper(c);
    }
    return result;
}

void validateDepartmentAndProgram(string& dept, string& prog) {
    // Validate department input
    do {
        dept = getValidStringInput("\n\tEnter Department: \n\t   - CITE (College of Information Technology and Engineering)\n\t   - CBEAM (College of Business, Economics, Accountancy and Management)\n\t   - CEAS (College of Education, Arts and Sciences)\n\t     --> ");
        dept = convertToUpper(dept);
        if (dept != "CITE" && dept != "CBEAM" && dept != "CEAS") {
            cout << "\t\033[31mInvalid Department. Please try again.\033[0m\n";
        }
    } while (dept != "CITE" && dept != "CBEAM" && dept != "CEAS");

    // Validate program input based on department
    do {
        if (dept == "CITE") {
            prog = getValidStringInput("\n\tEnter Program: \n\t   - BSCS (Bachelor of Science in Computer Science)\n\t   - BSIT (Bachelor of Science in Information Technology) \n\t   - BSARCHI (Bachelor of Science in Architecture) \n\t     --> ");
            prog = convertToUpper(prog);
            
        } else if (dept == "CBEAM") {
            prog = getValidStringInput("\n\tEnter Program: \n\t   - BSA (Bachelor of Science in Accountancy)\n\t   - BSLM (Bachelor of Science in Legal Management) \n\t   - BSENTREP (Bachelor of Science in Entrepreneurship) \n\t     --> ");
            prog = convertToUpper(prog);
            
        } else if (dept == "CEAS") {
            prog = getValidStringInput("\n\tEnter Program: \n\t   - BSMMA (Bachelor of Science in Multimedia Arts)\n\t   - BSBIO (Bachelor of Science in Biology) \n\t   - BSPSYCH (Bachelor of Science in Psychology) \n\t     --> ");
            prog = convertToUpper(prog);
            
        }
        if ((dept == "CITE" && prog != "BSCS" && prog != "BSIT" && prog != "BSARCHI") ||
            (dept == "CBEAM" && prog != "BSA" && prog != "BSLM" && prog != "BSENTREP") ||
            (dept == "CEAS" && prog != "BSMMA" && prog != "BSBIO" && prog != "BSPSYCH")) {
            cout << "\t\033[31mInvalid Program. Please try again.\033[0m\n";
            prog = ""; // Clear invalid program to repeat input
        }
    } while (prog.empty());
}

class Professor;

class Course {
private:
    string courseCode;
    string courseName;
    int courseUnit;
    string courseDept;
    string courseProg;
    int courseYear;
    Professor* courseProfessor;
    vector<string> enrolledStudents; 

public:
    // Parameterized constructor
    Course(string c, string n, int u, string cDept, string cProg, int cYr)
        : courseCode(c), courseName(n), courseUnit(u), courseDept(cDept), courseProg(cProg), courseYear(cYr), courseProfessor(nullptr) {}

    // Getters
    string getCourseCode() const { return courseCode; }
    string getCourseName() const { return courseName; }
    int getCourseUnit() const { return courseUnit; }
    string getCourseDept() const { return courseDept; }
    string getCourseProg() const { return courseProg; }
    int getCourseYear() const { return courseYear; }
    Professor* getProfessor() const { return courseProfessor; }

    // Setters
    void setCourseCode(const string &c) { courseCode = c; }
    void setCourseName(const string &n) { courseName = n; }
    void setCourseUnit(int u) { courseUnit = u; }
    void setCourseDept(const string &d) { courseDept = d; }
    void setCourseProg(const string &p) { courseProg = p; }
    void setCourseYear(int y) { courseYear = y; }
    void setProfessor(Professor& professor) { 
        courseProfessor = &professor; 
    }
    
    void addStudent(const string& studentName) {
    enrolledStudents.push_back(studentName);
	}

    // Get enrolled students
    vector<string> getEnrolledStudents() const {
        return enrolledStudents;
    }

    // Display course info
    void displayCourseInfo() const {
        cout << "\t" 
			 << left << setw(20) << courseCode
             << setw(50) << courseName
             << right << setw(10) << courseUnit
             << endl;
    }

    // Convert string to uppercase
    string convertToUpper(string str) const {
        for (auto& c : str) {
            c = toupper(c);
        }
        return str;
    }

    virtual void displayCourses(const string dept, string program, int year) const {}

    virtual ~Course() = default; // Virtual destructor for base class
};

class CurriculumStrategy {
public:
    virtual void viewCurriculum(const string& dept, const string& program) const = 0;
    virtual ~CurriculumStrategy() = default;
};

// Derived class to store all courses
class AllCourses {
private:
	CurriculumStrategy* curriculumStrategy;

    vector<Course*> allCourses;
    static AllCourses* instance;

    	AllCourses() { 
    // Adding BSCS courses for Year 1
    allCourses.push_back(new Course("CMSC 12", "Foundations of Computer Science", 3, "CITE", "BSCS", 1));
    allCourses.push_back(new Course("CMSC 56", "Discrete Mathematics I", 3, "CITE", "BSCS", 1));
    allCourses.push_back(new Course("ETHICS 1", "Ethics and Moral Reasoning", 3, "CITE", "BSCS", 1));
    allCourses.push_back(new Course("MATH 27", "Analytic Geometry & Calculus II", 3, "CITE", "BSCS", 1));
    allCourses.push_back(new Course("STS 1", "Science, Technology and Society", 3, "CITE", "BSCS", 1));
    allCourses.push_back(new Course("HK 11", "Wellness and Basic Injury Management", 3, "CITE", "BSCS", 1));

    // Year 2 courses for BSCS
    allCourses.push_back(new Course("CMSC 122", "Data Structures and Algorithms", 3, "CITE", "BSCS", 2));
    allCourses.push_back(new Course("CMSC 128", "Computer Organization", 3, "CITE", "BSCS", 2));
    allCourses.push_back(new Course("MATH 33", "Mathematical Methods for Computer Science", 3, "CITE", "BSCS", 2));
    allCourses.push_back(new Course("CS 130", "Software Engineering", 3, "CITE", "BSCS", 2));
    allCourses.push_back(new Course("PHYS 11", "Physics for Engineers", 3, "CITE", "BSCS", 2));
    allCourses.push_back(new Course("PE 1", "Physical Education", 3, "CITE", "BSCS", 2));

    // Year 3 courses for BSCS
    allCourses.push_back(new Course("CMSC 135", "Database Systems", 3, "CITE", "BSCS", 3));
    allCourses.push_back(new Course("CMSC 142", "Operating Systems", 3, "CITE", "BSCS", 3));
    allCourses.push_back(new Course("CMSC 150", "Web Development", 3, "CITE", "BSCS", 3));
    allCourses.push_back(new Course("MATH 42", "Discrete Structures", 3, "CITE", "BSCS", 3));
    allCourses.push_back(new Course("PE 2", "Physical Education", 3, "CITE", "BSCS", 3));
    allCourses.push_back(new Course("HK 12", "Health & Wellness", 3, "CITE", "BSCS", 3));

    // Year 4 courses for BSCS
    allCourses.push_back(new Course("CMSC 180", "Capstone Project I", 3, "CITE", "BSCS", 4));
    allCourses.push_back(new Course("CMSC 181", "Capstone Project II", 3, "CITE", "BSCS", 4));
    allCourses.push_back(new Course("CMSC 143", "Computer Networks", 3, "CITE", "BSCS", 4));
    allCourses.push_back(new Course("CMSC 120", "Theoretical Computer Science", 3, "CITE", "BSCS", 4));
    allCourses.push_back(new Course("CS 131", "Advanced Software Engineering", 3, "CITE", "BSCS", 4));
    allCourses.push_back(new Course("PE 3", "Physical Education", 3, "CITE", "BSCS", 4));

    // Adding BSIT courses for Year 1
    allCourses.push_back(new Course("CMSC 12", "Foundations of Computer Science", 3, "CITE", "BSIT", 1));
    allCourses.push_back(new Course("CMSC 56", "Discrete Mathematics I", 3, "CITE", "BSIT", 1));
    allCourses.push_back(new Course("ETHICS 1", "Ethics and Moral Reasoning", 3, "CITE", "BSIT", 1));
    allCourses.push_back(new Course("MATH 27", "Analytic Geometry & Calculus II", 3, "CITE", "BSIT", 1));
    allCourses.push_back(new Course("STS 1", "Science, Technology and Society", 3, "CITE", "BSIT", 1));
    allCourses.push_back(new Course("HK 11", "Wellness and Basic Injury Management", 3, "CITE", "BSIT", 1));

    // Year 2 courses for BSIT
    allCourses.push_back(new Course("CMSC 122", "Data Structures and Algorithms", 3, "CITE", "BSIT", 2));
    allCourses.push_back(new Course("CMSC 128", "Computer Organization", 3, "CITE", "BSIT", 2));
    allCourses.push_back(new Course("MATH 33", "Mathematical Methods for Computer Science", 3, "CITE", "BSIT", 2));
    allCourses.push_back(new Course("CS 130", "Software Engineering", 3, "CITE", "BSIT", 2));
    allCourses.push_back(new Course("PHYS 11", "Physics for Engineers", 3, "CITE", "BSIT", 2));
    allCourses.push_back(new Course("PE 1", "Physical Education", 3, "CITE", "BSIT", 2));

    // Year 3 courses for BSIT
    allCourses.push_back(new Course("CMSC 135", "Database Systems", 3, "CITE", "BSIT", 3));
    allCourses.push_back(new Course("CMSC 142", "Operating Systems", 3, "CITE", "BSIT", 3));
    allCourses.push_back(new Course("CMSC 150", "Web Development", 3, "CITE", "BSIT", 3));
    allCourses.push_back(new Course("MATH 42", "Discrete Structures", 3, "CITE", "BSIT", 3));
    allCourses.push_back(new Course("PE 2", "Physical Education", 3, "CITE", "BSIT", 3));
    allCourses.push_back(new Course("HK 12", "Health & Wellness", 3, "CITE", "BSIT", 3));

    // Year 4 courses for BSIT
    allCourses.push_back(new Course("CMSC 180", "Capstone Project I", 3, "CITE", "BSIT", 4));
    allCourses.push_back(new Course("CMSC 181", "Capstone Project II", 3, "CITE", "BSIT", 4));
    allCourses.push_back(new Course("CMSC 143", "Computer Networks", 3, "CITE", "BSIT", 4));
    allCourses.push_back(new Course("CMSC 120", "Theoretical Computer Science", 3, "CITE", "BSIT", 4));
    allCourses.push_back(new Course("CS 131", "Advanced Software Engineering", 3, "CITE", "BSIT", 4));
    allCourses.push_back(new Course("PE 3", "Physical Education", 3, "CITE", "BSIT", 4));

    // Adding BSARCHI courses for Year 1
    allCourses.push_back(new Course("ARCHI 10", "Architectural Design 1", 3, "CITE", "BSARCHI", 1));
    allCourses.push_back(new Course("MATH 27", "Analytic Geometry & Calculus II", 3, "CITE", "BSARCHI", 1));
    allCourses.push_back(new Course("ENG 1", "English for Academic Purposes", 3, "CITE", "BSARCHI", 1));
    allCourses.push_back(new Course("HIST 1", "History of Architecture", 3, "CITE", "BSARCHI", 1));
    allCourses.push_back(new Course("ETHICS 1", "Ethics and Moral Reasoning", 3, "CITE", "BSARCHI", 1));
    allCourses.push_back(new Course("PE 1", "Physical Education", 3, "CITE", "BSARCHI", 1));

    // Year 2 courses for BSARCHI
    allCourses.push_back(new Course("ARCHI 20", "Architectural Design 2", 3, "CITE", "BSARCHI", 2));
    allCourses.push_back(new Course("MATH 33", "Mathematical Methods for Architecture", 3, "CITE", "BSARCHI", 2));
    allCourses.push_back(new Course("PHY 11", "Physics for Architecture", 3, "CITE", "BSARCHI", 2));
    allCourses.push_back(new Course("ARCHI 21", "Building Materials and Construction", 3, "CITE", "BSARCHI", 2));
    allCourses.push_back(new Course("PHIL 2", "Philosophy of Architecture", 3, "CITE", "BSARCHI", 2));
    allCourses.push_back(new Course("PE 2", "Physical Education", 3, "CITE", "BSARCHI", 2));

   // Year 3 courses for BSARCHI 
    allCourses.push_back(new Course("ARCHI 30", "Architectural Design 3", 3, "CITE", "BSARCHI", 3));
    allCourses.push_back(new Course("ARCAD 28", "Computer Aided Design and Drafting", 3, "CITE", "BSARCHI", 3));
    allCourses.push_back(new Course("FUNDA 67", "Fundamentals of Community Planning", 3, "CITE", "BSARCHI", 3));
    allCourses.push_back(new Course("ARCHI 22", "Building Acoustics and Lighting System", 3, "CITE", "BSARCHI", 3));
    allCourses.push_back(new Course("ARCHI 45", "Architectural Interiors", 3, "CITE", "BSARCHI", 3));
    allCourses.push_back(new Course("PE 3", "Physical Education", 3, "CITE", "BSARCHI", 3));

   // Year 4 courses for BSARCHI
    allCourses.push_back(new Course("CMSC 180", "Capstone Project I", 3, "CITE", "BSARCHI", 4));
    allCourses.push_back(new Course("CMSC 181", "Capstone Project II", 3, "CITE", "BSARCHI", 4));
    allCourses.push_back(new Course("ARCHI 40", "Architectural Design 4", 3, "CITE", "BSARCHI", 4));
    allCourses.push_back(new Course("COMARC 54", "Community Architecture and Urban Design", 3, "CITE", "BSARCHI", 4));
    allCourses.push_back(new Course("ARHOUSE 17", "Housing", 3, "CITE", "BSARCHI", 4));
    allCourses.push_back(new Course("ARCHI 76", "Design of Complex Structures", 3, "CITE", "BSARCHI", 4));

   // Adding BSA courses for Year 1
    allCourses.push_back(new Course("MATH 13", "Business Mathematics", 3, "CBEAM", "BSA", 1));
    allCourses.push_back(new Course("COM 21", "Business Communication", 3, "CBEAM", "BSA", 1));
    allCourses.push_back(new Course("ECON 13", "Microeconomics", 3, "CBEAM", "BSA", 1));
    allCourses.push_back(new Course("STAT 110", "Statistics", 3, "CBEAM", "BSA", 1));
    allCourses.push_back(new Course("ACC 71", "Introduction to Financial Accounting", 3, "CBEAM", "BSA", 1));
    allCourses.push_back(new Course("PE 1", "Physical Education", 3, "CBEAM", "BSA", 1));

   // Year 2 courses for BSA
    allCourses.push_back(new Course("ACC 72", "Financial Accounting 2", 3, "CBEAM", "BSA", 2));
    allCourses.push_back(new Course("BLAW 12", "Business Law", 3, "CBEAM", "BSA", 2));
    allCourses.push_back(new Course("AUD 45", "Auditing Principles and Practices", 3, "CBEAM", "BSA", 2));
    allCourses.push_back(new Course("FIN 8", "Financial Management", 3, "CBEAM", "BSA", 2));
    allCourses.push_back(new Course("TAX 28", "Taxation", 3, "CBEAM", "BSA", 2));
    allCourses.push_back(new Course("PE 2", "Physical Education 2", 3, "CBEAM", "BSA", 2));

   // Year 3 courses for BSA
    allCourses.push_back(new Course("ACC 73", "Financial Accounting 3", 3, "CBEAM", "BSA", 3));
    allCourses.push_back(new Course("BLAW 22", "Business Law 2", 3, "CBEAM", "BSA", 3));
    allCourses.push_back(new Course("ENTR 61", "Entrepreneurship and Small Business Accounting", 3, "CBEAM", "BSA", 3));
    allCourses.push_back(new Course("ACC 31", "Advanced Accounting", 3, "CBEAM", "BSA", 3));
    allCourses.push_back(new Course("ECON 58", "Macroeconomics", 3, "CBEAM", "BSA", 3));
    allCourses.push_back(new Course("PE 3", "Physical Education 3", 3, "CBEAM", "BSA", 3));

   // Year 4 courses for BSA
    allCourses.push_back(new Course("CMSC 180", "Capstone Project I", 3, "CBEAM", "BSA", 4));
    allCourses.push_back(new Course("CMSC 181", "Capstone Project II", 3, "CBEAM", "BSA", 4));
    allCourses.push_back(new Course("ACC 43", "Risk Management in Accounting", 3, "CBEAM", "BSA", 4));
    allCourses.push_back(new Course("AUD 53", "Advanced Auditing", 3, "CBEAM", "BSA", 4));
    allCourses.push_back(new Course("FIN 89", "Financial Statement Analysis", 3, "CBEAM", "BSA", 4));
    allCourses.push_back(new Course("AUDTP 42", "Auditing Theory and Practice", 3, "CBEAM", "BSA", 4));
    
   // Year 1 courses for BSLM
	allCourses.push_back(new Course("LM 101", "Introduction to Logistics Management", 3, "CBEAM", "BSLM", 1));
	allCourses.push_back(new Course("MATH 10", "Business Mathematics", 3, "CBEAM", "BSLM", 1));
	allCourses.push_back(new Course("ENGL 1", "Communication Skills 1", 3, "CBEAM", "BSLM", 1));
	allCourses.push_back(new Course("ETHICS 1", "Ethics and Moral Reasoning", 3, "CBEAM", "BSLM", 1));
	allCourses.push_back(new Course("STS 1", "Science, Technology and Society", 3, "CBEAM", "BSLM", 1));
	allCourses.push_back(new Course("PE 1", "Physical Education 1", 3, "CBEAM", "BSLM", 1));
	
	// Year 2 courses for BSLM
	allCourses.push_back(new Course("LM 201", "Supply Chain Management", 3, "CBEAM", "BSLM", 2));
	allCourses.push_back(new Course("ACC 101", "Fundamentals of Accounting", 3, "CBEAM", "BSLM", 2));
	allCourses.push_back(new Course("MGMT 101", "Principles of Management", 3, "CBEAM", "BSLM", 2));
	allCourses.push_back(new Course("MKTG 101", "Principles of Marketing", 3, "CBEAM", "BSLM", 2));
	allCourses.push_back(new Course("COMM 2", "Business Communication", 3, "CBEAM", "BSLM", 2));
	allCourses.push_back(new Course("PE 2", "Physical Education 2", 3, "CBEAM", "BSLM", 2));
	
	// Year 3 courses for BSLM
	allCourses.push_back(new Course("LM 301", "Warehousing and Distribution Management", 3, "CBEAM", "BSLM", 3));
	allCourses.push_back(new Course("LM 302", "Inventory Control", 3, "CBEAM", "BSLM", 3));
	allCourses.push_back(new Course("FIN 201", "Financial Management", 3, "CBEAM", "BSLM", 3));
	allCourses.push_back(new Course("OM 301", "Operations Management", 3, "CBEAM", "BSLM", 3));
	allCourses.push_back(new Course("RES 301", "Research Methods", 3, "CBEAM", "BSLM", 3));
	allCourses.push_back(new Course("PE 3", "Physical Education 3", 3, "CBEAM", "BSLM", 3));
	
	// Year 4 courses for BSLM
	allCourses.push_back(new Course("LM 401", "Global Logistics", 3, "CBEAM", "BSLM", 4));
	allCourses.push_back(new Course("LM 402", "Transportation Management", 3, "CBEAM", "BSLM", 4));
	allCourses.push_back(new Course("ENTR 401", "Entrepreneurship", 3, "CBEAM", "BSLM", 4));
	allCourses.push_back(new Course("CAP 401", "Capstone Project", 3, "CBEAM", "BSLM", 4));
	allCourses.push_back(new Course("PRACT 401", "Practicum in Logistics", 3, "CBEAM", "BSLM", 4));
	allCourses.push_back(new Course("PE 4", "Physical Education 4", 3, "CBEAM", "BSLM", 4));
	
	allCourses.push_back(new Course("ENTREP 11", "Introduction to Entrepreneurship", 3, "CBEAM", "BSENTREP", 1));
	allCourses.push_back(new Course("MATH 13", "Business Mathematics", 3, "CBEAM", "BSENTREP", 1));
	allCourses.push_back(new Course("COM 21", "Business Communication", 3, "CBEAM", "BSENTREP", 1));
	allCourses.push_back(new Course("ECON 13", "Microeconomics", 3, "CBEAM", "BSENTREP", 1));
	allCourses.push_back(new Course("STAT 110", "Statistics", 3, "CBEAM", "BSENTREP", 1));
	allCourses.push_back(new Course("PE 1", "Physical Education", 3, "CBEAM", "BSENTREP", 1));
	
	allCourses.push_back(new Course("ENTREP 21", "Marketing for Entrepreneurs", 3, "CBEAM", "BSENTREP", 2));
	allCourses.push_back(new Course("ACC 71", "Introduction to Financial Accounting", 3, "CBEAM", "BSENTREP", 2));
	allCourses.push_back(new Course("ENTREP 22", "Business Planning", 3, "CBEAM", "BSENTREP", 2));
	allCourses.push_back(new Course("ECON 14", "Macroeconomics", 3, "CBEAM", "BSENTREP", 2));
	allCourses.push_back(new Course("LAW 101", "Introduction to Business Law", 3, "CBEAM", "BSENTREP", 2));
	allCourses.push_back(new Course("PE 2", "Physical Education 2", 3, "CBEAM", "BSENTREP", 2));
	
	allCourses.push_back(new Course("ENTREP 31", "Operations Management", 3, "CBEAM", "BSENTREP", 3));
	allCourses.push_back(new Course("ENTREP 32", "Financial Management for Entrepreneurs", 3, "CBEAM", "BSENTREP", 3));
	allCourses.push_back(new Course("MGT 101", "Principles of Management", 3, "CBEAM", "BSENTREP", 3));
	allCourses.push_back(new Course("ENTREP 33", "Innovation and Product Development", 3, "CBEAM", "BSENTREP", 3));
	allCourses.push_back(new Course("RES 101", "Research Methods", 3, "CBEAM", "BSENTREP", 3));
	allCourses.push_back(new Course("PE 3", "Physical Education 3", 3, "CBEAM", "BSENTREP", 3));
	
	allCourses.push_back(new Course("ENTREP 41", "Entrepreneurship Seminar and Workshop", 3, "CBEAM", "BSENTREP", 4));
	allCourses.push_back(new Course("ENTREP 42", "Enterprise Feasibility Study", 3, "CBEAM", "BSENTREP", 4));
	allCourses.push_back(new Course("ENTREP 43", "Entrepreneurial Leadership", 3, "CBEAM", "BSENTREP", 4));
	allCourses.push_back(new Course("STRAT 101", "Strategic Management", 3, "CBEAM", "BSENTREP", 4));
	allCourses.push_back(new Course("OJT 101", "On-the-Job Training", 6, "CBEAM", "BSENTREP", 4));
	allCourses.push_back(new Course("ETHICS 101", "Business Ethics", 3, "CBEAM", "BSENTREP", 4));

    
 // Adding BSMMA courses for Year 1
    allCourses.push_back(new Course("EPD 101", "Elements and Principle of Design Lec ", 3, "CEAS", "BSMMA", 1));
    allCourses.push_back(new Course("AH 101", "Art History 1", 3, "CEAS", "BSMMA", 4));
    allCourses.push_back(new Course("PC 101", "Purposive Communication", 3, "CEAS", "BSMMA", 1));
    allCourses.push_back(new Course("DRW 101", "Drawing 1 Lec", 3, "CEAS", "BSMMA", 1));
    allCourses.push_back(new Course("DRW 10", "Drawing 1 Lab ", 3, "CEAS", "BSMMA", 1));
    allCourses.push_back(new Course("PE 1", "Physical Education", 3, "CEAS", "BSMMA", 1));

	   // Year 2 courses for BSMMA
	allCourses.push_back(new Course("GD 201", "Graphic Design 1", 3, "CEAS", "BSMMA", 2));
	allCourses.push_back(new Course("VID 201", "Video Production", 3, "CEAS", "BSMMA", 2));
	allCourses.push_back(new Course("3D 201", "3D Modeling and Animation", 3, "CEAS", "BSMMA", 2));
	allCourses.push_back(new Course("WEB 201", "Web Design and Development", 3, "CEAS", "BSMMA", 2));
	allCourses.push_back(new Course("MMP 201", "Multimedia Project Management", 3, "CEAS", "BSMMA", 2));
	allCourses.push_back(new Course("PE 2", "Physical Education 2", 3, "CEAS", "BSMMA", 2));
	
	//Year 3 BSMMA
	allCourses.push_back(new Course("ADV 301", "Advertising Design", 3, "CEAS", "BSMMA", 3));
	allCourses.push_back(new Course("ANI 301", "Advanced Animation Techniques", 3, "CEAS", "BSMMA", 3));
	allCourses.push_back(new Course("UIUX 301", "UI/UX Design", 3, "CEAS", "BSMMA", 3));
	allCourses.push_back(new Course("AUD 301", "Audio-Visual Production", 3, "CEAS", "BSMMA", 3));
	allCourses.push_back(new Course("CPM 301", "Creative Portfolio Management", 3, "CEAS", "BSMMA", 3));
	allCourses.push_back(new Course("PE 3", "Physical Education 3", 3, "CEAS", "BSMMA", 3));
	
	// Year 4 BSMMA
	allCourses.push_back(new Course("MMP 401", "Multimedia Capstone Project", 3, "CEAS", "BSMMA", 4));
	allCourses.push_back(new Course("FILM 401", "Film Production and Post-Processing", 3, "CEAS", "BSMMA", 4));
	allCourses.push_back(new Course("BIZ 401", "Business for Creatives", 3, "CEAS", "BSMMA", 4));
	allCourses.push_back(new Course("GAM 401", "Game Design and Development", 3, "CEAS", "BSMMA", 4));
	allCourses.push_back(new Course("VRAR 401", "Virtual Reality and Augmented Reality", 3, "CEAS", "BSMMA", 4));
	allCourses.push_back(new Course("PE 4", "Physical Education 4", 3, "CEAS", "BSMMA", 4));
	
	// Adding BSBIO courses for Year 1
	allCourses.push_back(new Course("GENBIO 101", "General Biology 1", 3, "CEAS", "BSBIO", 1));
	allCourses.push_back(new Course("CHEM 101", "General Chemistry 1", 3, "CEAS", "BSBIO", 1));
	allCourses.push_back(new Course("MATBIO 101", "Mathematics for Biologists", 3, "CEAS", "BSBIO", 1));
	allCourses.push_back(new Course("PC 101", "Purposive Communication", 3, "CEAS", "BSBIO", 1));
	allCourses.push_back(new Course("ICTBIO 101", "Introduction to ICT for Biologists", 3, "CEAS", "BSBIO", 1));
	allCourses.push_back(new Course("PE 1", "Physical Education 1", 3, "CEAS", "BSBIO", 1));
	
	// Year 2 BSBIO
	allCourses.push_back(new Course("GENBIO 201", "General Biology 2", 3, "CEAS", "BSBIO", 2));
	allCourses.push_back(new Course("CHEM 201", "Organic Chemistry", 3, "CEAS", "BSBIO", 2));
	allCourses.push_back(new Course("BOT 201", "Botany", 3, "CEAS", "BSBIO", 2));
	allCourses.push_back(new Course("ZOO 201", "Zoology", 3, "CEAS", "BSBIO", 2));
	allCourses.push_back(new Course("STATBIO 201", "Biostatistics", 3, "CEAS", "BSBIO", 2));
	allCourses.push_back(new Course("PE 2", "Physical Education 2", 3, "CEAS", "BSBIO", 2));
	
	// BSBIO Year 3
	allCourses.push_back(new Course("MICROBIO 301", "Microbiology", 3, "CEAS", "BSBIO", 3));
	allCourses.push_back(new Course("PHYSIOBIO 301", "Physiology", 3, "CEAS", "BSBIO", 3));
	allCourses.push_back(new Course("ECOBIO 301", "Ecology", 3, "CEAS", "BSBIO", 3));
	allCourses.push_back(new Course("GENETICS 301", "Genetics", 3, "CEAS", "BSBIO", 3));
	allCourses.push_back(new Course("RESBIO 301", "Research in Biology 1", 3, "CEAS", "BSBIO", 3));
	allCourses.push_back(new Course("PE 3", "Physical Education 3", 3, "CEAS", "BSBIO", 3));
	
	
	// BSBIO Year 4
	allCourses.push_back(new Course("BIOCAP 401", "Biology Capstone Project", 3, "CEAS", "BSBIO", 4));
	allCourses.push_back(new Course("EVOBIO 401", "Evolutionary Biology", 3, "CEAS", "BSBIO", 4));
	allCourses.push_back(new Course("BIOTECH 401", "Biotechnology", 3, "CEAS", "BSBIO", 4));
	allCourses.push_back(new Course("ENVSCI 401", "Environmental Science", 3, "CEAS", "BSBIO", 4));
	allCourses.push_back(new Course("RESBIO 402", "Research in Biology 2", 3, "CEAS", "BSBIO", 4));
	allCourses.push_back(new Course("PE 4", "Physical Education 4", 3, "CEAS", "BSBIO", 4));
	
	// Adding BS Psychology courses for Year 1
	allCourses.push_back(new Course("GENPSY 101", "General Psychology", 3, "CEAS", "BSPSYCH", 1));
	allCourses.push_back(new Course("SOCANTH 101", "Sociology and Anthropology", 3, "CEAS", "BSPSYCH", 1));
	allCourses.push_back(new Course("PC 101", "Purposive Communication", 3, "CEAS", "BSPSYCH", 1));
	allCourses.push_back(new Course("BIOPSY 101", "Biological Psychology", 3, "CEAS", "BSPSYCH", 1));
	allCourses.push_back(new Course("STATPSY 101", "Statistics for Psychology", 3, "CEAS", "BSPSYCH", 1));
	allCourses.push_back(new Course("PE 1", "Physical Education 1", 3, "CEAS", "BSPSYCH", 1));
	
	// Adding BS Psychology courses for Year 2
	allCourses.push_back(new Course("DEVPSY 201", "Developmental Psychology", 3, "CEAS", "BSPSYCH", 2));
	allCourses.push_back(new Course("EXPPSY 201", "Experimental Psychology", 3, "CEAS", "BSPSYCH", 2));
	allCourses.push_back(new Course("SOCPSY 201", "Social Psychology", 3, "CEAS", "BSPSYCH", 2));
	allCourses.push_back(new Course("COGPSY 201", "Cognitive Psychology", 3, "CEAS", "BSPSYCH", 2));
	allCourses.push_back(new Course("RSHPSY 201", "Research in Psychology 1", 3, "CEAS", "BSPSYCH", 2));
	allCourses.push_back(new Course("PE 2", "Physical Education 2", 3, "CEAS", "BSPSYCH", 2));
	
	// Adding BS Psychology courses for Year 3
	allCourses.push_back(new Course("THEO 301", "Theories of Personality", 3, "CEAS", "BSPSYCH", 3));
	allCourses.push_back(new Course("CLPSY 301", "Clinical Psychology", 3, "CEAS", "BSPSYCH", 3));
	allCourses.push_back(new Course("ABPSY 301", "Abnormal Psychology", 3, "CEAS", "BSPSYCH", 3));
	allCourses.push_back(new Course("ORGPSY 301", "Industrial/Organizational Psychology", 3, "CEAS", "BSPSYCH", 3));
	allCourses.push_back(new Course("RSHPSY 301", "Research in Psychology 2", 3, "CEAS", "BSPSYCH", 3));
	allCourses.push_back(new Course("PE 3", "Physical Education 3", 3, "CEAS", "BSPSYCH", 3));
	
	// BS Psychology Year 4
	allCourses.push_back(new Course("PSYCAP 401", "Psychology Capstone Project", 3, "CEAS", "BSPSYCH", 4));
	allCourses.push_back(new Course("NEUROPSY 401", "Neuropsychology", 3, "CEAS", "BSPSYCH", 4));
	allCourses.push_back(new Course("CONSPSY 401", "Counseling Psychology", 3, "CEAS", "BSPSYCH", 4));
	allCourses.push_back(new Course("PSYPRA 401", "Psychology Practicum", 3, "CEAS", "BSPSYCH", 4));
	allCourses.push_back(new Course("PSYETH 401", "Ethics in Psychology", 3, "CEAS", "BSPSYCH", 4));
	allCourses.push_back(new Course("PE 4", "Physical Education 4", 3, "CEAS", "BSPSYCH", 4));
}

public:
    static AllCourses& getInstance() {
    static AllCourses instance;
    return instance;
}

	~AllCourses() {
        // Clean up dynamically allocated memory
        for (Course* course : allCourses) {
            delete course;
        }
    }
	//Add New Course to the list of all courses
    bool addCourseToAll(Course* newCourse) {
    for (const auto& course : allCourses) {
        if (course->getCourseCode() == newCourse->getCourseCode()) {
            delete newCourse; // Avoid memory leak
            return false; // Duplicate course code
        }
    }
    allCourses.push_back(newCourse);
    return true; // Successfully added
}


    // Method to get all courses
    vector<Course*> getAllCourses() {
        return allCourses;
    }
	// Method to search a course based on its ID
    Course* searchCourse(const string searchID) const {
        string searchLower = convertToUpper(searchID);
        for (const auto& course : allCourses) {
            if (convertToUpper(course->getCourseCode()) == searchLower){
                return course;
            }
        }
        return nullptr;
    }
	// Function to update course code, name or unit
    void updateCourse(const string& searchID) {
	    Course* course = searchCourse(searchID);
	    if (!course) {
	        cout << "\t\033[31mCourse not found!\033[0m" << endl;
	        return; // Exit if the course is not found
	    }
	
	    string choice;
	    system("CLS");
	    cout << "\n\t-------------------------------------------------------------------------------------\n"
	         << "\t                                       UPDATE COURSE"
	         << "\n\t-------------------------------------------------------------------------------------\n";
	    cout << "\n\tWhat would you like to modify?\n";
	    cout << "\t1. Course Code\n\t2. Course Name\n\t3. Course Unit\n";
	    do {
	        cout << "\n\tEnter your choice: ";
	        getline(cin, choice);
	        if (choice == "1") {
	            string newCode;
	            newCode = getValidStringInput("\tEnter new Course Code: ");
	            newCode = convertToUpper(newCode);
	            course->setCourseCode(newCode);
	        } else if (choice == "2") {
	            string newName;
	            newName = getValidStringInput("\tEnter new Course Name: ");
	            course->setCourseName(newName);
	        } else if (choice == "3") {
	            int newUnit;
	            do {
	                newUnit = getValidIntegerInput("\tEnter new Course Unit: ");
	                if (newUnit < 1) {
	                    cout << "\t\033[31mInvalid unit.\033[0m\n";
	                }
	            } while (newUnit < 1);
	            course->setCourseUnit(newUnit);
	        } else {
	            cout << "\t\033[31mInvalid choice. Please try again.\033[m\n";
	        }
	    } while (choice != "1" && choice != "2" && choice != "3");
	}

	// Function to remove a course from the system
    void removeCourse(const string& searchID) {
        for (int i = 0; i < allCourses.size(); ++i) {
            if (convertToUpper(allCourses[i]->getCourseCode()) == convertToUpper(searchID)) {
                delete allCourses[i];  
                allCourses.erase(allCourses.begin() + i);  
                cout << "\t\033[32mCourse removed successfully.\033[0m\n";
                return;
            }
        }
        cout << "\t\033[31mCourse not found.\033[0m\n"; 
    }
    // Display courses according to Department, Program, and Year
    void displayCoursesByCategory(const string& dept, const string& program, int year) const {
        bool found = false;
        system("CLS");
        cout << "\n\t------------------------------------------------------------------------------------------\n"
             << "\t                              DISPLAYING COURSES (BY CATEGORY)"
             << "\n\t------------------------------------------------------------------------------------------\n";
        cout << "\n\tAvailable Courses for " << program << " - Year " << year << " in " << dept << ":\n";
        cout << endl << "\t\033[32m" << setw(20) << "Course Code" << setw(50) << "Course Name" << setw(10) << "Units\033[0m";
        
                cout << "\n\t----------------------------------------- Year " << year 
                     << " -----------------------------------------" << endl;

        // Loop over all courses in citeCourses to filter by department, program, and year
        for (const Course* course : allCourses) {
            if (course->getCourseDept() == dept && course->getCourseProg() == program && course->getCourseYear() == year) {
                cout << "\t" << setw(20) << course->getCourseCode() 
                         << setw(50) << course->getCourseName() 
                         << setw(10) << course->getCourseUnit() 
                         << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "\t\033[31mNo courses available for this program and year.\033[0m" << endl;
        }
    }
    
    // Display Curriculum of a specific Program
    void setCurriculumStrategy(CurriculumStrategy* strategy) {
        curriculumStrategy = strategy;
    }

    // Use the strategy to view the curriculum
    void viewCurriculum(const string& dept, const string& program) const {
        curriculumStrategy->viewCurriculum(dept, program);
    }
};

AllCourses* AllCourses::instance = nullptr;
class CurriculumByYear : public CurriculumStrategy {
public:
    void viewCurriculum(const string& dept, const string& program) const override {
        const vector<Course*>& allCourses = AllCourses::getInstance().getAllCourses();

        // Check if there are any courses for the specified department and program
        bool hasCourses = false;
        for (const Course* course : allCourses) {
            if (course->getCourseDept() == dept && course->getCourseProg() == program) {
                hasCourses = true;
                break;
            }
        }

        if (!hasCourses) {
            cout << "\tNo courses available for this program and department." << endl;
            system("PAUSE");
            return;
        }

        // Prompt user for the year they want to view
        int selectedYear;
        do {
            selectedYear = getValidIntegerInput("\tEnter the year you want to view (1-4): ");
            if (selectedYear < 1 || selectedYear > 4) {
                cout << "\t\033[31mInvalid input.\033[0m\n";
            }
        } while (selectedYear < 1 || selectedYear > 4);

        // Display courses for the selected year
        bool foundCourses = false;
        cout << "\033[32m";
        cout << endl << setw(20) << "Course Code" << setw(50) << "Course Name" 
             << setw(10) << "Units" << setw(10) << "Year";
        cout << "\033[0m";
        cout << "\n\t-------------------------------------- Year " << selectedYear 
             << " --------------------------------------" << endl;
        for (const Course* course : allCourses) {
            if (course->getCourseDept() == dept && course->getCourseProg() == program && course->getCourseYear() == selectedYear) {
                cout << setw(20) << course->getCourseCode()
                     << setw(50) << course->getCourseName()
                     << setw(10) << course->getCourseUnit()
                     << setw(10) << course->getCourseYear()
                     << endl;
                foundCourses = true;
            }
        }

        if (!foundCourses) {
            cout << "\tNo courses available for Year " << selectedYear << endl;
        }
    }
};

class CurriculumAllCourses : public CurriculumStrategy {
public:
    void viewCurriculum(const string& dept, const string& program) const override {
        cout << "\n\t---------------------------------------------------------------------------------------\n"
             << "\t                                      VIEWING COURSES"
             << "\n\t---------------------------------------------------------------------------------------\n";
        cout << "\033[32m";
        cout << setw(20) << "Course Code" << setw(50) << "Course Name" << setw(10) << "Units" << setw(10) << "Year" << endl;
        cout << "\033[0m";

        const vector<Course*>& allCourses = AllCourses::getInstance().getAllCourses();
        bool hasCourses = false;

        for (int year = 1; year <= 4; ++year) { 
            bool yearHasCourses = false;
            for (const Course* course : allCourses) {
                if (course->getCourseDept() == dept && 
                    course->getCourseProg() == program && 
                    course->getCourseYear() == year) {
                    if (!yearHasCourses) {
                        cout << "\n\t---------------------------------------- Year " << year << " ---------------------------------------" << endl;
                        yearHasCourses = true;
                        hasCourses = true;
                    }
                    cout
						 << setw(20) << course->getCourseCode()
                         << setw(50) << course->getCourseName()
                         << setw(10) << course->getCourseUnit()
                         << setw(10) << course->getCourseYear()
                         << endl;
                }
            }
        }

        if (!hasCourses) {
            system("CLS");
            cout << "\n\tNo courses available for this program and department." << endl;
        }
    }
};

class User {
protected:
    string firstName;
    string lastName;
    string userID;
    string password;

public:
    User(string fn, string ln, string id, string pass)
        : firstName(fn), lastName(ln), userID(id), password(pass) {}

    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getUserID() const { return userID; }
    string getPassword() const { return password; }

    void setFirstName(const string& fn) { firstName = fn; }
    void setLastName(const string& ln) { lastName = ln; }
    void setUserID(const string& id) { userID = id; }
    void setPassword(const string& pass) { password = pass; }

    virtual void displayUserInfo() const {
    	cout << "\t" << left << setw(15) << userID 
             << setw(25) << firstName + " " + lastName;
        
    }
    
    virtual void validateID() = 0;
	
    virtual ~User() = default;
};

class PaymentStrategy {
public:
    virtual void processPayment(double totalTuition, double& amountPaid) = 0;
    virtual ~PaymentStrategy() = default; 
};

class FullPayment : public PaymentStrategy {
public:
    void processPayment(double totalTuition, double& amountPaid) override {
        double paymentAmount = totalTuition - amountPaid;
        cout << "\tEnter full payment amount (PHP " << fixed << setprecision(2) << paymentAmount << "): ";
        double payment = getValidIntegerInput("");
        
        if (payment == paymentAmount) {
            amountPaid += payment;
            cout << "\tFull payment of PHP " << fixed << setprecision(2) << payment << " received." << endl;
        } else {
            cout << "\t\033[31mInvalid payment amount. You must pay exactly PHP " << fixed << setprecision(2) << paymentAmount << ".\033[0m" << endl;
        }
    }
};

class InstallmentPayment : public PaymentStrategy {
public:
    void processPayment(double totalTuition, double& amountPaid) override {
        double installmentAmount = totalTuition / 3;
        cout << "\tEnter installment payment (PHP " << fixed << setprecision(2) << installmentAmount << "): ";
        double payment = getValidIntegerInput("");
        
        if (payment == installmentAmount) {
            amountPaid += payment;
            cout << "\t\033[32mInstallment payment of PHP " << fixed << setprecision(2) << payment << " received.\033[0m" << endl;
        } else {
            cout << "\t\033[31mInvalid installment amount. Expected PHP " << fixed << setprecision(2) << installmentAmount << ".\033[0m" << endl;
        }
    }
};

class CustomPayment : public PaymentStrategy {
public:
    void processPayment(double totalTuition, double& amountPaid) override {
        cout << "\tEnter the amount you want to pay: PHP ";
        double payment = getValidIntegerInput("");
        
        if (payment <= 0) {
            cout << "\t\033[31mInvalid payment amount. Payment must be greater than 0.\033[0m" << endl;
        } else if (payment + amountPaid > totalTuition) {
            cout << "\t\033[31mExcess payment! You only need PHP " << fixed << setprecision(2) << (totalTuition - amountPaid) << " to fully pay.\033[0m" << endl;
        } else {
            amountPaid += payment;
            cout << "\t\033[32mPayment of PHP " << fixed << setprecision(2) << payment << " received.\033[0m" << endl;
        }
    }
};

class Student : public User {
private:
    string department;
    string program;
    int yearLevel;
    vector<Course> enrolledCourses;
    string paymentStatus = "Unpaid";  
    double amountPaid = 0;   
	string paymentPlan = ""; 
	PaymentStrategy* paymentStrategy = nullptr;

public:
    Student(string fn, string ln, string id, string pass, string dept, string prog, int year)
        : User(fn, ln, id, pass), department(dept), program(prog), yearLevel(year) {}

    string getDepartment() const { return department; }
    string getProgram() const { return program; }
    int getYearLevel() const { return yearLevel; }
    string getPaymentStatus() const { return paymentStatus; }
    int getAmountPaid() const { return amountPaid; }
    string getPaymentPlan() const { return paymentPlan; }

    void setDepartment(const string& dept) { department = dept; }
    void setProgram(const string& prog) { program = prog; }
    void setYearLevel(int year) { yearLevel = year; }
    
	void setPaymentPlan(const string& plan) {
        paymentPlan = plan;
        if (plan == "Full Payment") {
            paymentStrategy = new FullPayment();
        } else if (plan == "Installment") {
            paymentStrategy = new InstallmentPayment();
        } else if (plan == "Custom") {
            paymentStrategy = new CustomPayment();
        } else {
            cout << "\t\033[31mInvalid payment plan!\033[0m" << endl;
        }
    }

    void enrollCourse(Course& course) {
    
    // Check if the course is already enrolled
    for (const auto& enrolledCourse : enrolledCourses) {
        if (enrolledCourse.getCourseCode() == course.getCourseCode()) {
            cout << "\t\033[31m" << enrolledCourse.getCourseName() 
                 << " has already been added. Choose another one.\033[0m" << endl;
            return;
        }
    }
    // Add the course and update enrollment details
    enrolledCourses.push_back(course);
    course.addStudent(getFirstName() + " " + getLastName());
    cout << "\t\033[32m" << course.getCourseName() << " has been enrolled.\033[0m" << endl;
    if(amountPaid==0) {
    	paymentStatus = "Unpaid"; }
    else{
    	paymentStatus = "Pending";
	}
    
}

    void dropCourse(string& courseCode) {
        for (auto it = enrolledCourses.begin(); it != enrolledCourses.end(); ++it) {
            if (it->getCourseCode() == courseCode) {
                cout << "\t" << it->getCourseName() << " has been dropped." << endl;
                enrolledCourses.erase(it);
                return;
            }
        }
        cout << "\tCourse not found." << endl;
    }

    void updatePaymentStatus(double totalTuition) {
        if (amountPaid >= totalTuition) {
            paymentStatus = "Fully Paid";
        } else if (amountPaid > 0) {
            paymentStatus = "Pending";
        } else {
            paymentStatus = "Unpaid";
        }
    }
    
    void addPayment(double payment, double totalTuition) {
        amountPaid += payment;
        updatePaymentStatus(totalTuition);
    }
    

    void processPayment(double totalTuition) {
        if (paymentStatus == "Fully Paid") {
            cout << "\tYou have already fully paid your tuition." << endl;
            return;
        }

        // If payment plan is not set, ask the user for one
        if (paymentPlan.empty()) {
            cout << "\n\tPayment Options:" << endl;
            cout << "\t1. Pay in Full" << endl;
            cout << "\t2. Pay in Installments" << endl;
            cout << "\t3. Pay a Custom Amount" << endl;

            int choice = getValidIntegerInput("\n\tEnter your choice (1, 2, or 3): ");
            switch (choice) {
                case 1:
                    setPaymentPlan("Full Payment");
                    break;
                case 2:
                    setPaymentPlan("Installment");
                    break;
                case 3:
                    setPaymentPlan("Custom");
                    break;
                default:
                    cout << "\t\033[31mInvalid choice. Please try again.\033[0m" << endl;
                    return;
            }
        }

        // Process payment using the selected strategy
        if (paymentStrategy) {
            paymentStrategy->processPayment(totalTuition, amountPaid);
        }

        updatePaymentStatus(totalTuition);
        if (paymentStatus == "Fully Paid"){ cout << "\n\tUpdated Payment Status: \033[32m" << paymentStatus << "\033[0m" <<endl; } 
		else if (paymentStatus == "Pending"){ cout << "\n\tUpdated Payment Status: \033[33m" << paymentStatus << "\033[0m" <<endl; }
		else if (paymentStatus == "Unpaid"){ cout << "\n\tUpdated Payment Status: \033[31m" << paymentStatus << "\033[0m" <<endl; } 
    }
    
    // Destructor to clean up dynamically allocated strategy object
    ~Student() {
        delete paymentStrategy;  // Avoid memory leak
    }

    // View enrolled courses with payment details
    void viewEnrolledCoursesWithPayment() {
        if (enrolledCourses.empty()) {
        	system("CLS");
        	cout << "\n\t-------------------------------------------------------------------------------------\n"
           		 << "\t                                   ENROLLED COURSES"
       			 << "\n\t-------------------------------------------------------------------------------------\n";
            cout << "\tYou are not enrolled in any courses." << endl;
            system("PAUSE");
            return;
        }

        int totalUnits = 0;
        system("CLS");
        cout << "\n\t-------------------------------------------------------------------------------------\n"
           	 << "\t                                   ENROLLED COURSES"
       		 << "\n\t-------------------------------------------------------------------------------------\n";
       	cout << "\033[32m";
       	cout << setw(20) << "\tCourse Code" << setw(50) << "Course Name"  << right <<setw(10) << "Units" << endl << endl;
       	cout << "\033[0m";
        for (const auto& course : enrolledCourses) {
            course.displayCourseInfo();  // Displays course details, including units
            totalUnits += course.getCourseUnit();  // Assumes Course class has a getUnits() method
        }
		
        int totalTuition = totalUnits * 1500;
        cout << "\n\tTotal Units: " << totalUnits << endl;
        cout << "\tTotal Tuition: PHP " << totalTuition << endl;
        cout << "\n\t-------------------------------------------------------------------------------------\n";
        if (paymentStatus == "Fully Paid"){ cout << "\n\tPayment Status: \033[32m" << paymentStatus << "\033[0m" <<endl; } 
		else if (paymentStatus == "Pending"){ cout << "\n\tPayment Status: \033[33m" << paymentStatus << "\033[0m" <<endl; }
		else if (paymentStatus == "Unpaid"){ cout << "\n\tPayment Status: \033[31m" << paymentStatus << "\033[0m" <<endl; } 
        cout << "\tAmount Paid: PHP " << amountPaid << endl;
        cout << "\tRemaining Balance: PHP " << totalTuition - amountPaid << endl;

        processPayment(totalTuition);
    }

	void viewEnrolledCourses() const {
    if (enrolledCourses.empty()) {
    	system("CLS");
    	cout << "\n\t-------------------------------------------------------------------------------------\n"
           	 << "\t                                   ENROLLED COURSES"
       		 << "\n\t-------------------------------------------------------------------------------------\n";
        cout << "\tYou are not enrolled in any courses." << endl;
        return;
    }

    system("CLS");
    cout << "\n\t-------------------------------------------------------------------------------------\n"
      	 << "\t                                   ENROLLED COURSES"
		 << "\n\t-------------------------------------------------------------------------------------\n";
	cout << "\033[32m";
       	cout << setw(20) << "\tCourse Code" << setw(50) << "Course Name" << right << setw(10) << "Units" << endl << endl;
    cout << "\033[0m";
    for (const auto& course : enrolledCourses) {
        course.displayCourseInfo();  // Display course details
    }
	if (paymentStatus == "Fully Paid"){
    cout << "\n\tPayment Status: \033[32m" << paymentStatus << "\033[0m" <<endl;
	} 
	else if (paymentStatus == "Pending"){
    cout << "\n\tPayment Status: \033[33m" << paymentStatus << "\033[0m" <<endl;
	}
	else if (paymentStatus == "Unpaid"){
    cout << "\n\tPayment Status: \033[31m" << paymentStatus << "\033[0m" <<endl;
	}
}

    void displayUserInfo() const override {
        User::displayUserInfo();
        cout << left
			 << setw(20) << department
             << setw(15) << program
             << setw(10) << yearLevel
             << endl;
    }
    
    void displayUser() const {
    	system("CLS");
    	cout << "\n\t--------------------------------------------------------------------------\n"
    	 	 << "\t                            STUDENT INF0RMATION"
    	 	 << "\n\t--------------------------------------------------------------------------\n";
    	cout << "\n\tName: " << getFirstName() << " " << getLastName() 
			 << "\n\tStudent ID: " << getUserID() 
			 << "\n\tDepartment: " << department
			 << "\n\tProgram: " << program
			 << "\n\tYear: " << yearLevel << endl;	
	}
	
	void validateID() override {
        while (getUserID().empty() || getUserID()[0] != 'S') {
            cout << "\t\033[31mError: Student ID must start with 'S'. Invalid ID: \033[0m" << getUserID() << endl;
            string newID;
            newID = getValidStringInput("\tPlease enter a valid Student ID: ");
            newID = convertToUpper(newID);
            setUserID(newID);
        }
    }
};

class AllStudents {
private:
    vector<Student> allStudents;
    static AllStudents* instance;

    // Private constructor to prevent instantiation
    AllStudents() {}

public:
    // Static method to get the instance
    static AllStudents& getInstance() {
    static AllStudents instance;
    return instance;
}
    
    void addStudent(const Student& student) {
        allStudents.push_back(student);
    }

    Student* findStudent(const string& studentID) {
        for (auto& student : allStudents) {
            if (student.getUserID() == studentID) {
                return &student;
            }
        }
        return nullptr;
    }
    
    void displayAllStudents() {
    if (allStudents.empty()) {
        cout << "\tNo students available." << endl;
        return;
    }

    // Header
    cout << "\t\033[32m" << left 
         << setw(15) << "Student ID" 
         << setw(25) << "Name" 
         << setw(20) << "Department" 
         << setw(15) << "Program" 
         << setw(10) << "Year\033[0m" 
         << endl;
    cout << "\t-------------------------------------------------------------------------------------\n";

    // Display student details
    for (const Student& student : allStudents) {
        student.displayUserInfo();
    }
}
	// Function to remove a student from the system
	void removeStudent(const string& searchID) {
    	for (int i = 0; i < allStudents.size(); ++i) {
        	if (convertToUpper(allStudents[i].getUserID()) == convertToUpper(searchID)) {
            	allStudents.erase(allStudents.begin() + i); // Removing by index
            	cout << "\t\033[32mStudent removed successfully.\033[0m\n";
            	return;
        	}
    	}
    	cout << "\t\033[31mStudent not found.\033[0m\n";
	}
	
	void editStudent(const string& studentID) {
        Student* student = findStudent(studentID);
        if (student == nullptr) {
            cout << "\t\033[31mStudent not found.\033[0m\n";
            return;
        }

        int choice;
        cout << "\t-------------------------------------------------------------------------------------";
        cout << "\n\tEditing student with ID: " << studentID << endl << endl;
        cout << "\t1. Edit Name" << endl;
        cout << "\t2. Edit Department and Program" << endl;
        cout << "\t3. Edit Year" << endl;
        cout << "\t4. Cancel" << endl << endl;
        
        choice = getValidIntegerInput("\tEnter your choice: ");

        switch (choice) {
            case 1: {
            	system("CLS");
            	cout << "\n\t-------------------------------------------------------------------------------------\n"
            		 << "\t                                       EDIT NAME"
            		 << "\n\t-------------------------------------------------------------------------------------\n";
                string newFName, newLName;
                cout << "\n\tEnter new first name: ";
                getline(cin, newFName);
                student->setFirstName(newFName);
                cout << "\tEnter new last name: ";
                getline(cin, newLName);
                student->setLastName(newLName);
                cout << "\t\033[32mName updated successfully.\033[0m" << endl;
                break;
            }
            case 2: {
                string newDept, newProgram;
                system("CLS");
                cout << "\n\t-------------------------------------------------------------------------------------\n"
            		 << "\t                              EDIT DEPARTMENT AND PROGRAM"
            		 << "\n\t-------------------------------------------------------------------------------------\n";
				do {
			        newDept = getValidStringInput("\tEnter new department:  \n\t   - CITE (College of Information Technology and Engineering)\n\t   - CBEAM (College of Business, Economics, Accountancy and Management)\n\t   - CEAS (College of Education, Arts and Sciences)\n\t     --> ");
			        newDept = convertToUpper(newDept);
			        if (newDept != "CITE" && newDept != "CBEAM" && newDept != "CEAS") {
			            cout << "\t\033[31mInvalid Department. Please try again.\033[0m\n";
			        }
			        
			        if (newDept == student->getDepartment()){
			    					cout << "\t\033[31mInvalid. Department cannot be the same as previous department.\033[0m\n";
					} 
								
			    } while (newDept != "CITE" && newDept != "CBEAM" && newDept != "CEAS" || newDept == student->getDepartment());
    
                student->setDepartment(newDept);
                cout << "\t\033[32mDepartment updated successfully.\033[0m" << endl;                
                
                do {
			        if (newDept == "CITE") {
			            newProgram = getValidStringInput("\n\tEnter Program: \n\t   - BSCS (Bachelor of Science in Computer Science)\n\t   - BSIT (Bachelor of Science in Information Technology) \n\t   - BSARCHI (Bachelor of Science in Architecture) \n\t     --> ");
			            newProgram = convertToUpper(newProgram);
			            
			        } else if (newDept == "CBEAM") {
			            newProgram = getValidStringInput("\n\tEnter Program: \n\t   - BSA (Bachelor of Science in Accountancy)\n\t   - BSLM (Bachelor of Science in Legal Management) \n\t   - BSENTREP (Bachelor of Science in Entrepreneurship) \n\t     --> ");
			            newProgram = convertToUpper(newProgram);
			            
			        } else if (newDept == "CEAS") {
			            newProgram = getValidStringInput("\n\tEnter Program: \n\t   - BSMMA (Bachelor of Science in Multimedia Arts)\n\t   - BSBIO (Bachelor of Science in Biology) \n\t   - BSPSYCH (Bachelor of Science in Psychology) \n\t     --> ");
			            newProgram = convertToUpper(newProgram);
			            
			        }
			        if ((newDept == "CITE" && newProgram != "BSCS" && newProgram != "BSIT" && newProgram != "BSARCHI" || newProgram == student->getProgram()) ||
			            (newDept == "CBEAM" && newProgram != "BSA" && newProgram != "BSLM" && newProgram != "BSENTREP" || newProgram == student->getProgram()) ||
			            (newDept == "CEAS" && newProgram != "BSMMA" && newProgram != "BSBIO" && newProgram != "BSPSYCH" || newProgram == student->getProgram())) {
			            cout << "\t\033[31mInvalid Program. Please try again.\033[0m\n";
			            newProgram = ""; // Clear invalid program to repeat input
			        }
			    } while (newProgram.empty());
			    
			    student->setProgram(newProgram);
                cout << "\n\t\033[32mProgram updated successfully.\033[0m" << endl;
                
                
                break;
            }
            case 3: {
                int newYear;
                system("CLS");
                cout << "\n\t-------------------------------------------------------------------------------------\n"
            		 << "\t                                       EDIT YEAR"
            		 << "\n\t-------------------------------------------------------------------------------------\n";
            	do{
                newYear = getValidIntegerInput("\n\tEnter new year: ");
                if(newYear < 1 || newYear > 4){
                	cout << "\t\033[31mInvalid Year.\033[0m";
				} 
				}while(newYear < 1 || newYear > 4);
                student->setYearLevel(newYear);
                cout << "\t\033[32mYear updated successfully.\033[0m" << endl;
                break;
            }
            case 4:
                cout << "\tEdit canceled." << endl;
                break;
            default:
                cout << "\t\033[31mInvalid choice!\033[0m" << endl;
        }
    }
    
    bool empty() const {
        return allStudents.empty();
    }
};
AllStudents* AllStudents::instance = nullptr;

class Professor : public User {
private:
    vector<Course*> courses; // Courses assigned to the professor

public:
    // Constructor
    Professor(string fn, string ln, string profID, string pwd)
        : User(fn, ln, profID, pwd) {}

    // Add a course to the professor's assigned courses
    void assignCourse(Course* course) {
        // Ensure the course isn't already assigned
            courses.push_back(course);
            course->setProfessor(*this); // Associate this professor with the course
        
    }

    // Get all assigned courses
    vector<Course*> getAssignedCourses() const {
        return courses;
    }

    // View assigned courses and their enrolled students
    void viewCoursesAndStudents(const Professor* professor) const {
    	cout << "\n\t--------------------------------------------------------------------------\n"
			 << "\t                            VIEW COURSES AND STUDENTS"
			 << "\n\t--------------------------------------------------------------------------\n";
        if (courses.empty()) {
            cout << "\n\tNo courses assigned to you yet.\n";
            return;
        }

        for (const auto& course : courses) {
            cout << "\n\t\033[32mCourse: " << course->getCourseCode() << " - "<< course->getCourseName() << "\033[0m";

            // Display enrolled students
            const vector<string>& students = course->getEnrolledStudents();
            if (students.empty()) {
                cout << "\n\tNo students are enrolled in this course.\n";
            } else {
                cout << "\n\tEnrolled Students: \n\n";
                for (const auto& studentName : students) {
                    cout << "\t    - " << studentName << endl;
                }
            }
        }
    }

    // Display professor's information
    void displayUserInfo() const override {
        system("CLS");
    	cout << "\n\t---------------------------------------------------------------------\n"
             << "\t                         PROFESSOR INFORMATION"
             << "\n\t---------------------------------------------------------------------\n";
        cout << "\n\tName: " << getFirstName() << " " << getLastName()  <<
				"\n\tProfessor ID: " << getUserID();
        cout << "\n\tAssigned Courses: ";
        if (courses.empty()) {
            cout << "\tNone";
            system("PAUSE");
        } else {
            for (const auto& course : courses) {
                cout << course->getCourseCode() << " ";
            }
        }
        cout << endl;
    }
    
    void validateID() override {
        while (getUserID().empty() || getUserID()[0] != 'P') {
            cout << "\t\033[31mError: Professor ID must start with 'P'. Invalid ID: " << getUserID() << "\033[0m" << endl;
            string newID;
            newID = getValidStringInput("\tPlease enter a valid Professor ID: ");
            newID = convertToUpper(newID);
            setUserID(newID);
        }
    }
};

class AllProfessors {
private:
    vector<Professor> professors;
    static AllProfessors* instance;

    // Private constructor to prevent instantiation
    AllProfessors() {}

public:
    // Static method to get the instance
    static AllProfessors& getInstance() {
    static AllProfessors instance;
    return instance;
}
    
    void addProfessor(const Professor& prof) {
        professors.push_back(prof);
    }

    bool empty() const {
        return professors.empty();
    }

	void displayAllProfessors() const {
    system("CLS"); // Clear the screen for better user experience
    cout << "\n\t-------------------------------------------------------------------------------------\n"
         << "\t                                 DISPLAY ALL PROFESSORS"
         << "\n\t-------------------------------------------------------------------------------------\n";

    if (professors.empty()) {
        cout << "\tNo professors available." << endl;
        return;
    }

    // Display table header
    cout << "\033[32m";
    cout << "\t" << setw(15) << "Professor ID" 
         << setw(30) << "Name" 
         << setw(30) << "Assigned Courses" << endl;
    cout << "\033[0m";
    cout << "\t-------------------------------------------------------------------------------------\n";

    for (const auto& prof : professors) {
        // Display professor ID and name
        cout << "\t" << setw(15) << prof.getUserID()
             << setw(30) << (prof.getFirstName() + " " + prof.getLastName()) << setw(30);

        // Retrieve and display assigned courses
        vector<Course*> profCourses = prof.getAssignedCourses();
        if (profCourses.empty()) {
            cout << "None";
        } else {
            for (size_t i = 0; i < profCourses.size(); ++i) {
                cout << profCourses[i]->getCourseCode() << "  ";
            }
        }
        cout << endl;
    }
}

    Professor* findProfessor(const string& profID) {
    for (auto& prof : professors) {
        if (prof.getUserID() == profID) {
            return &prof; // Return a pointer to the professor
        }
    }
   		return nullptr; // Return null if not found
	}
};
AllProfessors* AllProfessors::instance = nullptr;

class Admin {
private:
    string username;
    string password;
    AllStudents& allStudents;    // Reference to students
    AllCourses& allCourses;      // Reference to courses
    AllProfessors& allProfessors; // Reference to professors

public:
    // Constructor
    Admin(string u, string p, AllStudents& students, AllCourses& courses, AllProfessors& professors)
        : username(u), password(p), allStudents(students), allCourses(courses), allProfessors(professors) {}

    // Getters and Setters
    string getUsername() const { return username; }
    void setUsername(const string& u) { username = u; }
    string getPassword() const { return password; }
    void setPassword(const string& p) { password = p; }

    // Add a new student
    void addStudent() {
        string department, program, studentID;
        int yearLevel;

        system("CLS");
        cout << "\n\t-------------------------------------------------------------------------------------\n"
             << "\t                                      ADD STUDENT"
             << "\n\t-------------------------------------------------------------------------------------\n";
        string firstName = getValidStringInput("\n\tEnter First Name: ");
        string lastName = getValidStringInput("\tEnter Last Name: ");

        // Ensure unique student ID
         do {
	        studentID = getValidStringInput("\tEnter Student ID: ");
	        studentID = convertToUpper(studentID);
		    // Create Student object temporarily to validate the ID
		    Student tempStudent(firstName, lastName, studentID, "", "", "", 0);
		    // Validate the student ID
		    tempStudent.validateID(); // Calls validateID of Student class
		    studentID = tempStudent.getUserID();
			if (allStudents.findStudent(studentID) != nullptr) {
		            cout << "\t\033[31mError: Student ID already exists. Please enter a unique ID.\033[0m\n";
		        }
	    } while (allStudents.findStudent(studentID) != nullptr);

        string studentPass = getValidStringInput("\tEnter Student Password: ");
        validateDepartmentAndProgram(department, program);

        do {
            yearLevel = getValidIntegerInput("\n\tEnter Year Level (1-4): ");
            if (yearLevel < 1 || yearLevel > 4) {
                cout << "\n\t\033[31mInvalid input. Enter a number from 1-4.\033[0m\n";
            }
        } while (yearLevel < 1 || yearLevel > 4);

        Student newStudent(firstName, lastName, studentID, studentPass, department, program, yearLevel);
        allStudents.addStudent(newStudent);
        cout << "\t\033[32mStudent added successfully!\033[0m\n";
    }

    // Remove a student
    void removeStudent() {
        string studentID;
        if (allStudents.empty()) {
        	system("CLS");
        	cout << "\n\t-------------------------------------------------------------------------------------\n"
			 	 << "\t                                      REMOVE STUDENT"
			 	 << "\n\t-------------------------------------------------------------------------------------\n";
        	cout << "\tNo students available to remove." << endl;
        	system("PAUSE");
        	return;
    	}
    	else{
        	system("CLS");
        	cout << "\n\t-------------------------------------------------------------------------------------\n"
			 	 << "\t                                      REMOVE STUDENT"
			 	 << "\n\t-------------------------------------------------------------------------------------\n";
        	allStudents.displayAllStudents();
        	string studentID = getValidStringInput("\n\tEnter Student ID to remove: ");
        	studentID = convertToUpper(studentID);
        	allStudents.removeStudent(studentID);
    	}
    }
    
    // Edit student details 
    void editStudent() {
        string studentID;
        if (allStudents.empty()) {
        	system("CLS");
        	cout << "\n\t-------------------------------------------------------------------------------------\n"
			 	 << "\t                                       EDIT STUDENT"
			 	 << "\n\t-------------------------------------------------------------------------------------\n";
        	cout << "\tNo students available to edit." << endl;
        	return;
    	}
    	else{
    		system("CLS");
    		cout << "\n\t-------------------------------------------------------------------------------------\n"
			 	 << "\t                                       EDIT STUDENT"
			 	 << "\n\t-------------------------------------------------------------------------------------\n";
        	allStudents.displayAllStudents();
        	string studentID = getValidStringInput("\n\tEnter Student ID to edit: ");
        	studentID = convertToUpper(studentID);
        	allStudents.editStudent(studentID);
    	}
    }

    // Add a course
    void addCourse() {
    string courseCode, courseName, courseDept, courseProg;
    int courseUnit, courseYear;

    system("CLS");
    cout << "\n\t-------------------------------------------\n"
         << "\t                 ADD COURSE"
         << "\n\t-------------------------------------------\n";

    courseCode = getValidStringInput("\n\tEnter Course Code: ");
    courseCode = convertToUpper(courseCode);
    courseName = getValidStringInput("\tEnter Course Name: ");
    do{
    courseUnit = getValidIntegerInput("\tEnter Course Units (e.g., 3): ");
    if(courseUnit < 1){
    	cout << "\t\033[31mInvalid input.\033[0m\n";
	}
    }while(courseUnit < 1);
    validateDepartmentAndProgram(courseDept, courseProg);

    do {
        courseYear = getValidIntegerInput("\n\tEnter Course Year (1-4): ");
        if (courseYear < 1 || courseYear > 4) {
            cout << "\t\033[31mInvalid input. Enter a number from 1-4.\033[0m\n";
        }
    } while (courseYear < 1 || courseYear > 4);

    Course* newCourse = new Course(courseCode, courseName, courseUnit, courseDept, courseProg, courseYear);
    if (!allCourses.addCourseToAll(newCourse)) {
        cout << "\t\033[31mError: Could not add course. Duplicate code?\033[0m\n";
    } else {
        cout << "\033[32m\tCourse successfully added!\033[0m\n";
        allCourses.setCurriculumStrategy(new CurriculumAllCourses());
        allCourses.viewCurriculum(courseDept, courseProg);
        
    }
}
    // Edit an existing course
	void editCourse(AllCourses& allCourses) {
	    string dept, prog;
	    system("CLS");
	    cout << "\n\t----------------------------------------------------------------\n"
	         << "\t                          EDIT COURSE"
	         << "\n\t----------------------------------------------------------------\n\n";
	    validateDepartmentAndProgram(dept, prog);
	    allCourses.setCurriculumStrategy(new CurriculumAllCourses());
	    allCourses.viewCurriculum(dept, prog);
	
	    string courseID = getValidStringInput("\n\tEnter Course Code to edit: ");
	    courseID = convertToUpper(courseID);
	
	    // Check if the course is available under the selected department and program
	    Course* courseToEdit = allCourses.searchCourse(courseID);
	    if (courseToEdit && courseToEdit->getCourseDept() == dept && courseToEdit->getCourseProg() == prog) {
	        // Proceed to update the course
	        allCourses.updateCourse(courseID);
	    } else {
	        cout << "\t\033[31mCourse not found in the selected department and program!\033[0m" << endl;
	    }
	}

	
	void displayAllStudents(){
		system("CLS"); 
		cout << "\n\t-------------------------------------------------------------------------------------\n"
			 << "\t                                      ALL STUDENTS"
			 << "\n\t-------------------------------------------------------------------------------------\n\n"; 
		allStudents.displayAllStudents();
	}
    // Remove a course
	void removeCourse() {
    	string courseID, dept, prog;
    	int year;
    	
    	// Validate department input
    	validateDepartmentAndProgram(dept, prog);
    	// Validate year input
    	allCourses.setCurriculumStrategy(new CurriculumByYear());
		system("CLS");
		cout << "\n\t-------------------------------------------------------------------------------------\n"
			 << "\t                                     REMOVE COURSE"
			 << "\n\t-------------------------------------------------------------------------------------\n";
			 allCourses.viewCurriculum(dept, prog);
    	courseID = getValidStringInput("\n\tEnter Course Code to remove: ");
    	courseID = convertToUpper(courseID);
    	allCourses.removeCourse(courseID);
	}
	
	void addProfessor() {
	    string firstName, lastName, profID, password;
		
		system("CLS");
		cout << "\n\t-------------------------------------------------------\n"
			 << "\t                       ADD PROFESSOR"
			 << "\n\t-------------------------------------------------------\n";
	    cout << "\n\tEnter Professor Details:\n";
	    firstName = getValidStringInput("\tFirst Name: ");
	    lastName = getValidStringInput("\tLast Name: ");
	
	    // Ensure unique and valid professor ID
	    do {
	        profID = getValidStringInput("\tProfessor ID: ");
	        profID = convertToUpper(profID);
	
	        // Create a temporary professor to validate the ID
	        Professor tempProfessor(firstName, lastName, profID, "");
	        tempProfessor.validateID();
	
	        // Update profID with the validated ID
	        profID = convertToUpper(tempProfessor.getUserID());
	
	        // Check for duplicate ID after validation
	        if (allProfessors.findProfessor(profID) != nullptr) {
	            cout << "\t\033[31mError: Validated Professor ID already exists. Please enter a unique ID.\033[0m\n";
	            profID.clear(); // Clear the ID to enforce re-entry
	        }
	    } while (profID.empty() || allProfessors.findProfessor(profID) != nullptr);
	
	    // Proceed if the ID is valid and unique
	    cout << "\tPassword: ";
	    getline(cin, password);
	
	    // Create and add the new professor
	    Professor newProfessor(firstName, lastName, profID, password);
	    allProfessors.addProfessor(newProfessor);
	
	    cout << "\t\033[32mProfessor " << firstName << " " << lastName << " added successfully.\033[0m\n";
	}

    void assignProfessorToCourse() {
    if (allProfessors.empty()) {
    	system("CLS");
    	cout << "\n\t-------------------------------------------------------------------------------------\n"
			 << "\t                                    ASSIGN PROFESSOR"
			 << "\n\t-------------------------------------------------------------------------------------\n";
        cout << "\n\tNo professors available to assign.\n";
        system("PAUSE");
        return;
    }

    // Display all courses and prompt for selection
    string dept, prog;
    system("CLS");
    cout << "\n\t---------------------------------------------------------------------------------------\n"
		 << "\t                                       ASSIGN PROFESSOR"
		 << "\n\t---------------------------------------------------------------------------------------\n";
    validateDepartmentAndProgram(dept, prog);
    allCourses.setCurriculumStrategy(new CurriculumAllCourses());
    allCourses.viewCurriculum(dept, prog);
    string courseCode = getValidStringInput("\n\tEnter the Course Code to assign a Professor: ");
    courseCode = convertToUpper(courseCode);
    Course* course = allCourses.searchCourse(courseCode);

    if (!course) {
        cout << "\tCourse not found.\n";
        return;
    }
    // Display all professors and prompt for selection
    allProfessors.displayAllProfessors();
    string profID = getValidStringInput("\n\tEnter the Professor ID to assign to this course: ");
    profID = convertToUpper(profID);
    Professor* professor = allProfessors.findProfessor(profID);

    if (!professor) {
        cout << "\tProfessor not found.\n";
        return;
    }
    // Assign the course to the professor
    professor->assignCourse(course);
    course->setProfessor(*professor); // Link course to professor
    cout << "\t\033[32mProfessor " << professor->getFirstName() << " " << professor->getLastName()
         << " assigned to course " << course->getCourseCode() << " successfully.\033[0m\n";
}

	void displayAllProfessors(){
		system("CLS");
		cout << "\n\t---------------------------------------------------------------------------------------\n"
			 << "\t                                      ALL PROFESSORS"
			 << "\n\t---------------------------------------------------------------------------------------\n\n";
		allProfessors.displayAllProfessors();
	}

};

//done. dont think im done w the colors
void adminMenu(Admin& admin, AllCourses& courses) {
    int choice;
    do {
    	system("CLS");
        cout << "\n\t------------------------------------------------------\n"
			 << "\t                        ADMIN MENU"
			 << "\n\t------------------------------------------------------\n"
             << "\n\t1. Student Management\n"
             << "\t2. Professor Management\n"
             << "\t3. Course Management\n"
             << "\t4. Log Out\n"
             << "\t5. Exit\n";
        choice = getValidIntegerInput("\n\tEnter your choice: ");

        switch (choice) {
            case 1: { // Student Management
                int studentChoice;
                do {
                	system("CLS");
                    cout << "\n\t------------------------------------------------------\n"
						 << "\t                  STUDENT MANAGEMENT MENU"
						 << "\n\t------------------------------------------------------\n"
                    	 << "\n\t1. Display All Students\n"
                         << "\t2. Add Student\n"
                         << "\t3. Remove Student\n"
                         << "\t4. Edit Student Details\n"
                         << "\t5. Back to Admin Menu\n";
                    studentChoice = getValidIntegerInput("\n\tEnter your choice: ");

                    switch (studentChoice) {
                    	case 1: 
                    		admin.displayAllStudents();
                    		break;
                        case 2:
                            admin.addStudent();
                            break;
                        case 3:
                            admin.removeStudent();
                            break;
                        case 4:
                            admin.editStudent();
                            break;
                        case 5:
                        	system("CLS");
                            cout << "\n\tReturning to Admin Menu...\n";
                            break;
                        default:
                            cout << "\n\t\033[31mInvalid choice. Please try again.\033[0m\n";
                            break;
                    }
                cout << endl << "\tPress any key to continue . . . ";  // Adding tab for indentation
				cin.ignore();  // Wait for the user to press a key
                } while (studentChoice != 5);
                break;
            }
            case 2: { // Professor Management
                int professorChoice;
                do {
                	system("CLS");
                    cout << "\n\t------------------------------------------------------\n"
						 << "\t               PROFESSOR MANAGEMENT MENU"
						 << "\n\t------------------------------------------------------\n"
                    	 << "\n\t1. Display All Professors\n"
                         << "\t2. Add Professor\n"
                         << "\t3. Assign Professor to a Course\n"
                         << "\t4. Back to Admin Menu\n";
                    professorChoice = getValidIntegerInput("\n\tEnter your choice: ");

                    switch (professorChoice) {
                    	case 1:
                    		admin.displayAllProfessors();
							break;
                        case 2:
                            admin.addProfessor();
                            break;
                        case 3:
                            admin.assignProfessorToCourse();
                            break;
                        case 4:
                        	system("CLS");
                            cout << "\n\tReturning to Admin Menu...\n";
                            break;
                        default:
                            cout << "\n\t\033[31mInvalid choice. Please try again.\033[0m\n";
                            break;
                    }
                cout << endl << "\tPress any key to continue . . . ";  // Adding tab for indentation
				cin.ignore();  // Wait for the user to press a key
                } while (professorChoice != 4);
                break;
            }
            case 3: { // Course Management
                int courseChoice;
                do {
                	system("CLS");
                    cout << "\n\t------------------------------------------------------\n"
						 << "\t                 COURSE MANAGEMENT MENU"
						 << "\n\t------------------------------------------------------\n"
                         << "\n\t1. Add Course\n"
                         << "\t2. Edit Course\n"
                         << "\t3. Remove Course\n"
                         << "\t4. View Curriculum\n"
                         << "\t5. Back to Admin Menu\n";
                    courseChoice = getValidIntegerInput("\n\tEnter your choice: ");

                    switch (courseChoice) {
                        case 1:
                            admin.addCourse();
                            break;
                        case 2:
                            admin.editCourse(courses);
                            break;
                        case 3:
                            admin.removeCourse();
                            break;
                        case 4: {
                            string dept, prog;
                            validateDepartmentAndProgram(dept, prog);
                            system("CLS");
                            cout << "\n\t------------------------------------------------------\n"
								 << "\t            Select Curriculum View Strategy\n"
								 << "\t--------------------------------------------------------\n"
                                 << "\n\t   1. View by Year\n"
                                 << "\t   2. View All Courses\n";
                            int strategyChoice = getValidIntegerInput("\n\tEnter your choice: ");
                            if (strategyChoice == 1) {
                                courses.setCurriculumStrategy(new CurriculumByYear());
                            } else if (strategyChoice == 2) {
                                courses.setCurriculumStrategy(new CurriculumAllCourses());
                            } else {
                                cout << "\n\t\033[31mInvalid choice.\033[0m\n";
                            }
                            courses.viewCurriculum(dept, prog);
                            break;
                        }
                        case 5:
                        	system("CLS");
                            cout << "\n\tReturning to Admin Menu...\n";
                            break;
                        default:
                            cout << "\n\t\033[31mInvalid choice. Please try again.\033[0m\n";
                            break;
                    }
                cout << endl << "\tPress any key to continue . . . ";  
				cin.ignore();  // Wait for the user to press a key
                } while (courseChoice != 5);
                break;
            }
            case 4:
            	system("CLS");
                cout << "\n\tLogging out...\n";
                break;
            case 5:
            	system("CLS");
                cout << "\n\t-Exiting...\n";
                exit(0);
            default:
                cout << "\n\t\033[31mInvalid choice. Please try again.\033[0m\n";
                break;
        }
    } while (choice != 4);
}

void studentMenu(Student& student, AllCourses& allCourses) {
    int choice;

    do {
        // Display student information and menu options
        student.displayUser();
        choice = getValidIntegerInput("\n\tSTUDENT MENU\n"
                                      "\t1. View Enrolled Courses\n"
                                      "\t2. Add Course\n"
                                      "\t3. Manage Payments\n"
                                      "\t4. Drop Course\n"
                                      "\t5. View Curriculum\n"
                                      "\t6. Log Out\n"
                                      "\t7. Exit\n\t--> ");
        system("CLS");

        switch (choice) {
            case 1: {
                // Display the courses the student is enrolled in
                student.viewEnrolledCourses();
                break;
            }
            case 2: {
			    string courseCode;
			
			    // Display courses based on the student's department, program, and year level
			    allCourses.displayCoursesByCategory(student.getDepartment(), student.getProgram(), student.getYearLevel());
			    cout << "\n\t\033[33mEnter 'X' if done.\033[0m\n";
			
			    do {
			        courseCode = getValidStringInput("\n\tEnter the Course Code to add: ");
			        courseCode = convertToUpper(courseCode);
			
			        if (courseCode == "X") {
			            break; // Exit the loop if the user enters 'X'
			        }
			
			        // Search for the course in all available courses
			        Course* courseToEnroll = nullptr;
			        for (auto& course : allCourses.getAllCourses()) { // Assuming getAllCourses() returns a list of all courses
			            if (course->getCourseCode() == courseCode) {
			                if (course->getCourseProg() == student.getProgram() && course->getCourseYear() == student.getYearLevel()) {
			                    courseToEnroll = course; // No need to use const_cast, just work directly with the pointer
			                    break;
			                } else {
			                    cout << "\t\033[31mError: " << course->getCourseName()
			                         << " is not available for your program or year level.\033[0m" << endl;
			                    courseToEnroll = nullptr;
			                    break;
			                }
			            }
			        }
			
			        // Handle enrollment or error if course not found
			        if (courseToEnroll) {
			            student.enrollCourse(*courseToEnroll);
			        } else if (courseCode != "X") {
			            cout << "\t\033[31mCourse not found!\033[0m" << endl;
			        }
			    } while (true);
			
			    break;
			}

            case 3: {
                // Manage payments
                student.viewEnrolledCoursesWithPayment();
                break;
            }
            case 4: {
                // Allow the student to drop a course
                student.viewEnrolledCourses();
                string courseCode = getValidStringInput("\tEnter the Course Code to drop: ");
                courseCode = convertToUpper(courseCode);
                student.dropCourse(courseCode);
                break;
            }
            case 5: {
                // View the curriculum for the student's program and department
                allCourses.setCurriculumStrategy(new CurriculumAllCourses());
                allCourses.viewCurriculum(student.getDepartment(), student.getProgram());
                break;
            }
            case 6:
                // Return to the main menu
                cout << "\tLogging out..." << endl;
                break;
            case 7:
                // Exit the program
                exit(0);
            default:
                cout << "\t\033[31mInvalid choice! Please select again.\033[0m" << endl;
        }
	cout << endl << "\tPress any key to continue . . . ";
    cin.ignore();  // Wait for the user to press a key
    system("CLS");
    } while (choice != 6);  // Exit the student menu when choice is 6
}

//done. dont think im done w the colors
void profMenu(Professor& professor, AllCourses& allCourses) {
    int choice;

    do {
        professor.displayUserInfo();  // Display professor's basic information

        // Present the professor menu options
        choice = getValidIntegerInput("\n\tPROFESSOR MENU:\n"
                                      "\t1. View Courses and Students\n"
                                      "\t2. Log Out\n"
                                      "\t3. Exit\n\t--> ");
        system("CLS");  // Clear the screen before showing next menu options

        switch (choice) {
            case 1: {
    			professor.viewCoursesAndStudents(&professor);
    			break;
			}
            case 2:
                // Return to the main menu
                cout << "\n\tLogging out...\n";
                break;
            case 3:
                // Exit the program
                exit(0);
                break;
            default:
                cout << "\t\033[31mInvalid choice! Please select again.\033[0m" << endl;
        }

        // Pause to let the user view results before clearing the screen
        if (choice != 2) {
            cout << endl << "\tPress any key to continue . . . ";  // Adding tab for indentation
			cin.ignore();  // Wait for the user to press a key
            system("CLS");
        }

    } while (choice != 2);  // Exit the professor menu when choice is 2
}

int main() {
    int userType;
    string firstName, lastName, studentID, department, program;
    int yearLevel;
    string username, password, studentPassword;
    AllStudents& allStudents = AllStudents::getInstance();
    AllCourses& allCourses = AllCourses::getInstance();
    AllProfessors& allProfessors = AllProfessors::getInstance();
    Admin admin("admin", "admin123", allStudents, allCourses, allProfessors); 
        
    do {
        cout << "\n\033[32m        ______                 ____                     __    _____            __               \n"
             << "       / ____/___  _________  / / /___ ___  ___  ____  / /_  / ___/__  _______/ /____  ____ ___ \n"
             << "      / __/ / __ \\/ ___/ __ \\/ / / __ `__ \\/ _ \\/ __ \\/ __/  \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\\n"
             << "     / /___/ / / / /  / /_/ / / / / / / / /  __/ / / / /_   ___/ / /_/ (__  ) /_/  __/ / / / / /\n"
             << "    /_____/_/ /_/_/   \\____/_/_/_/ /_/ /_/\\___/_/ /_/\\__/  /____/\\__, /____/\\__/\\___/_/ /_/ /_/  \n"
             << "                                                                /____/    \033[0m\n";

        cout << "\n\n\t\t\t 1. Admin \n"
             << "\t\t\t 2. Student \n"
             << "\t\t\t 3. Professor \n"
             << "\t\t\t 4. Exit \n";
             
        userType = getValidIntegerInput("\t\t\t     --> ");
        switch(userType) {
            case 1: {
            //	system("PAUSE");
            	system("CLS");
            	cout << "\n\t------------------------------------------------------" << endl;
            	cout << "\t                  A D M I N   L O G I N";
            	cout << "\n\t------------------------------------------------------" << endl;
                cout << "\n\t\tEnter Admin Username: ";
                getline(cin, username);
                cout << "\n\t\tEnter Password: ";
                getline(cin, password);

                // Simple admin login check
                if (username == admin.getUsername() && password == admin.getPassword()) {
                	cout << endl << "\t\tPress any key to continue . . . ";  // Adding tab for indentation
					cin.ignore();  // Wait for the user to press a key
					
            		system("CLS");
                    adminMenu(admin, allCourses);
                } else {
                    cout << "\033[31m\n\t\tInvalid username or password!\033[0m\n";
                }
                break;
            }
            case 2: {
            	if(allStudents.empty()){
            		system("CLS");
            		cout << "\n\t\t----------------------------------------------" << endl;
            		cout << "\t\t\t  S T U D E N T   L O G I N";
            		cout << "\n\t\t----------------------------------------------" << endl;
            		cout << "\n\t\t\tNo students in the system yet.\n";
            		cout << endl << "\t\tPress any key to continue . . . ";  // Adding tab for indentation
					cin.ignore();  // Wait for the user to press a key
					system("CLS");
            		break;
				}
				system("CLS");
				cout << "\n\t------------------------------------------------------" << endl;
            	cout << "\t\t     S T U D E N T   L O G I N";
            	cout << "\n\t------------------------------------------------------" << endl;
                string studentID = getValidStringInput("\n\t\tEnter Student ID: ");
                studentPassword = getValidStringInput("\n\t\tEnter Password: ");
                Student* student = allStudents.findStudent(studentID);
                if (student && studentPassword == student->getPassword()) {
                    studentMenu(*student, allCourses);
                } else {
                    cout << "\n\t\t\033[31mInvalid Student ID or Password.\033[0m" << endl;
                    cout << endl << "\t\tPress any key to continue . . . ";  // Adding tab for indentation
					cin.ignore();  // Wait for the user to press a key
					system("CLS");
                }
                break;
            }
            case 3: {
            	if(allProfessors.empty()){
            		system("CLS");
            		cout << "\n\t\t------------------------------------------------" << endl;
            		cout << "\t\t\t  P R O F E S S O R   L O G I N";
            		cout << "\n\t\t------------------------------------------------" << endl;
            		cout << "\n\t\t\tNo professors in the system yet.\n";
            		break;
				}
				system("CLS");
				cout << "\n\t------------------------------------------------------" << endl;
            	cout << "\t\tP R O F E S S O R   L O G I N";
            	cout << "\n\t------------------------------------------------------" << endl;
                string profID = getValidStringInput("\n\t\tEnter Professor ID: ");
    			string profPassword = getValidStringInput("\n\t\tEnter Password: ");
    			Professor* professor = allProfessors.findProfessor(profID);

    			if (professor && professor->getPassword() == profPassword) {
        			system("CLS");
        			profMenu(*professor, allCourses);
    			} else {
        			cout << "\n\t\t\033[31mInvalid Professor ID or Password.\033[0m\n";
    			}
    			break;
            }
            case 4: {
            	system("CLS");
                cout << "\tExiting Program..." << endl;
                break;
            }
            default: {
                cout << "\t\t\t\033[31mInvalid choice! Try again.\033[0m" << endl;
                break;
            }
        }

        if (userType != 4 && userType != 2) {
            cout << endl << "\t\tPress any key to continue . . . ";  // Adding tab for indentation
			cin.ignore();  // Wait for the user to press a key
			system("CLS");

        }

    } while (userType != 4);  // Program will keep running until user chooses to exit
    return 0;
}