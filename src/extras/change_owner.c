#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    uid_t uid;
    struct passwd *pwd;
    char *endptr;

    if (argc != 3 || argv[1][0] == '\0') {
        fprintf(stderr, "%s <owner> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    uid = strtol(argv[1], &endptr, 10);  /* Allow a numeric string */

    if (*endptr != '\0') {         /* Was not pure numeric string */
        pwd = getpwnam(argv[1]);   /* Try getting UID for username */       
        if (pwd == NULL) {
            perror("getpwnam");
            exit(EXIT_FAILURE);
        }

        uid = pwd->pw_uid;       
    }

    // if (chown(argv[2], uid, -1) == -1) {
    //     perror("chown");
    //     exit(EXIT_FAILURE);
    // }

    int rval = chown(argv[2], uid, -1);
    if (rval != 0) {
        /* Save errno because it's clobbered by the next system call */
        int error_code = errno;
        /* The operation didn't succeed; chown should return -1 on error */ 
        assert (rval == -1);
        /* check the value of errno, and take appropriate action */
        switch (error_code) {
            case EPERM:         /* Permission denied. */
            case EROFS:         /* PATH is on a read-only */
            case ENAMETOOLONG:  /* PATH is too long */
            case ENOENT:        /* PATH does not exit */
            case ENOTDIR:       /* A component of PATH is not a directory */
            case EACCES:        /* A component of PATH is not accessible */
                /* Something's wrong with the file. Print an error message. */
                fprintf(stderr, "error changing ownership of %s: %s\n",
                 argv[2], strerror (error_code));
                /* Don't end the program; perhaps give the user a chance to 
                    choose another file... */
                break;

            case EFAULT:
                /* PATH contains an invalid memory address. This is probably a bug. */    
                abort();

            case ENOMEM:
                /* Ran out of memory */    
                fprintf(stderr, "%s\n", strerror (error_code));
                exit(1);
            
            default:
                /* Some other, unexpected, error code. We've tried to handle all
                    possible error codes; if we've missed one, that's a bug! */    
                abort();
        }

    }

    exit(EXIT_SUCCESS);
}
