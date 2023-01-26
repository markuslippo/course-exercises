

// A student structure with arrays of information: 
// Student number is exactly 6 digits, and there needs to be room for '\0'
// Both first and last name are required to hold at most 20 characters, still requiring to have room for '\0'
// Points in rounds are stored in an array with size 6. When adding a student to database, all six values are 
// initialized to zero. 

typedef struct {
    char studentNumber[7];
    char firstname[21];
    char lastname[21];
    int roundPoints[6];
} Student;


// A database structure that holds information of all the students 
// and the amount of students. 

typedef struct {
    Student *students;       //Dynamic array of all students
    int amount;
} Database;

