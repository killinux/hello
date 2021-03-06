apue/environ/doatexit.c                                                                                664     340      24          701  5211773676  10477                                                                                                                                                                                                                                                                                                                                                                      #include	"ourhdr.h"
static void	my_exit1(void), my_exit2(void);
int
main(void)
{
	if (atexit(my_exit2) != 0)
		err_sys("can't register my_exit2");
	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");
	if (atexit(my_exit1) != 0)
		err_sys("can't register my_exit1");
	printf("main is done\n");
	return(0);
}
static void
my_exit1(void)
{
	printf("first exit handler\n");
}
static void
my_exit2(void)
{
	printf("second exit handler\n");
}
ptriptr, PTR_SZ) != PTR_SZ)
		err_dump("write error of ptr fielapue/environ/getrlimit.c                                                                               664     340      24         1774  5211773677  10712                                                                                                                                                                                                                                                                                                                                                                      #include	<sys/types.h>
#include	<sys/time.h>
#include	<sys/resource.h>
#include	"ourhdr.h"

#define	doit(name)	pr_limits(#name, name)

static void	pr_limits(char *, int);

int
main(void)
{
	doit(RLIMIT_CORE);
	doit(RLIMIT_CPU);
	doit(RLIMIT_DATA);
	doit(RLIMIT_FSIZE);
#ifdef	RLIMIT_MEMLOCK
	doit(RLIMIT_MEMLOCK);
#endif
#ifdef	RLIMIT_NOFILE	/* SVR4 name */
	doit(RLIMIT_NOFILE);
#endif
#ifdef	RLIMIT_OFILE	/* 44BSD name */
	doit(RLIMIT_OFILE);
#endif
#ifdef	RLIMIT_NPROC
	doit(RLIMIT_NPROC);
#endif
#ifdef	RLIMIT_RSS
	doit(RLIMIT_RSS);
#endif
	doit(RLIMIT_STACK);
#ifdef	RLIMIT_VMEM
	doit(RLIMIT_VMEM);
#endif
	exit(0);
}

static void
pr_limits(char *name, int resource)
{
	struct rlimit	limit;

	if (getrlimit(resource, &limit) < 0)
		err_sys("getrlimit error for %s", name);
	printf("%-14s  ", name);
	if (limit.rlim_cur == RLIM_INFINITY)
		printf("(infinite)  ");
	else
		printf("%10ld  ", limit.rlim_cur);
	if (limit.rlim_max == RLIM_INFINITY)
		printf("(infinite)\n");
	else
		printf("%10ld\n", limit.rlim_max);
}
((dbapue/environ/opendata.c                                                                                664     340      24          461  5211773700  10440                                                                                                                                                                                                                                                                                                                                                                      #include	<stdio.h>

#define	DATAFILE	"datafile"

FILE *
open_data(void)
{
	FILE	*fp;
	char	databuf[BUFSIZ];  /* setvbuf makes this the stdio buffer */

	if ( (fp = fopen(DATAFILE, "r")) == NULL)
		return(NULL);

	if (setvbuf(fp, databuf, BUFSIZ, _IOLBF) != 0)
		return(NULL);

	return(fp);		/* error */
}
EMLOCK);
#endif
#ifdef	RLIMIT_NOFILE	/* SVR4 name */
	doit(RLIMIT_NOFILE);
#endif
#ifdef	RLIMIT_OFILE	/* 44BSD name */
	doit(RLIMIT_OFILE);
#endif
#ifdef	RLIMIT_NPROC
	doit(RLIMIT_NPROC);
#endif
#ifdef	RLIMIapue/environ/testjmp.c                                                                                 664     340      24         1174  5211773701  10356                                                                                                                                                                                                                                                                                                                                                                      #include	<s