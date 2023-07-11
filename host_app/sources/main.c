#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main(int argc, char *argv[]) {
    // check number of parameters
    if (argc != 3) {
        printf("Usage: %s <file> <serialport>\n", argv[0]);
        return 1;
    }
    // open serial port
    int serial_fd = open(argv[2], O_RDWR | O_NOCTTY | O_SYNC);
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

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

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

    // open file
    FILE* hex_file = fopen(argv[1], "r");
    if (hex_file == NULL) {
        perror("Error opening hex file");
        exit(1);
    }

    char buffer[100];
    int counter = 0;
    char c;
    while ((c = fgetc(hex_file)) != EOF) {
        // Send the character over the serial port
        write(serial_fd, &c, 1);
        printf("%c", c);
        if (c == '\n')
        {   

            // Wait for an "OK" message from the other end over the serial port
            char response[2];
            do
            {
                read(serial_fd, response, 1);
                response[1] = '\0';
            } while (strcmp(response, "C") != 0);
            }
    }

    close(serial_fd);
    fclose(hex_file);
    return 0;
}
