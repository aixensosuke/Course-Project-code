#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

void clearScreen() {
    printf("\033[H\033[J");
}

struct WorldTime {
    const char* location;
    float hour_offset;  // Changed to float for half-hour offsets
};

void displayWorldTime(int base_hour, int minutes, int seconds, struct WorldTime city) {
    float local_time = base_hour + minutes/60.0;
    float city_time = local_time + city.hour_offset;
    int city_hour = ((int)city_time + 24) % 24;
    int city_minutes = minutes;
    printf("  |  %-14s %02d:%02d:%02d  |\n", city.location, city_hour, city_minutes, seconds);
}

void displayAllTimes(int local_hour, int minutes, int seconds) {
    struct WorldTime cities[] = {
        {"Local", 0},
        {"India", 5.5},      // UTC+5:30
        {"New York", -4},  // UTC-4
        {"Los Angeles", -7}, // UTC-7
        {"Japan", 9}       // UTC+9
    };

    printf("  +--------------------------------+\n");
    printf("  |        World Time Clock        |\n");
    printf("  +--------------------------------+\n");
    
    for (int i = 0; i < 5; i++) {
        displayWorldTime(local_hour, minutes, seconds, cities[i]);
    }
    
    printf("  +--------------------------------+\n");
    printf("  | Press Ctrl+C to exit          |\n");
    printf("  +--------------------------------+\n");
}

void startStopwatch() {
    int hours = 0, minutes = 0, seconds = 0;
    while (1) {
        clearScreen();
        printf("  +--------------------------------+\n");
        printf("  |          Stopwatch             |\n");
        printf("  +--------------------------------+\n");
        printf("  |            %02d:%02d:%02d            |\n", hours, minutes, seconds);
        printf("  +--------------------------------+\n");
        printf("  | Press Ctrl+C to exit          |\n");
        printf("  +--------------------------------+\n");
        
        sleep(1);
        seconds++;
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60) {
            minutes = 0;
            hours++;
        }
    }
}

void startTimer(int hours, int minutes, int seconds) {
    int total_seconds = hours * 3600 + minutes * 60 + seconds;
    
    while (total_seconds > 0) {
        clearScreen();
        hours = total_seconds / 3600;
        minutes = (total_seconds % 3600) / 60;
        seconds = total_seconds % 60;
        
        printf("  +--------------------------------+\n");
        printf("  |            Timer               |\n");
        printf("  +--------------------------------+\n");
        printf("  |            %02d:%02d:%02d            |\n", hours, minutes, seconds);
        printf("  +--------------------------------+\n");
        printf("  | Press Ctrl+C to exit          |\n");
        printf("  +--------------------------------+\n");
        
        sleep(1);
        total_seconds--;
    }
    
    if (total_seconds == 0) {
        clearScreen();
        printf("\n\n  +--------------------------------+\n");
        printf("  |         Time's Up!!!           |\n");
        printf("  +--------------------------------+\n");
        sleep(2);
    }
}

void inputTime() {
    int hours, minutes, seconds;
    printf("Enter time (HH MM SS): ");
    if (scanf("%d %d %d", &hours, &minutes, &seconds) != 3) {
        printf("Invalid input! Press any key to continue...\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    printf("\n1. Use as World Clock Time\n");
    printf("2. Use as Timer\n");
    printf("Select option: ");
    
    int option;
    scanf("%d", &option);
    
    if (option == 1) {
        clearScreen();
        displayAllTimes(hours, minutes, seconds);
    } else if (option == 2) {
        startTimer(hours, minutes, seconds);
    }
}

void displayMenu() {
    printf("  +--------------------------------+\n");
    printf("  |        World Time Clock        |\n");
    printf("  +--------------------------------+\n");
    printf("  | 1. Display World Time          |\n");
    printf("  | 2. Start Stopwatch             |\n");
    printf("  | 3. Input Time/Timer            |\n");
    printf("  | 4. Exit                        |\n");
    printf("  +--------------------------------+\n");
    printf("  Select an option: ");
}

int main() {
    int choice;

    while (1) {
        clearScreen();
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer after scanf

        switch (choice) {
            case 1:
                while (1) {
                    time_t now = time(NULL);
                    struct tm *local = localtime(&now);
                    clearScreen();
                    displayAllTimes(local->tm_hour, local->tm_min, local->tm_sec);
                    sleep(1);
                }
                break;
            case 2:
                startStopwatch();
                break;
            case 3:
                inputTime();
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                sleep(1);
        }
    }
    return 0;
}
