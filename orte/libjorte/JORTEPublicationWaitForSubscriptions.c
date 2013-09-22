/* JORTEPublicationWaitForSubscriptions.c */

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


JNIEXPORT jint JNICALL
Java_org_ocera_orte_Publication_jORTEPublicationWaitForSubscriptions
(JNIEnv *env, jobject obj, jlong j_appDomain_handle,
 jobject obj_ntpT, jlong jretries, jlong jnoSubscriptions)
{
  int            i;
  NtpTime        wait;

  #ifdef TEST_STAGE
    printf(":c: jORTEPublicationWaitForSubscriptions called.. \n");
  #endif

  wait = getNtpTime(env, obj_ntpT);
  #ifdef TEST_STAGE
    printf(":c: check: wait: sec = %"PRId32", fract = %"PRIu32"  \n",
           wait.seconds, wait.fraction);
  #endif

  // calling original native method
  i = ORTEPublicationWaitForSubscriptions((ORTEPublication *) j_appDomain_handle,
                                          wait,
                                          (unsigned int) jretries,
                                          (unsigned int) jnoSubscriptions);
  if (i == ORTE_BAD_HANDLE)
  {
    printf(":c!: wait for subscription failed! [bad sub handle] \n");
    return ORTE_BAD_HANDLE;
  }
  if (i == ORTE_TIMEOUT)
  {
    printf(":c!: wait for subscriptions - timeout! [number of subscriptions exhausted] \n");
    return ORTE_TIMEOUT;
  }
  if (i == ORTE_OK);
  return ORTE_OK;
}
