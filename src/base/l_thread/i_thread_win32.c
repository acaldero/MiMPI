/* ....................................................................
 *
 * Copyright Alejandro Calderon (1997-2000)
 * <acaldero@laurel.datsi.fi.upm.es>
 * See documentation for more information.
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * .................................................................... */



   /* ... Include / Inclusion ........................................... */

      #include "base/l_thread/i_thread_win32.h"


   /* ... Functions / Funciones ......................................... */


#if defined(HAVE_WINDOWS_H)

     /*
      *  Thread
      * --------
      */

     T_BOOL   I_THREAD_WIN32_createDetached
     (
       OUT  t_win32_thread   *thid,
       IN   t_win32_thcode    thcode,
       IN   void             *tharg
     )
     {
       /*
        *  check params
        */
       NULL_RET_FALSE(thid) ;

       /*
        *  create thread
        */
       (*thid) = CreateThread(NULL,0,thcode,tharg,0,NULL) ;
       if ((*thid) == NULL)
          {
            L_DEBUG_MSG_perror(DBG_ERROR,TRUE,"CreateThread:") ;
            return FALSE ;
          }

       /*
        *  return ok
        */
       return TRUE ;
     }

     T_BOOL   I_THREAD_WIN32_createJoinable
     (
       OUT  t_win32_thread   *thid,
       IN   t_win32_thcode    thcode,
       IN   void             *tharg
     )
     {
       /*
        *  check params
        */
       NULL_RET_FALSE(thid) ;

       /*
        *  create thread
        */
       (*thid) = CreateThread(NULL,0,thcode,tharg,0,NULL) ;
       if ((*thid) == NULL)
          {
            L_DEBUG_MSG_perror(DBG_ERROR,TRUE,"CreateThread:") ;
            return FALSE ;
          }

       /*
        *  return ok
        */
       return TRUE ;
     }


     T_BOOL   I_THREAD_WIN32_join
     (
       IN   t_win32_thread    thid,
       OUT  void            **thret
     )
     {
       /*
        *  wait for thread...
        */
	   (*thret) = (void *)WaitForSingleObject(thid,INFINITE) ; 

       /*
        *  return ok
        */
       return TRUE ;
     }


     /*  mtsdaToXZY  *
      * ------------ */
     T_CHAR  *I_THREAD_WIN32_mtsdaToString   
     ( 
       IN   t_win32_mtsda  *mtsda 
     )
     {
        T_CHAR  *pstr ;
        T_CHAR  *ret ;
        T_INT    mstat ;

       /*
        *  NULL mtsda value.
        */
        if (mtsda == NULL)
           {
             pstr = X_STRING_StrDup("NULL") ;
           }

       /*
        *  build mtsda value.
        */
        if (mtsda != NULL)
           {
             /* ... set to null ... */
             pstr = NULL ;
     
             /* ... add boolean ... */
             ret  = X_DTD_vBeginPutEnd(&pstr,"bool","ready",
                                       "%i",(mtsda)->ready) ;
             NULL_RET_NULL(ret) ;
             ret  = X_DTD_addln(&pstr) ;
             NULL_RET_NULL(ret) ;
     
             /* ... add lock ... */
			 mstat = WAIT_TIMEOUT ;
             ret  = X_DTD_vBeginPutEnd(&pstr,"pMutex","mutex",
                                       "lock") ;
             NULL_RET_NULL(ret) ;
             ret  = X_DTD_addln(&pstr) ;
             NULL_RET_NULL(ret) ;
/*
             mstat = WaitForSingleObject( ((mtsda)->mutex),0 ) ;
             switch (mstat)
             {
               case WAIT_TIMEOUT :
                    ret  = X_DTD_vBeginPutEnd(&pstr,"pMutex","mutex",
                                              "lock") ;
                    break ;
               case WAIT_FAILED :
                    ret  = X_DTD_vBeginPutEnd(&pstr,"pMutex","mutex",
                                              "invalid") ;
                    break ;
               default : ; 
                    ReleaseMutex( ((mtsda)->mutex) ) ;
                    ret  = X_DTD_vBeginPutEnd(&pstr,"pMutex","mutex",
                                              "unlock") ;
                    break ;
             }
             NULL_RET_NULL(ret) ;
             ret  = X_DTD_addln(&pstr) ;
             NULL_RET_NULL(ret) ;
*/     
             /* ... add cond ... */
             ret  = X_DTD_vBeginPutEnd(&pstr,"pCond","cond",
                                       "%p",(void *)&((mtsda)->event)) ;
             NULL_RET_NULL(ret) ;
             ret  = X_DTD_addln(&pstr) ;
             NULL_RET_NULL(ret) ;
           }

       /*
        *  return dtd
        */
        return pstr ;
     }

#endif


/* ...................................................................... */

