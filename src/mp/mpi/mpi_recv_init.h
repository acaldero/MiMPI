

#ifndef MPI_RECV_INIT_H
#define MPI_RECV_INIT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif
 

  /* ... Includes / Inclusiones ....................................... */

     #include "mp/mpi/c_base.h"
     #include "mp/mpi/node.h"
     #include "mp/mpi/l_filter_request.h"
     #include "mp/mpi/mpi_comm.h"
     #include "mp/mpi/mpi_request.h"


   /* ... Functions / Funciones ....................................... */

      int     MPI_Recv_init
      (
        IN        char         *data_buff,
        IN        int           data_count,
        IN        MPI_Datatype  data_type,
        IN        int           from,
        IN        int           tag,
        IN        MPI_Comm      comm,
        INOUT     MPI_Request  *mpi_req
      ) ;


   /* ................................................................. */


 #ifdef  __cplusplus
    }
 #endif

#endif  /* MPI_RECV_INIT_H */


