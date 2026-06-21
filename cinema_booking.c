#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 50 // Maximum number of seats in the cinema

// structure to represent each seat in the cinema

typedef struct SeatNode {
    char customerName[100];// name of the costumer who booked or concelled the seat
    int seatNumber;
    int status; // 0: Empty, 1: Booked, 2: Cancelled
    struct SeatNode* next; // pointer to the next seat node in the linked list
} SeatNode;

// structure to represent the cinema
typedef struct {
    SeatNode* head; // head of the linked list of seats
    char movieTitle[100]; // title of the movie being shown
} Cinema;

void InitializeCinema(Cinema* cinema, const char* title);
void BookSeat(Cinema* cinema);
void CancelSeat(Cinema* cinema);
void DisplaySeats(const Cinema* cinema);

int SeatAvailable(const Cinema* cinema, int seatNumber);

int main() {
    Cinema cinema;
    InitializeCinema(&cinema, "Inception"); // initialize cinema with the movie title 

    char option;
    do {
        printf("Movie Booking System\n");
        printf("--------------------\n");
        printf("1. Book a seat\n");
        printf("2. Cancel booking\n");
        printf("3. Display seats\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &option); 

        switch (option) {
            case '1':
                BookSeat(&cinema);
                break;
            case '2':
                CancelSeat(&cinema);
                break;
            case '3':
                DisplaySeats(&cinema);
                break;
            case '4':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != '4');

   
    return 0;
}

void InitializeCinema(Cinema* cinema, const char* title) {
    cinema->head = NULL;
    strncpy(cinema->movieTitle, title, sizeof(cinema->movieTitle) - 1); // copy the movie titlte
}

void BookSeat(Cinema* cinema) {
    int seatNumber;
    char customerName[100];

    printf("Enter customer name: ");
    getchar();
    fgets(customerName, 100, stdin);
    

    printf("Enter seat number (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNumber);

    // check if the seat is availblable
    if (seatNumber < 1 || seatNumber > MAX_SEATS || SeatAvailable(cinema, seatNumber)) {
        printf("Error: Invalid seat number or seat already booked.\n");
        return;
    }

    SeatNode* newSeat = (SeatNode*)malloc(sizeof(SeatNode)); // allocate memory for a new seat
    strcpy(newSeat->customerName, customerName); // copy the name of costomer to the new seat
    newSeat->seatNumber = seatNumber;
    newSeat->status = 1; // Booked
    newSeat->next = cinema->head; // insert the seat at the beginning 
    cinema->head = newSeat;

    printf("Seat booked successfully.\n");
}
 // checks if a seat is availble for booking
int SeatAvailable(const Cinema* cinema, int seatNumber) {
    SeatNode* current = cinema->head;
    while (current != NULL) {
        if (current->seatNumber == seatNumber && current->status == 1) {
            return 1; // Seat is not available
        }
        current = current->next;
    }
    return 0; // Seat is available
}
// concels a booking
void CancelSeat(Cinema* cinema) {
    char customerName[100];
    printf("Enter customer name to cancel booking: ");
     getchar();
    fgets(customerName, 100, stdin);

    SeatNode* current = cinema->head;
    while (current != NULL) {
        if (strcmp(current->customerName, customerName) == 0 && current->status == 1) {
            current->status = 2; // Cancelled
            printf("Booking cancelled for %s.\n", customerName);
            return;
        }
        current = current->next;
    }

    printf("No booking found for %s.\n", customerName);
}
// display the seat bookings in the cinema
void DisplaySeats(const Cinema* cinema) {
    printf("Current bookings for %s:\n", cinema->movieTitle);
    SeatNode* current = cinema->head;
    while (current != NULL) {
        const char* status = current->status == 1 ? "Booked" : "Cancelled"; // determin the statu of the seat
        printf("Seat %d: %s (%s)\n", current->seatNumber, current->customerName, status);
        current = current->next;
    }
}

