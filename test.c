#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include <time.h>



// Concatenate two strings
char* strcat(char* dest, const char* src) {
  char* dest_orig = dest;

  while (*dest != '\0') {
    dest++;
  }

  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }

  *dest = '\0';
  return dest_orig;
}



void reverse(char *str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void itoa(int num, char *str, int base) {
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    str[i] = '\0'; 
    reverse(str, i);
}

int main(int argc, char * argv[]) {
	int n = 150;
  int pid;
  pid = 0;


  int x = 0;
  for (int i = 0; i < n; i++) {
    pid = fork();
    if (pid == -1) {
      // printf(1, "%d failed in fork!\n", getpid());
    } else if (pid > 0) {
      // printf(1, "Parent %d creating child %d\n",getpid(), pid);
      wait();
    } else {
      printf(1, "Child %d created\n", getpid());
      x = 0;
      int t;
      t = uptime();
      int i, j;
      long long sum = 0;
      int n = 1000000;
      for(int j = 1; j <= n; j++) {
        for(int z = 1; z <= n; z++) {
            sum += z * j;
        }
      }

      t = uptime() - t;
      char file_name[25] = "output_child_";
      char file_num[5];

      itoa(getpid(), file_num, 10);
      strcat(file_name, file_num);

      int fd;

      // Open a file in writing mode
      fd = open(file_name, O_CREATE | O_WRONLY);

      char data[30];
      itoa(t, data, 10);
      int n = write(fd, data, strlen(data));

      // Close the file
      if(n < 0)
        close(fd); 
      else close(fd);

      printf(1, "Child %d ticks: %d\n", getpid(), t);
      break;
    }
  }
  exit();
}