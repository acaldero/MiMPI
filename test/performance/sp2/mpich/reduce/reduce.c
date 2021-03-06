/* ....................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 * See documentation for more information.
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * .................................................................... */



#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "mpi.h"

#define PRUEBAS 		10


int main(int argc, char *argv[])
{
	int             ret;
	char           *buf;
	char            processor_name[MPI_MAX_PROCESSOR_NAME];
	int             namelen;
	double          start_time;
        double          used_time;
        double          avg_time;
        double          us_rate;
        double          barrier_time;
        int             max_len, lenbuf;
        int             j;
	int             me, nproc;
        FILE           *fparam ;


	setbuf(stdout, NULL) ;

        fparam = fopen("reduce.in","rt") ;
        if (fparam == NULL)
        {
                printf("ERROR: can not open reduce.in, sorry.\n") ;
		exit(1) ;
        }
        ret = fscanf(fparam,"max_len=%i",&max_len) ;
        fclose(fparam) ;
        if (ret != 1)
        {
                printf("ERROR: can not read a valid 'max_len' value from reduce.in, sorry.\n") ;
		exit(1) ;
        }
        if ( (max_len <= 0) || (max_len >= 4*1024*1024) )
        {
                printf("ERROR: (max_len <= 0) || (max_len >= 4*1024*1024)\n") ;
                exit(1) ;
        }


	ret = MPI_Init(&argc, &argv);	
	if (ret < 0)
	{
		printf("Can't init\n") ;
		exit(1) ;
	}

	MPI_Comm_rank(MPI_COMM_WORLD,&me) ;
	MPI_Get_processor_name(processor_name,&namelen) ;
	MPI_Comm_size(MPI_COMM_WORLD, &nproc) ;

#if (0)
	printf("Process %d; total %d is alive on %s\n",me,nproc,processor_name) ;
#endif


        buf = (char *) malloc((unsigned) max_len) ;
        if (buf == NULL)
        {
                perror("Error en malloc") ;
                exit(1) ;
        }
	memset(buf,'x',max_len) ;

        /* ... Barrier ... */
        start_time = MPI_Wtime() ;
        for(j = 0; j < PRUEBAS; j++)
        {
          MPI_Barrier(MPI_COMM_WORLD) ;
        }
        barrier_time = (MPI_Wtime() - start_time) ;
 
        /* ... test ... */
	lenbuf = 1 ;
        while (lenbuf <= max_len)
        {
		avg_time = 0.0;
		if (me != 0)
		{
	                MPI_Barrier(MPI_COMM_WORLD) ;
			for(j = 0; j < PRUEBAS; j++)
                	{
				MPI_Reduce(buf,buf,lenbuf,
                                               MPI_CHAR,MPI_MAX,0,
				               MPI_COMM_WORLD) ;
	                        MPI_Barrier(MPI_COMM_WORLD) ;
			}
		}
		else
		{
	                MPI_Barrier(MPI_COMM_WORLD) ;
			start_time = MPI_Wtime() ;
			for(j = 0; j < PRUEBAS; j++)
                        {
				MPI_Reduce(buf,buf,lenbuf,
                                               MPI_CHAR,MPI_MAX,0,
				               MPI_COMM_WORLD) ;
	                        MPI_Barrier(MPI_COMM_WORLD) ;
			}
			used_time = (MPI_Wtime() - start_time) ;

                	avg_time =  (used_time - barrier_time) / (float)  PRUEBAS;
			if (avg_time > 0)    /* rate is megabytes per second */
                        	us_rate = (double)((nproc * lenbuf)/
					(avg_time*(double)1000000)) ;
                	else
                        	us_rate = 0.0;

                	printf("len_bytes=%e avg_time_sec=%e rate_Mbytes_sec=%e\n", 
			        (double)lenbuf, (double)avg_time, (double)us_rate) ;
                }

                lenbuf *= 2;
        }

#if (0)
	if (me == 0)
	    printf("\nclock resolution in seconds: %10.8f\n", MPI_Wtick()) ;
#endif

	MPI_Finalize() ;
        free(buf) ;
	exit(0) ;

}

		
	
	
	
	
