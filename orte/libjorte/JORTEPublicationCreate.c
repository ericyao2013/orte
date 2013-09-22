/* JORTEPublicationCreate.c */

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

// ### DOCASNE ##################################################################

// ### DOCASNE ##################################################################
int counter = 0;

void
sendCallBack(const ORTESendInfo *info,void *vinstance, void *sendCallBackParam)
{

  printf(":c: zacatek sendCallBack()..\n");

  switch (info->status) {
    case NEED_DATA:
      printf(":c:PUB: Sampling publication, count %d\n", counter++);
      printf(":c:PUB: !! DOCASNE - ZRUSIT!! - callback() u Publishera \n");
      break;
    case CQL:  //criticalQueueLevel
      break;
  }
}
// ### DOCASNE ##################################################################

// ### DOCASNE ##################################################################


// native method
JNIEXPORT jlong JNICALL
Java_org_ocera_orte_Publication_jORTEPublicationCreate
(JNIEnv   *env ,
 jobject   obj,
 jlong     dom_handle,
 jstring   j_topic,
 jstring   j_type_name,
 jobject   j_instance,
 jobject   j_persistence,
 jint      j_strength)
{
  ORTEPublication  *p = 0;
  ORTEDomain       *d;
  const char       *topic;
  const char       *typeName;
  void             *buffer;
  NtpTime           persistence;
  int               strength;
  int               flag_ok = 0;

  // check domain handle
  d = (ORTEDomain *) dom_handle;
  if(d == 0)
  {
    printf(":!c: publication create failed! [bad domain handle] \n");
    return 0;
  }
  // get topic
  topic = (*env)->GetStringUTFChars(env, j_topic, 0);
  if(topic == 0)
  {
    // OutOfMemoryError already thrown
    #ifdef TEST_STAGE
      printf(":!c: topic = NULL \n");
    #endif
    return 0;
  }
  // get typeName
  typeName = (*env)->GetStringUTFChars(env, j_type_name, 0);
  if(typeName == 0)
  {
    // OutOfMemoryError already thrown
    #ifdef TEST_STAGE
      printf(":!c: typeName = NULL \n");
    #endif
    // free memory
    (*env)->ReleaseStringUTFChars(env, j_topic, topic);
    return 0;
  }

  do
  {
    // get persistence
    persistence = getNtpTime(env, j_persistence);
    // get strenght
    strength = (int) j_strength;
    // get direct ByteBuffer pointer from Java
    buffer = (*env)->GetDirectBufferAddress(env, j_instance);
    if(buffer == 0)
    {
      printf(":!c: buffer create failed! \n");
      break;
    }
    // call ORTE function
    p = ORTEPublicationCreate(d,
                              topic,
                              typeName,
                              buffer,
                              &persistence,
                              strength,
                              sendCallBack, // BUDE NULL!!
                              NULL,
                              NULL);
    if(p == 0)
    {
      printf(":!c: publication create failed! \n");
      break;
    }
    // set flag
    flag_ok = 1;
  }  while(0);

  // free memory in every case
  (*env)->ReleaseStringUTFChars(env, j_topic, topic);
  (*env)->ReleaseStringUTFChars(env, j_type_name, typeName);
  //
  if (flag_ok == 0)
  {
    return 0;
  }
  return ((jlong) p);

}
