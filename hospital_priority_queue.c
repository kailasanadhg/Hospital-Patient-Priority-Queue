
#include <stdio.h>
#include <string.h>

#define MAX 50

struct Patient {
    char name[30];
    int priority;
};

struct Patient pq[MAX];
int size = 0;

// Add patient
void addPatient(char name[], int priority) {
    if (size == MAX) {
        printf("Queue is full!\n");
        return;
    }

    int i = size++;

    while (i > 0 && pq[(i - 1) / 2].priority > priority) {
        pq[i] = pq[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    strcpy(pq[i].name, name);
    pq[i].priority = priority;

    printf("Patient %s added successfully.\n", name);
}

// Treat next patient
void treatNextPatient() {
    if (size == 0) {
        printf("No patients waiting.\n");
        return;
    }

    printf("Treating patient: %s (Priority: %d)\n",
           pq[0].name, pq[0].priority);

    struct Patient last = pq[--size];

    if (size == 0)
        return;

    int i = 0;

    while (2 * i + 1 < size) {
        int child = 2 * i + 1;

        if (child + 1 < size &&
            pq[child + 1].priority < pq[child].priority)
            child++;

        if (last.priority <= pq[child].priority)
            break;

        pq[i] = pq[child];
        i = child;
    }

    pq[i] = last;
}

int main() {
    printf("HOSPITAL PATIENT PRIORITY QUEUE\n");

    // Initial patients
    addPatient("P1", 3);
    addPatient("P2", 1);
    addPatient("P3", 2);
    addPatient("P4", 1);
    addPatient("P5", 3);
    addPatient("P6", 2);

    printf("\n--- First Test ---\n");

    while (size > 0)
        treatNextPatient();

    // Second test
    printf("\n--- Second Test ---\n");

    addPatient("P1", 3);
    addPatient("P2", 1);
    addPatient("P3", 2);
    addPatient("P4", 1);
    addPatient("P5", 3);
    addPatient("P6", 2);

    printf("\nTreating first 2 patients:\n");
    treatNextPatient();
    treatNextPatient();

    printf("\nAdding new Emergency patient:\n");
    addPatient("Emergency", 1);

    printf("\nRemaining treatment order:\n");

    while (size > 0)
        treatNextPatient();

    return 0;
}
