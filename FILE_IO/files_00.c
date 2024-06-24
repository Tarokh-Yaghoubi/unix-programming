

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


static char* FILE_NAME = "trash_file";
static char* CREAT_FILE = "creat_file";

int open_trunc(void);
int open_file_for_read(void);
int creat_syscall(void);
int creat_syscall_userspace(const char*, int);
int read_syscall(void);
int write_syscall(void);

int
main(int argc, char* argv[]) {
	int fd = 0;
	fd = open("trash_file", O_RDWR | O_CREAT/* | O_EXCL*/);
	if (fd == -1) {
		/*
		if (errno == EEXIST) {
			printf("%s\n", "file already exists");
		} */
		perror("open");
		return EXIT_FAILURE;
	}

	creat_syscall();
	read_syscall();
	return EXIT_SUCCESS;
}

int 
open_trunc(void) {
	int fd = 0;
	fd = open("trash_file", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

}

// you must provide the mode argument of open system call when passing O_CREAT
// If you forget to pass the mode arg, quite ugly things may happen, btw the result
// is undefined.

// Permissions (mode) are te same as the UNIX permission bitset.
// But for more portability, POSIX has provided some sort of constants.
// this CONSTANTS can be binary-ORed together and supply the mode argument

// umask is modifiable via the umask() call

int 
open_file_for_read(void) {
	int fd = 0;
	fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 
			S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);
	if (fd == -1) {
		printf("%s [%d]\n", "The file descriptor ret_val is ---->>> ", fd);
		perror("open");
		return EXIT_FAILURE;

	}

	// this is doing the same thing, we are trading portability for readability
	// fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}


// The combination of O_WRONLY | O_CREAT | O_TRUNC is so common that a syscall exists to provide
// just that behavior

int
creat_syscall(void) {
	int fd = 0;
	fd = creat(CREAT_FILE, 0744);
	if (fd == -1) {
		printf("%s [%d] \n", "The file descriptor ret_val is ----->>>> ", fd);
		perror("creat");
		return EXIT_FAILURE;
	} else {
		printf("%s\n%s [%s]\n", "file created successfully", "file name ", CREAT_FILE);
		return EXIT_SUCCESS;
	}

}


int
creat_syscall_userspace(const char* name, int mode) {

	return open(name, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

int
read_syscall(void) {
	ssize_t read_data = 0;
	char buf[100] = { 0 };

	int fd = 0;
	fd = open(FILE_NAME, O_RDONLY);
	if (fd == -1) {
		printf("%s\n", "failed to open the file");
		perror("open");
		return EXIT_FAILURE;
	}
	read_data = read(fd, &buf[0], (sizeof(buf) / sizeof(buf[0])));
	if (read_data != 0) { 
		printf("[%ld]  %s\n", (long)read_data, " bytes of data, read from file");
		printf("%s -->> [%s] \n", "Buffer is", buf);
		return EXIT_SUCCESS;
	} else {
		printf("%s\n", "failed to read file data");
		return EXIT_FAILURE;
	}

}

int
write_syscall(void) {
	ssize_t written_data = 0;
	int fd = 0;
	const char* data = "tarokh is a moderate programmer";
	fd = open("trash_file", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}
	written_data = write(fd, data, strlen(data));
	if (written_data == -1) {
		perror("write");
		return EXIT_FAILURE;
	}
	printf("%s [%ld]\n", "Written data length is ----->>>> ", (long)written_data);
	return EXIT_SUCCESS;

}

int
write_syscall_sec(int fd) {
	unsigned long word = 1720;
	size_t count;
	ssize_t nr;

	count = sizeof(word);
	nr = write(fd, &word, count);
	if (nr == -1)
		// error check
	else if (nr != count)
		// possible error, but 'errno' not set
	
	return;
}

