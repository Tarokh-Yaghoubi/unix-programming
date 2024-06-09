

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
	int fd = 0;
	fd = open("/home/tarok/Desktop/unix-programming/FILE_IO/trash_file", O_RDWR | O_CREAT);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	return EXIT_SUCCESS;
}

int open_trunc(void) {
	int fd = 0;
	fd = open("/home/tarok/Desktop/unix-programming/trash_file", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	return EXIT_SUCCESS;

}

