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



   /* ... Includes / Inclusiones ...................................... */

      #include "mp/xmp/map/node/l_nodes/l_nodecmd.h"


   /* ... Functions / Funciones ....................................... */

      T_BOOL   L_NODECMD_send_X_async
      (
        INOUT    t_nodeInfo     *node_info,
        INOUT    t_nodeReq      *send,
        INOUT    T_INT          *nodeli 
      )
      {
        t_mtsda        *reqmtsda ;
        t_reqli        *reqli ;
        t_reqRef       *peslabon ;
	int             chn ;
        t_params_xmp   *XMP_params ;
        T_INT           lessJump ;
        T_BOOL          ok ;

        /*
         *  trace
         */
        L_TRACE_MSG_PrintF(DEFCON_1,
                           "send_X_async (from %i, to %i, tagX=%i tagY=%i)",
                            send->from,
                            send->to,
                            send->tagX,
                            send->tagY) ;

        /*
         *  get configuration
         */
        XMP_params = L_NODECMD_getParams() ;
        lessJump   = XMP_params->MAX_SEND_THROUGH ;

        /*
         *  in list ?
         */
        ok = L_NODEGRP_isMember(nodeli,send->to) ;
        if (ok == FALSE)
           {
             L_TRACE_MSG_PrintF(DEFCON_2,
                                 "send_X_async 'to' (%i) not at node group",
                                 (send->to)) ;
             return FALSE ;
           }

        /*
         *  is connected ?
         */
        chn = L_NETMAN_getSock(node_info,(send->to)) ;
        if (chn == NID_NULL)
           {
             ok  = L_NETMAN_linkTo(node_info,(send->to)) ;
             FALSE_RET_FALSE(ok) ;
             chn = L_NETMAN_getSock(node_info,(send->to)) ;
             ok  = L_SNOOPY_createComunicationDaemons(node_info,chn) ;
             FALSE_RET_FALSE(ok) ;
           }
        if (chn == NID_ERROR)
           {
             L_TRACE_MSG_PrintF(DBG_ERROR,TRUE,
                                 "send_X_async BAD 'to' (%i) param",
                                 (send->to)) ;
             return FALSE ;
           }

        /*
         *  hand on !
         */
        reqmtsda = L_REQMAN_get_send_mtsda(node_info,chn) ;
        reqli    = L_REQMAN_get_send_reqli(node_info,chn) ;

        /*
         *  dispatch request
         */
        X_THREAD_lock( reqmtsda ) ;
        peslabon = L_REQMAN_submit(reqli,send,TRUE,NULL) ;
        if (peslabon == NULL)
           {
             X_THREAD_unlock( reqmtsda ) ;
             return FALSE ;
           }
        L_TRACE_MSG_PrintF(DEFCON_1,
                       "send_X_async inserted in reqli [%i] = %i",
                       chn,
                       reqli->nreqli) ;
        X_THREAD_signalReady( reqmtsda ) ;
        X_THREAD_unlock( reqmtsda ) ;
 
        /*
         *  trace
         */
        L_TRACE_MSG_PrintF(DEFCON_1,
                           "sent_X_async (from %i, to %i, tagX=%i tagY=%i)",
                            send->from,
                            send->to,
                            send->tagX,
                            send->tagY) ;

        /*
         *  return ok
         */
        return TRUE ;
      }


   /* ................................................................. */

