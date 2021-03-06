/* ....................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <fgarcia,acaldero@laurel.datsi.fi.upm.es>
 * See documentation for more information.
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * .................................................................... */



   /* ... Includes .................................................... */

      #include "mp/xmp/map/node_server/l_ns/l_brow/l_authors.h"


   /* ... Funciones ................................................... */

      T_BOOL   L_AUTHORS_authors       
      ( 
        INOUT   t_nsInfo     *nsinfo,
        INOUT   t_nsHeader   *mess,
        IN      int          *dsd 
      )
      {
#if defined(SIGPIPE)
        void (*oldSigPipe) (int) ;
#endif

        /*
         *  say "ok, hi" to browser
         */
#if defined(SIGPIPE)
        oldSigPipe = signal(SIGPIPE,SIG_IGN) ;
#endif
        write( (*dsd), 
               HTTP_OK,
               strlen(HTTP_OK) ) ;
        write( (*dsd), 
               HTTP_WELCOME_AUTHORS, 
               strlen(HTTP_WELCOME_AUTHORS) ) ;

        write( (*dsd), 
               HTTP_AUTHORS, 
               strlen(HTTP_AUTHORS) ) ;

        /*
         *  say "bye" to browser
         */
        write( (*dsd), 
               HTTP_SIGN,
               strlen(HTTP_SIGN) ) ;
#if defined(SIGPIPE)
        signal(SIGPIPE,oldSigPipe) ;
#endif
        L_SB_unplug( &(nsinfo->sb), 
                     (*dsd) ) ;
        (*dsd) = 0 ;

        /*
         *  return ok
         */
        return TRUE ;
      }


  /* .................................................................... */


