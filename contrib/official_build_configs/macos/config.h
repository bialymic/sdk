/* include/mega/config.h.  Generated from config.h.in.cmake by cmake.  */

/* Define to enable chat */
#ifndef ENABLE_CHAT
/* #undef ENABLE_CHAT */
#endif

/* Defined if sync subsystem is enabled */
#ifndef ENABLE_SYNC
#define ENABLE_SYNC
#endif

/* Define to use FreeImage library. */
#ifndef USE_FREEIMAGE 
/* #undef USE_FREEIMAGE */
#endif

#ifdef USE_FREEIMAGE
#include "FreeImageConfig.h"  // for FREEIMAGE_LIB setting
#endif

/* Define to indicate AIO presence in librt */
/* #undef HAVE_AIO_RT */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'. */
#define HAVE_DIRENT_H

#ifndef _WIN32
/* Define to 1 if you have the `fdopendir' function. */
//#define HAVE_FDOPENDIR 1
#endif

/* Define to use FFMPEG */
#ifndef HAVE_FFMPEG
#define HAVE_FFMPEG 
#endif

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H

/* Define to 1 if you have the <glob.h> header file. */
#define HAVE_GLOB_H

/* Define to use libraw */
#define HAVE_LIBRAW 1

/* Define to use libuv */
#define HAVE_LIBUV 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the <malloc/malloc.h> header file. */
/* #undef HAVE_MALLOC_MALLOC_H */

/* Define to 1 if you have the <mcheck.h> header file. */
#define HAVE_MCHECK_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <openssl/ssl.h> header file. */
#define HAVE_OPENSSL_SSL_H 1

/* Define to 1 if you have the <pcrecpp.h> header file. */
/* #undef HAVE_PCRECPP_H */

/* If available, contains the Python version number currently in use. */
/* #undef HAVE_PYTHON */

/* Define to 1 if you have the <readline/readline.h> header file. */
#define HAVE_READLINE_READLINE_H 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the <sodium.h> header file. */
#define HAVE_SODIUM_H 1

/* Define to 1 if you have the <sqlite3.h> header file. */
#define HAVE_SQLITE3_H 1

/* Define to 1 if the system has the type `ssize_t'. */
#define HAVE_SSIZE_T 1

/* Define to 1 if stdbool.h conforms to C99. */
/* #undef HAVE_STDBOOL_H */

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/inotify.h> header file. */
#ifndef __APPLE__
#define HAVE_SYS_INOTIFY_H 1
#endif

/* Define to 1 if you have the <sys/malloc.h> header file. */
/* #undef HAVE_SYS_MALLOC_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/timeb.h> header file. */
#define HAVE_SYS_TIMEB_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <termcap.h> header file. */
#define HAVE_TERMCAP_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef _WIN32
#define HAVE_UNISTD_H 1
#endif

/* Define to 1 if you have the <uv.h> header file. */
/* #undef HAVE_UV_H */

/* Define to 1 if you have the <ZenLib/Ztring.h> header file. */
/* #undef HAVE_ZENLIB_ZTRING_H */

/* Define to 1 if you have the <zlib.h> header file. */
#define HAVE_ZLIB_H 1

/* Define to 1 if the system has the type `_Bool'. */
/* #undef HAVE__BOOL */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* cpu-machine-OS */
#define OS "x86_64-pc-linux-gnu"

/* Name of package */
#define PACKAGE "libmega"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://github.com/meganz/sdk"

/* Define to the full name of this package. */
#define PACKAGE_NAME "libmega"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libmega 3.3.8"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libmega"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "3.3.8"

/* The size of `uint64_t', as computed by sizeof. */
#define SIZEOF_UINT64_T 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Define to use UNICODE (for MediaInfo) */
#define UNICODE 1

/* Define to use c-ares */
#define USE_CARES 1

/* Define to use libcryptopp */
#define USE_CRYPTOPP 1

/* Use inotify API */
#ifndef __APPLE__
#define USE_INOTIFY 1
#endif

/* Use IOS */
/* #undef USE_IOS */

/* Define to use libmediainfo */
#define USE_MEDIAINFO 1

/* Defined if MEGA API enabled */
#define USE_MEGAAPI 1

/* Define to use OpenSSL */
/* #undef USE_OPENSSL */

/* Define to use libpcre */
/* #undef USE_PCRE */

/* Defined if pthreads are available */
#define USE_PTHREAD 1

/* Define to use libsodium */
#define USE_SODIUM 1

/* Define to use SQLite */
#define USE_SQLITE 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define to use zlib */
#define USE_ZLIB 1

/* Version number of package */
#define VERSION "3.3.8"

/* Define _DARWIN_C_SOURCE */
/* #undef _DARWIN_C_SOURCE */

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Define _XOPEN_SOURCE */
/* #undef _XOPEN_SOURCE */

/* Force definition of constant macros for C++ */
#define __STDC_CONSTANT_MACROS /**/

/* Force definition of format macros for C++ */
#define __STDC_FORMAT_MACROS /**/

/* Force definition of limit macros for C++ */
#define __STDC_LIMIT_MACROS /**/

/* Define to `long int' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */
