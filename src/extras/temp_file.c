#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*  A handle for a temporary file created with write_temp_file.
	In this implementation, it’s just a file descriptor. */
typedef int temp_file_handle;

/*  Writes LENGTH bytes from BUFFER into a temporary file. The
	temporary file is immediately unlinked. Returns a handle to the
	temporary file. */

temp_file_handle write_temp_file (char* buffer, size_t length)
{
	/*  Create the filename and file. The XXXXXX will be replaced with
		characters that make the filename unique. */
	char temp_filename[] = "/tmp/temp_file.XXXXXX";
	int fd = mkstemp (temp_filename);
	printf("File created: %s\n", temp_filename);
	/*  Unlink the file immediately, so that it will be removed when the
		file descriptor is closed. */
	unlink (temp_filename);
	/*  Write the number of bytes to the file first. */
	write (fd, &length, sizeof (length));
	/*  Now write the data itself. */
	write (fd, buffer, length);
	printf("Wrote: %s\n", buffer);
	/*  Use the file descriptor as the handle for the temporary file. */
	return fd;
}

/* Reads the contents of a temporary file TEMP_FILE created with
	write_temp_file. The return value is a newly allocated buffer of
	those contents, which the caller must deallocate with free.
	*LENGTH is set to the size of the contents, in bytes. The
	temporary file is removed. */
char* read_temp_file (temp_file_handle temp_file, size_t* length)
{
	char* buffer;
	/* The TEMP_FILE handle is a file descriptor to the temporary file. */
	int fd = temp_file;
	/* Rewind to the beginning of the file. */
	lseek (fd, 0, SEEK_SET);
	/* Read the size of the data in the temporary file. */
	read (fd, length, sizeof (*length));
	/* Allocate a buffer and read the data. */
	buffer = (char*) malloc (*length);
	read (fd, buffer, *length);
	printf("Read: %s\n", buffer);
	/* Close the file descriptor, which will cause the temporary file to
	go away. */
	close (fd);
	return buffer;
}

int main()
{
	size_t length = 10;
	char text[] = "Hello";
	char *text2 = (char * )malloc(10*sizeof(char));

	temp_file_handle tempfile1 = write_temp_file(text, length);
	read_temp_file(tempfile1, &length);

	FILE *fp = tmpfile(); /* using tmpfile to directly create an unlinked temp file*/
	printf("tmpfile created\n");
	fwrite(text, 10*sizeof(char), 1, fp);
	printf("Wrote: %s\n", text);
	rewind(fp);
	fread(text2, 10*sizeof(char), 1, fp);
	fclose(fp);
	printf("Read: %s\n", text2);


	return 0;	
}