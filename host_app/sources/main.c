#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>



// Auxilary variables and function prototypes
int serial_fd;
FILE *hex_file;
char response[255];
time_t time1, time2;
void sendCommand(const char *command, char *response);

int main(int argc, char *argv[])
{
    // check number of parameters
    if (argc != 2) {
        printf("Usage: %s <serialport>\n", argv[0]);
        return 1;
    }

    while (1)
    {
    // Supported commands
    printf("STM32F103 Custom BootLoader\n");
    printf("===========================\n");
    printf("Select Command:\n");
    printf("Get Bootloader Version--> 0\n");
    printf("Get Device Id-----------> 1\n");
    printf("Write Memory------------> 2\n");
    printf("Read Memory-------------> 3\n");
    printf("Erase Memory------------> 4\n");
    printf("Jump to App-------------> 5\n");

    // Scan command
    int Command;
    time(&time1);
    printf("Enter a Command: ");
    scanf("%d", &Command);
    time(&time2);

    // Open serial port
    serial_fd = open(argv[1], O_RDWR | O_NOCTTY | O_SYNC);
    if (serial_fd < 0) {
        perror("Error opening serial port");
        exit(1);
    }
    
    // set serial port parameters
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("Error getting serial port attributes");
        exit(1);
    }

    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        exit(1);
    }

    int SessionFlag = 0;

    switch (Command)
    {
    case 0:
        if (difftime(time2,time1) <= 13)
        {
            // Send get version command
            sendCommand("FF00\n", response);
            system("clear");
            printf("Response:\n");
            printf("Bootloader Version: %s\n", response);
        }
        break;
    case 1:
        if (difftime(time2,time1) <= 13)
        {
            // Send get cpu id command
            sendCommand("FF01\n", response);
            system("clear");
            printf("Response:\n");
            printf("Device Id: 0x%s\n", response);
        }
        break;
    case 2:
        if (difftime(time2,time1) <= 13)
        {
            // Send hex file
            // Open file
            hex_file = fopen("app.hex", "r");
            if (hex_file == NULL) 
            {
                perror("Error opening hex file");
                exit(1);
            }
            char c;
            // Send File
            while ((c = fgetc(hex_file)) != EOF) 
            {
                // Send the character over the serial port
                write(serial_fd, &c, 1);
                printf("%c", c);
                if (c == '\n')
                {   
                    usleep(10000); // Wait for the response
                    int BytesRead = read(serial_fd, response, 255);  
                    printf("%s\n", response);
                }
            }
            system("clear");
            printf("Response:\n");
            printf("The Program was successfully flashed\n");
            fclose(hex_file);
        }
        break;
    case 3:
        if (difftime(time2,time1) <= 13)
        {
            // Send read flash command
            sendCommand("FF03\n", response);
            system("clear");
            printf("Response:\n");
            printf("%s\n", response);
        }
        break;
    case 4:
        if (difftime(time2,time1) <= 13)
        {
            // Send erase memory command
            sendCommand("FF04\n", response);
            system("clear");
            printf("Response:\n");
            printf("%s\n", response);
        }
        break;
    case 5:
        if (difftime(time2,time1) <= 13)
        {
            // Send jump command
            sendCommand("FF05\n", response);
            system("clear");
            printf("Response:\n");
            printf("%s\n", response);
            SessionFlag = 1;
        }
        break;
    default:
        // Do nothing
        break;
    }

    // Check session
    if (SessionFlag == 1  || difftime(time2,time1) >= 13 || (strcmp(response, "Exit") == 0))
    {
        printf("\nSession expired\n");
        printf("To activate it a gain, reset the target board\n");
        break;
    }

    // Close serial port
    close(serial_fd);
    printf("\n---------------------------\n\n");
    }

return 0;
}

// Function to send a command and receive the response
void sendCommand(const char* command, char* response) 
{
    // Write command
    write(serial_fd, command, strlen(command));
    // Wait for the response
    usleep(10000); 
    // Read response
    int BytesRead = read(serial_fd, response, 255);
}
