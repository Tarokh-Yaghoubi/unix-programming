

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char* argv[]) {
	int fd = 0;
	fd = open("/home/Desktop/unix-programming/trash_file", O_RDONLY);
	if (fd == -1)
		perror("open");

	return EXIT_SUCCESS;
}

