#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

struct Student {
    int roll_no;
    char name[50];
    char course[50];
};

struct Student active_students[MAX_STUDENTS];
struct Student recycle_bin[MAX_STUDENTS];

int active_count = 0;
int recycle_count = 0;

// 1. Add Student
void addStudent() {
    if (active_count >= MAX_STUDENTS) {
        printf("\nError: Memory full!\n");
        return;
    }
    struct Student new_student;
    printf("\n--- Add New Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &new_student.roll_no);

    for (int i = 0; i < active_count; i++) {
        if (active_students[i].roll_no == new_student.roll_no) {
            printf("Error: This Roll Number already exists!\n");
            return;
        }
    }
    printf("Enter Name: ");
    scanf("%s", new_student.name);
    printf("Enter Course: ");
    scanf("%s", new_student.course);

    active_students[active_count] = new_student;
    active_count++;
    printf("Student added successfully!\n");
}

// 2. Display Students
void displayStudents() {
    printf("\n--- Current Student List ---\n");
    if (active_count == 0) {
        printf("No active students found.\n");
    } else {
        printf("%-10s %-20s %-15s\n", "Roll No", "Name", "Course");
        printf("-----------------------------------------------\n");
        for (int i = 0; i < active_count; i++) {
            printf("%-10d %-20s %-15s\n", active_students[i].roll_no, active_students[i].name, active_students[i].course);
        }
    }
}

// 3. Soft Delete (To Recycle Bin)
void deleteStudent() {
    printf("\n--- Delete Student (Move to Bin) ---\n");
    if (active_count == 0) {
        printf("List is empty.\n");
        return;
    }
    int roll_no, found = 0;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll_no);

    for (int i = 0; i < active_count; i++) {
        if (active_students[i].roll_no == roll_no) {
            recycle_bin[recycle_count] = active_students[i];
            recycle_count++;

            for (int j = i; j < active_count - 1; j++) {
                active_students[j] = active_students[j + 1];
            }
            active_count--;
            printf("Student moved to Recycle Bin.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found.\n");
}

// 4. View Recycle Bin
void showRecycleBin() {
    printf("\n--- Recycle Bin ---\n");
    if (recycle_count == 0) {
        printf("Recycle Bin is empty.\n");
    } else {
        printf("%-10s %-20s %-15s\n", "Roll No", "Name", "Course");
        printf("-----------------------------------------------\n");
        for (int i = 0; i < recycle_count; i++) {
            printf("%-10d %-20s %-15s\n", recycle_bin[i].roll_no, recycle_bin[i].name, recycle_bin[i].course);
        }
    }
}

// 5. Recover Student
void recoverData() {
    printf("\n--- Recover Student ---\n");
    if (recycle_count == 0) {
        printf("No data to recover.\n");
        return;
    }
    int roll_no, found = 0;
    printf("Enter Roll Number to recover: ");
    scanf("%d", &roll_no);

    for (int i = 0; i < recycle_count; i++) {
        if (recycle_bin[i].roll_no == roll_no) {
            active_students[active_count] = recycle_bin[i];
            active_count++;

            for (int j = i; j < recycle_count - 1; j++) {
                recycle_bin[j] = recycle_bin[j + 1];
            }
            recycle_count--;
            printf("Student recovered successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found in Recycle Bin.\n");
}

// 6. Search Student
void searchStudent() {
    printf("\n--- Search Student ---\n");
    int roll_no, found = 0;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll_no);

    for (int i = 0; i < active_count; i++) {
        if (active_students[i].roll_no == roll_no) {
            printf("\nStudent Found:\n");
            printf("Name: %s\n", active_students[i].name);
            printf("Course: %s\n", active_students[i].course);
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found.\n");
}

// 7. NEW: Permanent Delete
void permanentlyDeleteStudent() {
    printf("\n--- Permanent Delete (From Bin) ---\n");

    // First, show the bin so user knows who they can delete
    if (recycle_count == 0) {
        printf("Recycle Bin is empty. Nothing to delete.\n");
        return;
    }

    // Show current bin contents
    printf("%-10s %-20s %-15s\n", "Roll No", "Name", "Course");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < recycle_count; i++) {
        printf("%-10d %-20s %-15s\n", recycle_bin[i].roll_no, recycle_bin[i].name, recycle_bin[i].course);
    }

    int roll_no, found = 0;
    printf("\nEnter Roll Number to PERMANENTLY delete: ");
    scanf("%d", &roll_no);

    // Confirmation logic
    char confirm;
    printf("Are you sure? This cannot be undone (y/n): ");
    scanf(" %c", &confirm); // Space before %c catches newline buffer

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = 0; i < recycle_count; i++) {
            if (recycle_bin[i].roll_no == roll_no) {
                // Remove from Recycle Bin (Shift elements left)
                for (int j = i; j < recycle_count - 1; j++) {
                    recycle_bin[j] = recycle_bin[j + 1];
                }
                recycle_count--;
                printf("Student Deleted Permanently.\n");
                found = 1;
                break;
            }
        }
        if (!found) printf("Student not found in Recycle Bin.\n");
    } else {
        printf("Operation cancelled.\n");
    }
}

// Main Menu
int main() {
    int choice;
    while (1) {
        printf("\n==============================\n");
        printf("   STUDENT MANAGEMENT SYSTEM  \n");
        printf("==============================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Delete Student (to Recycle Bin)\n");
        printf("4. View Recycle Bin\n");
        printf("5. Recover Student\n");
        printf("6. Search Student\n");
        printf("7. Permanently Delete (from Bin)\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear buffer
            choice = 0;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: deleteStudent(); break;
            case 4: showRecycleBin(); break;
            case 5: recoverData(); break;
            case 6: searchStudent(); break;
            case 7: permanentlyDeleteStudent(); break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please select 1-8.\n");
        }
    }
    return 0;
}
