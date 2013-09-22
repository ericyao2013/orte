/**
  * This code provides conversion between JAVA a C environments.
  * The C functions are calling here and results are send to JAVA
  * native functions. It uses the header pregenerated by JAVA
  * (by command 'javah -jni class_with_native_function')
  *
  * @author Lukas Pokorny (lukas_pokorny@centrum.cz)
  * @author Martin Vajnar (martin.vajnar@gmail.com)
  * @author CTU FEE Prague - Department of Control Engineering (dce.felk.cvut.cz)
  * @author Project ORTE - OCERA Real Time Ethernet (www.ocera.org)
  * @author dedication to Kj
  * @version 0.1
  *
  *
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  */

#include "jorte/jorte.h"

  JNIEXPORT jboolean JNICALL Java_org_ocera_orte_types_DomainProp_jORTEDomainPropDestroy
  (
   JNIEnv *env,
   jobject obj,
   jlong propshandle,        //ORTEDomainProp handle
   jstring mgrs              //Managers
  )
  {
    int flag_ok = 0;
    ORTEDomainProp *dp = NULL;

    #ifdef TEST_STAGE
      printf(":c: jORTEDomainPropDestroy() called.. \n");
    #endif

    do {
      dp = (ORTEDomainProp *) propshandle;
      if(dp == 0) {
        #ifdef TEST_STAGE
          printf(":!c: *dp = NULL \n");
        #endif
        break;
      }

      if (mgrs != NULL) {
        //release fellow managers string
        (*env)->ReleaseStringUTFChars(env,mgrs,dp->mgrs);
      }

      //free DomainProperties memory
      free(dp);

      flag_ok = 1;
    } while (0);

    if(flag_ok) {
      return  ORTE_TRUE;
    }

    return ORTE_FALSE;
  }
