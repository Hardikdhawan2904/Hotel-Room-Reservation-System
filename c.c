#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Room {
    int roomNumber;
    char guestName[50];
    int isReserved;
    struct Room* next;
} Room;

typedef struct WaitlistNode {
    char guestName[50];
    struct WaitlistNode* next;
} WaitlistNode;

WaitlistNode* front = NULL;
WaitlistNode* rear = NULL;

Room* createRoom(int roomNumber) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (!newRoom) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newRoom->roomNumber = roomNumber;
    strcpy(newRoom->guestName, "");
    newRoom->isReserved = 0;
    newRoom->next = NULL;
    return newRoom;
}

Room* initializeRooms(int size) {
    Room* head = NULL;
    Room* temp = NULL;
    for (int i = 1; i <= size; i++) {
        Room* newRoom = createRoom(i);
        if (head == NULL) {
            head = newRoom;
            temp = newRoom;
        } else {
            temp->next = newRoom;
            temp = newRoom;
        }
    }
    return head;
}

void addToWaitlist(const char* name) {
    WaitlistNode* newNode = (WaitlistNode*)malloc(sizeof(WaitlistNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->guestName, name);
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("Added %s to the waitlist.\n", name);
}

void removeFromWaitlist() {
    if (front == NULL) {
        printf("Waitlist is empty.\n");
        return;
    }
    WaitlistNode* temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    printf("Removed %s from the waitlist.\n", temp->guestName);
    free(temp);
}

void reserveRoom(Room* head) {
    int roomNumber;
    char name[50];
    printf("Enter room number to reserve: ");
    scanf("%d", &roomNumber);
    Room* temp = head;
    while (temp != NULL && temp->roomNumber != roomNumber) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid room number.\n");
    } else if (temp->isReserved) {
        printf("Room %d is already reserved. Adding guest to waitlist.\n", roomNumber);
        printf("Enter guest name: ");
        scanf(" %[^\n]", name);
        addToWaitlist(name);
    } else {
        printf("Enter guest name: ");
        scanf(" %[^\n]", name);
        strcpy(temp->guestName, name);
        temp->isReserved = 1;
        printf("Room %d has been reserved for %s.\n", roomNumber, name);
    }
}

void cancelReservation(Room* head) {
    int roomNumber;
    printf("Enter room number to cancel reservation: ");
    scanf("%d", &roomNumber);
    Room* temp = head;
    while (temp != NULL && temp->roomNumber != roomNumber) {
        temp = temp->next;
    }
    if (temp == NULL || !temp->isReserved) {
        printf("Invalid room number or no reservation exists.\n");
    } else {
        printf("Reservation for %s in Room %d has been canceled.\n", temp->guestName, roomNumber);
        strcpy(temp->guestName, "");
        temp->isReserved = 0;
        if (front != NULL) {
            strcpy(temp->guestName, front->guestName);
            temp->isReserved = 1;
            printf("Room %d has been reassigned to %s from the waitlist.\n", roomNumber, front->guestName);
            removeFromWaitlist();
        }
    }
}

void checkRoomStatus(Room* head) {
    int roomNumber;
    printf("Enter room number to check status: ");
    scanf("%d", &roomNumber);
    Room* temp = head;
    while (temp != NULL && temp->roomNumber != roomNumber) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid room number.\n");
    } else if (temp->isReserved) {
        printf("Room %d is reserved by %s.\n", roomNumber, temp->guestName);
    } else {
        printf("Room %d is available.\n", roomNumber);
    }
}

void displayReservedRooms(Room* head) {
    Room* temp = head;
    printf("Reserved Rooms:\n");
    int found = 0;
    while (temp != NULL) {
        if (temp->isReserved) {
            printf("Room %d - Guest: %s\n", temp->roomNumber, temp->guestName);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No rooms are currently reserved.\n");
    }
}

void freeRooms(Room* head) {
    Room* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int roomCount = 5;
    Room* hotelRooms = initializeRooms(roomCount);
    int choice;
    do {
        printf("\nHotel Reservation System\n");
        printf("1. Reserve a room\n");
        printf("2. Cancel a reservation\n");
        printf("3. Check room status\n");
        printf("4. Display reserved rooms\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                reserveRoom(hotelRooms);
                break;
            case 2:
                cancelReservation(hotelRooms);
                break;
            case 3:
                checkRoomStatus(hotelRooms);
                break;
            case 4:
                displayReservedRooms(hotelRooms);
                break;
            case 5:
                printf("Exiting the program.\n");
                freeRooms(hotelRooms);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}
