// Online C compiler to run C program online
#include <stdio.h>

#include <string.h>
#include <ctype.h>

typedef struct subject
{
    char course_id[14];
    float grades;
} subject;

typedef struct student
{
    long long int id;
    char name[30];
    char email[30];
    char status[14];
    char presence[9];
    int current_semester;
    subject transcript[5];
    float average;
} Student;

typedef struct courseload
{
    char course_id[14];
    int sem;
} Courseload;

typedef struct teacher
{
    long long int id;
    char name[30];
    long long int mobile;
    char status[11];
    float seniority;
    int semester;
    Courseload courseload[5];
} Teacher;

typedef struct course
{
    char id[14];
    char name[30];
    int hours;
    int semester;
} Course;

void fillStudentInfo(int);
void fillTeacherInfo(int);
void fillCourseInfo(int);
void fillHardStudentInfo();
void fillHardTeacherInfo();
void fillHardCourseInfo();
void displayStudentRecord(int);
void displayTeacherRecord(int);
void displayCourseRecord(int);
int isFound(int);

struct student students[250];
struct teacher teachers[25];
struct course courses[35];

int main()
{
    char ans;
    int menu, index;
    int category, sub_category;
    int num_students = 0;
    int num_teachers = 0;
    int num_courses = 0;
    long long int temp_id;
    int sem;
    char course_name[30];
    float num_international = 0;
    float sum_grades = 0;
    int counter = 0;
    char id[14];

    fillHardStudentInfo();
    fillHardTeacherInfo();
    fillHardCourseInfo();

    do
    {

        printf("\nEnter the number of the menus below.\n1. Data Entry\n2. Display a record\n3. update a record\n4. List Current Classes\n5. Run stats\n6. Display all Records\n7. Exit\n\n");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1: // Data Entry.

            printf("\nData Entry.\n");
            printf("Enter the number of the category.\n1. Student\n2. Teacher \n3. Course \n\n");
            scanf("%d", &category);

            switch (category)
            {
            case 1:
                printf("How many students ?\n");
                scanf(" %d", &num_students);
                fillStudentInfo(num_students);
                break;
            case 2:
                printf("How many teachers ?\n");
                scanf(" %d", &num_teachers);
                fillTeacherInfo(num_teachers);
                break;
            case 3:
                printf("How many courses ?\n");
                scanf(" %d", &num_courses);
                fillCourseInfo(num_courses);
                break;
            }
            break;

        case 2: // Display a Record.

            printf("\nDisplay a Record.\n");
            printf("Enter the number of the category\n1. Student\n2. Teacher \n3. Course \n\n");
            scanf("%d", &category);

            switch (category)
            {
            case 1:
                index = isFound(category);
                if (index != -1)
                    displayStudentRecord(index);
                break;
            case 2:
                index = isFound(category);
                if (index != -1)
                    displayTeacherRecord(index);
                break;
            case 3:
                index = isFound(category);
                if (index != -1)
                    displayCourseRecord(index);
                break;
            }
            break;
        case 3: // Update a Record.

            printf("\nUpdate a Record.\n");
            printf("Enter the number of the category \n1.Student \n2.Teacher \n\n");
            scanf("%d", &category);

            switch (category)
            {
            case 1:
                index = isFound(category);
                if (index != -1)
                {
                    printf("Edit.\n");

                    printf("\nStatus (Local / International): ");
                    scanf(" %s", students[index].status);

                    printf("Presence (Montreal / Abroad): ");
                    scanf("%s", students[index].presence);
                    do
                    {
                        printf("Current Semester: ");
                        scanf("%d", &students[index].current_semester);

                    } while (students[index].current_semester < 1 || students[index].current_semester > 4);

                    for (int j = 0; j < 5; j++)
                    {
                        printf("Course %d ID: ", j + 1);
                        scanf("%s", students[index].transcript[j].course_id);
                        printf("Course %d Grade : ", j + 1);
                        scanf("%f", &students[index].transcript[j].grades);
                    }

                    float total_grades = 0;
                    for (int k = 0; k < 5; k++)
                    {
                        total_grades = students[index].transcript[k].grades + total_grades;
                    }
                    students[index].average = (total_grades / 5);
                    printf("\nCurrent Average: %.2f", students[index].average);
                }
                break;
            case 2:
                index = isFound(category);
                if (index != -1)
                {
                    printf("Edit.\n");
                    printf("\nStatus (Permanent/Part-Time): ");
                    scanf(" %s", teachers[index].status);

                    do
                    {
                        printf("Seniority (0.0 - 20.0): ");
                        scanf("%f", &teachers[index].seniority);
                    } while (teachers[index].seniority < 0.0 || teachers[index].seniority > 20.0);

                    printf("Course Load: \n");
                    for (int j = 0; j < 5; j++)
                    {
                        printf("Course %d ID: ", j + 1);
                        scanf("%s", teachers[index].courseload[j].course_id);
                    }
                }
                break;
            default:
                break;
            }
            break;
        case 4: // List Current Classes.

            printf("\nList Current Classes.\n");
            printf("Enter the ID: ");
            scanf("%lld", &temp_id);

            for (int i = 0; i < 250; i++)
            {
                if (students[i].id == temp_id)
                {
                    sem = students[i].current_semester;
                    printf("\nSem : %d\n", sem);
                }
            }

            for (int i = 0; i < 35; i++)
            {
                if (courses[i].semester == sem)
                {

                    for (int j = 0; j < 25; j++)
                    {
                        for (int k = 0; k < 5; k++)
                        {
                            if (strcmp(teachers[j].courseload[k].course_id, courses[i].id) == 0)
                            {
                                printf("Course Id: %s -  %s\n", courses[i].id, teachers[j].name);
                            }
                        }
                    }
                }
            }

        default:
            break;
        case 5: // Run Stats

            if (num_students > 0)
            {
                for (int i = 0; i < 250; i++)
                {
                    if ((strcmp(students[i].status, "International") == 0) && strcmp(students[i].presence, "Abroad") == 0)
                    {
                        counter++;
                        num_international = num_international + counter;
                    }
                }
                printf("Total International Students Abraod: %.2f ", (num_international / 250));
                return 0;
            }
            else
            {
                for (int i = 0; i < 250; i++)
                {
                    if ((strcmp(students[i].status, "International") == 0) && strcmp(students[i].presence, "Abroad") == 0)
                    {
                        counter++;
                        num_international = num_international + counter;
                    }
                }
                printf("Total International Students Abraod: %.2f ", (num_international / 8));
            }

            //Distribution.

            printf("\n\nDistrbution of grades.\n");
            printf("Course ID: ");

            scanf("%s", id);
            printf("\n");

            for (int i = 0; i < 250; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (strcmp(students[i].transcript[j].course_id, id) == 0)
                    {
                        sum_grades += students[i].transcript[j].grades;
                        printf("Student %d : Grade : %.2f\n", i + 1, students[i].transcript[j].grades);
                    }
                }
            }
            if (sum_grades < 1)
            {
                printf("No records Found...\n");
            }
            else
            {
                printf("\nSum_grades: %.2f\n", sum_grades);
                printf("\nCourse Distribution Grade(%s) :  %.2f", id, (sum_grades / 8));
            }
            break;
        case 6: // Display all records.

            printf("\nDisplay all records\n");
            printf("Enter the number of the category \n1.Student \n2.Teacher \n3.Course \n\n");
            scanf("%d", &category);

            switch (category)
            {
            case 1:
                for (int i = 0; i < 8; i++)
                {
                    displayStudentRecord(i);
                }

                break;
            case 2:
                for (int i = 0; i < 4; i++)
                {
                    displayTeacherRecord(i);
                }

                break;
            case 3:
                for (int i = 0; i < 5; i++)
                {
                    displayCourseRecord(i);
                }

                break;

            default:
                break;
            }

            break;
        case 7:
            return 0;
            break;
        }

        printf("\nWant to continue ? (Y/N): ");
        scanf(" %c", &ans);
    } while (ans == 'Y' || ans == 'y');
    return 0;
}
void fillStudentInfo(int num_students)
{
    for (int i = 0; i < num_students; i++)
    {
        printf("\nStudent %d\n\n", i + 1);
        printf("ID: ");
        scanf("%lld", &students[i].id);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Email: ");
        scanf("%s", students[i].email);
        printf("Status (Local / International): ");
        scanf("%s", students[i].status);
        printf("Presence (Montreal / Abroad): ");
        scanf("%s", students[i].presence);

        do
        {
            printf("Current Semester: ");
            scanf("%d", &students[i].current_semester);
        } while (students[i].current_semester < 1 || students[i].current_semester > 4);

        printf("\nGrades (per each course)\n");

        for (int j = 0; j < 5; j++)
        {
            printf("Course %d ID: ", j + 1);
            scanf("%s", students[i].transcript[j].course_id);
            printf("Course %d Grade : ", j + 1);
            scanf("%f", &students[i].transcript[j].grades);
        }
        printf("\nCurrent Average: ");
        scanf("%f", &students[i].average);
    }
}
void fillTeacherInfo(int num_teachers)
{
    for (int i = 0; i < num_teachers; i++)
    {
        printf("\nTeacher %d\n\n", i + 1);
        printf("ID: ");
        scanf("%lld", &teachers[i].id);
        printf("Name: ");
        scanf("%s", teachers[i].name);
        printf("Mobile: ");
        scanf("%lld", &teachers[i].mobile);
        printf("Status (Permanent / Part-Timer): ");
        scanf("%s", teachers[i].status);
        printf("Seniority (0.0 - 20.0): ");
        scanf("%f", &teachers[i].seniority);
        do
        {
            printf("Current Semester: ");
            scanf("%d", &students[i].current_semester);
        } while (students[i].current_semester < 1 || students[i].current_semester > 4);

        printf("Course Load: \n");

        for (int j = 0; j < 5; j++)
        {
            printf("Course %d ID: ", j + 1);
            scanf("%s", teachers[i].courseload[j].course_id);
        }
        printf("\n");
    }
}
void fillCourseInfo(int num_courses)
{
    for (int i = 0; i < num_courses; i++)
    {

        printf("\nID: ");
        scanf("%s", courses[i].id);
        printf("Name: ");
        scanf("%s", courses[i].name);
        printf("Hours: ");
        scanf("%d", &courses[i].hours);
        printf("Semester: ");
        scanf("%d", &courses[i].semester);
    }
}
void displayStudentRecord(int index)
{
    printf("\nStudent : %d\n", index + 1);
    printf("ID  %lld\n", students[index].id);
    printf("Name: %s\n", students[index].name);
    printf("Email: %s\n", students[index].email);
    printf("Status: %s\n", students[index].status);
    printf("Presence: %s\n", students[index].presence);
    printf("Semester: %d\n", students[index].current_semester);
    for (int j = 0; j < 5; j++)
    {
        printf("\nCourse ID : %s\n", students[index].transcript[j].course_id);
        printf("Grade : %.2f\n", students[index].transcript[j].grades);
    }
    printf("\nAverage: %.2f\n", students[index].average);
}
void displayTeacherRecord(int index)
{
    printf("\n\nTeacher %d\n", index + 1);
    printf("ID  %lld\n", teachers[index].id);
    printf("Name: %s\n", teachers[index].name);
    printf("Mobile: %lld\n", teachers[index].mobile);
    printf("Status: %s\n", teachers[index].status);
    printf("Seniority: %.2f\n", teachers[index].seniority);
    printf("Course Load (per sem): ");
    for (int i = 0; i < 5; i++)
    {
        printf("\nCourse %d - %s", i + 1, teachers[index].courseload[i].course_id);
    }
}
void displayCourseRecord(int index)
{
    printf("\nCourse %d\n", index + 1);
    printf("ID  %s\n", courses[index].id);
    printf("Name: %s\n", courses[index].name);
    printf("Hours: %d\n", courses[index].hours);
    printf("Semester: %d\n", courses[index].semester);
}
void fillHardStudentInfo()
{
    students[0].id = 2030150;
    strcpy(students[0].name, "Aafrin");
    strcpy(students[0].email, "aafrinsayani@gmail.com");
    strcpy(students[0].status, "International");
    strcpy(students[0].presence, "Montreal");
    students[0].current_semester = 1;
    strcpy(students[0].transcript[0].course_id, "14323KL");
    strcpy(students[0].transcript[1].course_id, "124HkSD");
    strcpy(students[0].transcript[2].course_id, "23435KJ");
    strcpy(students[0].transcript[3].course_id, "72654FK");
    strcpy(students[0].transcript[4].course_id, "2323SJD");
    students[0].transcript[0].grades = 98;
    students[0].transcript[1].grades = 97;
    students[0].transcript[2].grades = 96;
    students[0].transcript[3].grades = 95;
    students[0].transcript[4].grades = 99;
    students[0].average = 97;

    students[1].id = 2787654;
    strcpy(students[1].name, "Rajdeep");
    strcpy(students[1].email, "rajdeep@gmail.com");
    strcpy(students[1].status, "International");
    strcpy(students[1].presence, "Montreal");
    students[1].current_semester = 1;
    strcpy(students[1].transcript[0].course_id, "14323KL");
    strcpy(students[1].transcript[1].course_id, "124HkSD");
    strcpy(students[1].transcript[2].course_id, "23435KJ");
    strcpy(students[1].transcript[3].course_id, "72654FK");
    strcpy(students[1].transcript[4].course_id, "2323SJD");
    students[1].transcript[0].grades = 98;
    students[1].transcript[1].grades = 97;
    students[1].transcript[2].grades = 96;
    students[1].transcript[3].grades = 95;
    students[1].transcript[4].grades = 99;
    students[1].average = 97;

    students[2].id = 2456765;
    strcpy(students[2].name, "ruchit");
    strcpy(students[2].email, "ruchitthakkar@gmail.com");
    strcpy(students[2].status, "International");
    strcpy(students[2].presence, "Montreal");
    students[2].current_semester = 1;
    strcpy(students[2].transcript[0].course_id, "14323KL");
    strcpy(students[2].transcript[1].course_id, "124HkSD");
    strcpy(students[2].transcript[2].course_id, "23435KJ");
    strcpy(students[2].transcript[3].course_id, "72654FK");
    strcpy(students[2].transcript[4].course_id, "2323SJD");
    students[2].transcript[0].grades = 98;
    students[2].transcript[1].grades = 97;
    students[2].transcript[2].grades = 96;
    students[2].transcript[3].grades = 95;
    students[2].transcript[4].grades = 99;
    students[2].average = 97;

    students[3].id = 2345676;
    strcpy(students[3].name, "mei");
    strcpy(students[3].email, "meiaili@gmail.com");
    strcpy(students[3].status, "Local");
    strcpy(students[3].presence, "Montreal");
    students[3].current_semester = 1;
    strcpy(students[3].transcript[0].course_id, "14323KL");
    strcpy(students[3].transcript[1].course_id, "124HkSD");
    strcpy(students[3].transcript[2].course_id, "23435KJ");
    strcpy(students[3].transcript[3].course_id, "72654FK");
    strcpy(students[3].transcript[4].course_id, "2323SJD");
    students[3].transcript[0].grades = 98;
    students[3].transcript[1].grades = 97;
    students[3].transcript[2].grades = 96;
    students[3].transcript[3].grades = 95;
    students[3].transcript[4].grades = 99;
    students[3].average = 97;
    students[4].id = 2676543;

    strcpy(students[4].name, "gunreet");
    strcpy(students[4].email, "gunreetkaur@gmail.com");
    strcpy(students[4].status, "International");
    strcpy(students[4].presence, "Abroad");
    students[4].current_semester = 1;
    strcpy(students[4].transcript[0].course_id, "14323KL");
    strcpy(students[4].transcript[1].course_id, "124HkSD");
    strcpy(students[4].transcript[2].course_id, "23435KJ");
    strcpy(students[4].transcript[3].course_id, "72654FK");
    strcpy(students[4].transcript[4].course_id, "2323SJD");
    students[4].transcript[0].grades = 98;
    students[4].transcript[1].grades = 97;
    students[4].transcript[2].grades = 96;
    students[4].transcript[3].grades = 95;
    students[4].transcript[4].grades = 99;
    students[4].average = 97;

    students[5].id = 2345465;
    strcpy(students[5].name, "kamaldeep");
    strcpy(students[5].email, "kamaldeepsingh@gmail.com");
    strcpy(students[5].status, "International");
    strcpy(students[5].presence, "Abroad");
    students[5].current_semester = 1;
    strcpy(students[5].transcript[0].course_id, "14323KL");
    strcpy(students[5].transcript[1].course_id, "124HkSD");
    strcpy(students[5].transcript[2].course_id, "23435KJ");
    strcpy(students[5].transcript[3].course_id, "72654FK");
    strcpy(students[5].transcript[4].course_id, "2323SJD");
    students[5].transcript[0].grades = 98;
    students[5].transcript[1].grades = 97;
    students[5].transcript[2].grades = 96;
    students[5].transcript[3].grades = 95;
    students[5].transcript[4].grades = 99;
    students[5].average = 97;

    students[6].id = 2430984;
    strcpy(students[6].name, "amit");
    strcpy(students[6].email, "amitgarg@gmail.com");
    strcpy(students[6].status, "International");
    strcpy(students[6].presence, "Abroad");
    students[6].current_semester = 1;
    strcpy(students[6].transcript[0].course_id, "14323KL");
    strcpy(students[6].transcript[1].course_id, "124HkSD");
    strcpy(students[6].transcript[2].course_id, "23435KJ");
    strcpy(students[6].transcript[3].course_id, "72654FK");
    strcpy(students[6].transcript[4].course_id, "2323SJD");
    students[6].transcript[0].grades = 98;
    students[6].transcript[1].grades = 97;
    students[6].transcript[2].grades = 96;
    students[6].transcript[3].grades = 95;
    students[6].transcript[4].grades = 99;
    students[6].average = 97;

    students[7].id = 2540987;
    strcpy(students[7].name, "stephen");
    strcpy(students[7].email, "stephenma@gmail.com");
    strcpy(students[7].status, "Local");
    strcpy(students[7].presence, "Montreal");
    students[7].current_semester = 1;
    strcpy(students[7].transcript[0].course_id, "14323KL");
    strcpy(students[7].transcript[1].course_id, "124HkSD");
    strcpy(students[7].transcript[2].course_id, "23435KJ");
    strcpy(students[7].transcript[3].course_id, "72654FK");
    strcpy(students[7].transcript[4].course_id, "2323SJD");
    students[7].transcript[0].grades = 98;
    students[7].transcript[1].grades = 97;
    students[7].transcript[2].grades = 96;
    students[7].transcript[3].grades = 95;
    students[7].transcript[4].grades = 99;
    students[7].average = 97;
}
void fillHardTeacherInfo()
{
    teachers[0].id = 123456;
    strcpy(teachers[0].name, "Michelle");
    teachers[0].mobile = 5149512343;
    strcpy(teachers[0].status, "permanent");
    teachers[0].seniority = 20.0;
    strcpy(teachers[0].courseload[0].course_id, "14323KL");
    strcpy(teachers[0].courseload[1].course_id, "24323KL");
    strcpy(teachers[0].courseload[2].course_id, "6323SJD");
    strcpy(teachers[0].courseload[3].course_id, "9823KL");
    strcpy(teachers[0].courseload[4].course_id, "2723SJD");

    teachers[1].id = 788922;
    strcpy(teachers[1].name, "Dara Aghamirkarimi");
    teachers[1].mobile = 5149512943;
    strcpy(teachers[1].status, "permanent");
    teachers[1].seniority = 19.1;
    strcpy(teachers[1].courseload[0].course_id, "124HkSD");
    strcpy(teachers[1].courseload[1].course_id, "324HkSD");
    strcpy(teachers[1].courseload[2].course_id, "25HkSD");
    strcpy(teachers[1].courseload[3].course_id, "14325KL");
    strcpy(teachers[1].courseload[4].course_id, "124H5SD");

    teachers[2].id = 787373;
    strcpy(teachers[2].name, "Alice");
    teachers[2].mobile = 514951443;
    strcpy(teachers[2].status, "Part-Timer");
    teachers[2].seniority = 18.5;
    strcpy(teachers[2].courseload[0].course_id, "23435KJ");
    strcpy(teachers[2].courseload[1].course_id, "43435KJ");
    strcpy(teachers[2].courseload[2].course_id, "26435KJ");
    strcpy(teachers[2].courseload[3].course_id, "23435HJ");
    strcpy(teachers[2].courseload[4].course_id, "2326SJD");

    teachers[3].id = 123446;
    strcpy(teachers[3].name, "Mohsen Yahia");
    teachers[3].mobile = 5149513343;
    strcpy(teachers[3].status, "permanent");
    teachers[3].seniority = 20.0;
    strcpy(teachers[3].courseload[0].course_id, "72654FK");
    strcpy(teachers[3].courseload[1].course_id, "52654FK");
    strcpy(teachers[3].courseload[2].course_id, "77654FK");
    strcpy(teachers[3].courseload[3].course_id, "72664FK");
    strcpy(teachers[3].courseload[4].course_id, "2323SJD");
}
void fillHardCourseInfo()
{
    strcpy(courses[0].id, "14323KL");
    strcpy(courses[0].name, "Algorithms & Programming");
    courses[0].hours = 90;
    courses[0].semester = 1;

    strcpy(courses[1].id, "124HkSD");
    strcpy(courses[1].name, "Databases");
    courses[1].hours = 90;
    courses[1].semester = 1;

    strcpy(courses[2].id, "23435KJ");
    strcpy(courses[2].name, "Computer Tools");
    courses[2].hours = 92;
    courses[2].semester = 1;

    strcpy(courses[3].id, "72654FK");
    strcpy(courses[3].name, "Introduction to web development");
    courses[3].hours = 93;
    courses[3].semester = 1;

    strcpy(courses[4].id, "2323SJD");
    strcpy(courses[4].name, "Computer Architechture");
    courses[4].hours = 94;
    courses[4].semester = 1;
}
int isFound(int category)
{
    long long int id;
    char course_id[14];

    printf("Enter ID: ");
    if (category != 3)
    {
        scanf("%lld", &id);
    }
    else
    {
        scanf("%s", course_id);
    }

    switch (category)
    {
    case 1:
        for (int i = 0; i < 250; i++)
        {

            if (id == students[i].id)
            {
                printf("\nRecords found......\n\n");
                return i;
            }
        }
        printf("\nNo records found.\n\n");
        return -1;

        break;
    case 2:
        for (int i = 0; i < 8; i++)
        {
            if (id == teachers[i].id)
            {
                printf("\nRecords found......\n\n");
                return i;
            }
        }
        printf("\nNo records found.\n\n");
        return -1;
        break;
    case 3:
        for (int i = 0; i < 8; i++)
        {
            if (strcmp(course_id, courses[i].id) == 0)
            {
                printf("\nRecords found......\n\n");
                return i;
            }
        }
        printf("\nNo records found.\n\n");
        return -1;
        break;
    }
    return 0;
}


