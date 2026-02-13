// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <cmath>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;

    //Allocate memory for the names
    student.f_name = new char[128];
    student.l_name = new char[128];

    // Sequence of user input -> store in fields of `student`

    //Get Student ID
    std::string id_msg = "Please enter the student's id number: ";

    student.id = promptInt(id_msg, 1, 999999999);

    //Get First Name
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    std::cin.ignore();

    //Get Last Name
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;
    std::cin.ignore();

    //Get Number of Assignments
    std::string assign_msg = "Please enter how many assignments were graded: ";
    student.n_assignments = promptInt(assign_msg, 1, 134217728);
    std::cout << std::endl;

    //Allocate memory for grades
    double *grade_list = new double[student.n_assignments];
    double grade;

    for(int i = 0; i < student.n_assignments; i++){
        std::string grade_msg =  "Please enter grade for assignment " + std::to_string(i) + ": ";
        
        
        grade = promptDouble(grade_msg, 0, 1000.0);
        grade_list[i] = grade;
        
    }
    student.grades = grade_list;


    // Call `CalculateStudentAverage(???, ???)`
    //pass address of student and address of average
    calculateStudentAverage(&student, &average);

    // Output `average`
    std::cout << std::endl;
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;
    std::cout << "  Average grade: " << average << std::endl;

    //Cleanup 
    delete[] student.grades;
    delete[] student.f_name;
    delete[] student.l_name;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    std::string input;

    while (true){
        std::cout << message;

        std::getline(std::cin, input);
     
        //if user hit enter
        if(input.empty()){
            continue;
        }

        int num = 0;

        bool isNum = true;
        //check if it is a valid number
        for (char c : input){
            if (c < '0' || c > '9'){
                isNum = false;
                break;
            }
            //convert char to int
            int digit = c - '0';
            num = (num * 10) + digit;

        }
        if(isNum){
            //check if number meets the range
            if(num >= min && num <= max){
                return num;
            } else{
                std::cout << "Sorry, I cannot understand your answer" << std::endl;  
            }
        }else{
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }
        
    }
    return 0;

}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    std::string input;
    double num = 0.0;

    while (true){
        std::cout << message;
        
        std::getline(std::cin, input);

        //check if it is a valid decimal number
        bool isNum = true;
        for (char c : input){
            if (c == '.'){
                continue;
            }else if(c < '0' || c > '9'){
                isNum = false;
                break;
            }
        }

        if(input.empty()){
            continue;
        }

        if(isNum){
            // string to double
            double digit = 0.0;
            double divisor = 1.0;
            bool dot = false;

            for (char c : input){
                if(c == '.'){
                    dot = true;
                    continue;
                }
                int digit = c - '0';
                if (!dot){
                    //whole number
                num = (num * 10) + digit;
                }else{
                    //decimal part
                    divisor = divisor * 10.0;
                    num = num + (digit / divisor);
                }
            }
            //check range
            if(num >= min && num <= max){
                return num;
            } else{
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
            }
        }else{
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
          
        }
        
    }
    return 0;

}

/*
   object: pointer to anything - your choice! 
   (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade

    Student *s = (Student*)object;

    double total = 0;

    //sum up all grades
    for(int i = 0; i < s->n_assignments; i++){
        total = total + s->grades[i];

    }
    //calculate average
    *avg = std::round((total / s->n_assignments) * 10.0 )/ 10.0;
}
