

 #ifndef L_ALLOC_H
 #define L_ALLOC_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "base/l_basic/c_basic.h"


   /* ... Functions / Funciones ......................................... */

      /*  
       *   Standard Memory Functions 
       *  ---------------------------
       */

      T_POINTER  L_ALLOC_Malloc    
      ( 
        IN     T_U_INT    size 
      ) ;
      /* - totalmemo-=size, return 'size' bytes */
      /* - da 'size' bytes del total disponible */

      void       L_ALLOC_Free      
      ( 
        INOUT  T_POINTER *ptr 
      ) ;
      /* - totalmemo+=size (**ptr), (*ptr)=NULL */
      /* - retorna 'size' bytes al total disponible */

      T_POINTER  L_ALLOC_Realloc   
      ( 
        IN     T_POINTER  block, 
        IN     T_U_INT    size 
      ) ;
      /* - Change 'block' memory size into 'size' bytes. */
      /* - Cambia el taman~o del bloque 'block' a 'size' bytes */
      

      /*  
       *   Advanced Memory Functions
       *  ---------------------------
       */
      T_POINTER  L_ALLOC_MemMove   
      ( 
        IN     T_POINTER  dest,
        IN     T_POINTER  src,
        IN     T_U_INT    count 
      ) ;   
      /* - Copy from 'src' to 'dest' 'count' bytes */
      /* - Copia en 'dest' los 'count' primeros bytes de 'src' */

      T_POINTER  L_ALLOC_MemSet    
      ( 
        IN     T_POINTER  dest,
        IN     T_BYTE     byte,
        IN     T_U_INT    count 
      ) ;   
      /* - Fill 'count' first bytes of 'dest' with 
          'byte' value */
      /* - Rellena los 'count' primeros bytes de 'dest' con 
           el byte 'byte'. */

      T_POINTER  L_ALLOC_MemDup    
      ( 
        IN     T_POINTER  b, 
        IN     T_U_INT    bsize 
      ) ;
      /* - Return a memory zone of 'bsize' bytes with same
	   byte contents that 'bsize' bytes from 'b' pointer */
      /* - Retorna zona de memoria de memoria de 'bsize' bytes    
           cuyo contenido es una copia de los 'bsize' primeros 
           bytes de 'b' */

      T_POINTER  L_ALLOC_AllocAndSet 
      ( 
        IN  T_U_INT  bsize, 
        IN  T_CHAR   setval 
      ) ;
      /* - Request 'bsize' free space, and return this space
           filled with 'setval'. 
           Return NULL if someth was wrong */
      /* - Retorna zona de memoria de 'bsize' bytes cuyo valor 
           se ha fijado a setval */


      /*  
       *   Control Memory Functions 
       *  ---------------------------
       */
      T_U_LONG   L_ALLOC_Available 
      ( 
        void 
      ) ;
      /* - Return total memory available.
           In Unix, can be changes using 'limit' */
      /* - Retorna totalmemo, salvo en unix, pues es
           ampliable hasta el valor definido por el
           comando 'limit' */

      T_POINTER  L_ALLOC_ChkPtr    
      ( 
        IN     T_POINTER   b 
      ) ;
      /* - Explore if 'b' is a valid memory block.
           Any way, return 'b'. */
      /* - Explora que 'b' sea la referencia valida a un bloque
           de memoria, retornando ese mismo 'b'. */


   /* ... Inline / Macros ............................................... */

      #include "base/l_alloc/l_alloc.m"


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif 

