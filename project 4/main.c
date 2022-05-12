#define _CRT_SECURE_NO_WARNINGS
/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/ //uncomment this block to check for heap memory allocation leaks.
// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StudentCourseGrade
{
	char courseName[35];
	int grade;
}StudentCourseGrade;

typedef struct Student
{
	char name[35];
	StudentCourseGrade* grades; //dynamic array of courses
	int numberOfCourses;
}Student;


//Part A
void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
int countPipes(const char* lineBuffer, int maxCount);
char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents);
void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor);
void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents);

//Part B
Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents);
void writeToBinFile(const char* fileName, Student* students, int numberOfStudents);
Student* readFromBinFile(const char* fileName);

int main()
{
	//Part A
	int* coursesPerStudent = NULL;
	int numberOfStudents = 0;
	
	/*factorGivenCourse(students, coursesPerStudent, numberOfStudents, "Advanced Topics in C", +5);
	printStudentArray(students, coursesPerStudent, numberOfStudents);*/
	//studentsToFile(students, coursesPerStudent, numberOfStudents); //this frees all memory. Part B fails if this line runs. uncomment for testing (and comment out Part B)

	//Part B
	//Student* transformedStudents = transformStudentArray(students, coursesPerStudent, numberOfStudents);
	//writeToBinFile("students.bin", transformedStudents, numberOfStudents);
	Student* testReadStudents = readFromBinFile("students.bin");

	//add code to free all arrays of struct Student


	/*_CrtDumpMemoryLeaks();*/ //uncomment this block to check for heap memory allocation leaks.
	// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019

	char pipes[] = { "a||b||||" };//chack if countpipes works
	int maxCount = 8;
	char c = 't';
	printf("the amount of '|' is %d", countPipes(&pipes, maxCount, c));
	char name[] = "studentList.txt";
	countStudentsAndCourses("studentList.txt", &coursesPerStudent, &numberOfStudents);
	printf("%d", numberOfStudents);
	printf("\n");
	for (int i = 0; i < 9; i++)
	{
		printf("%d  %p\n",coursesPerStudent[i], &coursesPerStudent[i]);
	}
	char*** students = makeStudentArrayFromFile("studentList.txt", &coursesPerStudent, &numberOfStudents);

	
	return 0;
}

void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents){
	char line[1023];
	int counter = 0;
	FILE *file = fopen(fileName, "r");
	if (!file) {
		puts("cannot open file\n");
		exit(1);
	}
	while (fgets(line,1023,file)!= NULL)
		counter++;
	*numberOfStudents = counter;
	rewind(file);
	int* array = (int*)malloc(counter * sizeof(int));
	if (!array) {
		puts("alocation failed\n");
		exit(1);
	}
	counter = 0;
	while (fgets(line, 1023, file) != NULL) {
		*(array+counter) = countPipes(line, 1023);
		counter++;
	}
	*coursesPerStudent = array;
	fclose(file);
}

int countPipes(const char* lineBuffer, int maxCount)
{
	int i = 0;
	int sum_of_pipe = 0;
	if (lineBuffer == NULL)
		return -1;
	if (maxCount <= 0)
		return 0;
	while (lineBuffer[0] != '\0' && i != maxCount)
	{
		if (lineBuffer[0] == '|')
			sum_of_pipe++;
		i++;
		lineBuffer++;
	}
	return sum_of_pipe;
}

char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	char pipe_psik[3] = "|,";
	char* str;
	char line[1023];
	FILE* file = fopen(fileName, "r");
	if (!file) {
		puts("cannot open file\n");
		exit(1);
	}
	int size = *numberOfStudents;
	char*** triple_array = (char***)malloc(size * sizeof(char**));
	if (!triple_array) {
		puts("alocation failed\n");
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		int numofcourse = *(*(coursesPerStudent)+i);
		*(triple_array+i) = (char**)malloc((numofcourse * 2 + 1)*sizeof(char*));
		if (!*(triple_array + i)) {
			puts("alocation failed\n");
			exit(1);
		}
	}
	int i = 0,length;
	while (fgets(line, 1023, file) != NULL)
	{
		str = strtok(line, pipe_psik);
		while (str != NULL) {
			length = strlen(str);
			*(*(triple_array + i)) = (char*)malloc(length + 1);
			if (!*(*(triple_array + i))) {
				puts("alocation failed");
				exit(1);
			}
			strcpy(*(*(triple_array + i)), str);
			puts(*(*(triple_array + i)));
			str = strtok(NULL, pipe_psik);
			
		}
		}
	fclose(file);
	return(triple_array);
}
	


void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor)
{
	//add code here
}

void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf("name: %s\n*********\n", students[i][0]);
		for (int j = 1; j <= 2 * coursesPerStudent[i]; j += 2)
		{
			printf("course: %s\n", students[i][j]);
			printf("grade: %s\n", students[i][j + 1]);
		}
		printf("\n");
	}
}

void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents)
{
	//add code here
}

void writeToBinFile(const char* fileName, Student* students, int numberOfStudents)
{
	//add code here
}

Student* readFromBinFile(const char* fileName)
{
	//add code here
}

Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents)
{
	//add code here
}
