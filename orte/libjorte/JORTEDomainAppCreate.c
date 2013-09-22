/* JORTEDomainAppCreate.c */

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

// /////////////////////////////////////////////////////////////////////
// create default application domain
// /////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL
Java_org_ocera_orte_DomainApp_jORTEDomainDefaultAppCreate
(JNIEnv *env, jobject obj, jint jdomain, jboolean jsusp)
{
  jlong     d;

  #ifdef TEST_STAGE
    printf(":c: jsem pred ORTEDomainDefaultAppCreate() \n");
  #endif
  // call ORTE function
  d = (jlong) ORTEDomainAppCreate((int)jdomain,
                                 NULL,
                                 NULL,
                                 (Boolean) jsusp);
  if(!d) {
    printf(":!c: ORTEDomainDefaultAppCreate() FAILED.. \n");
    return 0;
  }
  #ifdef TEST_STAGE
    printf(":c: ORTEDomainDefautlAppCreate() ok.. + %#"PRIxPTR"\n", (intptr_t)d);
  #endif
  return (d);
}

// //////////////////////////////////////////////////////////////////////
// create user application domain
// //////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL
Java_org_ocera_orte_DomainApp_jORTEDomainAppCreate
(JNIEnv *env, jobject obj,
 jint jdomain,
 jlong propHandle,
 jlong eventsHandle,
 jobject obj_de,
 jboolean jsusp)
{
  // jni varibles
  JavaVM                 *jvm;
  jclass                  cls;
  jfieldID                fid;
  jlong                   d;
  //
  ORTEDomainAppEvents    *dom_events;
  JORTEDomainEventsContext_t  *domain_events_cont;

  #ifdef TEST_STAGE
    printf(":c: ORTEDomainAppCreate() called.. \n");
  #endif
  //assign domain events only if not null
  if(obj_de != NULL) {
    // memory alocation
    domain_events_cont = (JORTEDomainEventsContext_t *) malloc(sizeof(JORTEDomainEventsContext_t));
    // get jvm
    jint b = (*env)->GetJavaVM(env,&jvm);
    if (b < 0)
    {
      printf(":!c: getJavaVM() failed! \n");
      return 0;
    }
    // create global references
    domain_events_cont->jvm = jvm;
    // domain events
    domain_events_cont->obj_de = (*env)->NewGlobalRef(env, obj_de);
    // get new events
    dom_events = (ORTEDomainAppEvents *) eventsHandle;
    ////////////////////////////////////////////////
    // set new events & their prarameters
    // onRegFail
    dom_events->onRegFail = (ORTEOnRegFail) onRegFail;
    dom_events->onRegFailParam = (void *) domain_events_cont;
    // onMgrNew
    dom_events->onMgrNew = (ORTEOnMgrNew) onMgrNew;
    dom_events->onMgrNewParam = (void *) domain_events_cont;
    // onMgrDelete
    dom_events->onMgrDelete = (ORTEOnMgrDelete) onMgrDelete;
    dom_events->onMgrDeleteParam = (void *) domain_events_cont;
    // onAppRemoteNew
    dom_events->onAppRemoteNew = (ORTEOnAppRemoteNew) onAppRemoteNew;
    dom_events->onAppRemoteNewParam = (void *) domain_events_cont;
    // onAppDelete
    dom_events->onAppDelete = (ORTEOnAppDelete) onAppDelete;
    dom_events->onAppDeleteParam = (void *) domain_events_cont;
    // onPubRemoteNew
    dom_events->onPubRemoteNew = (ORTEOnPubRemote) onPubRemoteNew;
    dom_events->onPubRemoteNewParam = (void *) domain_events_cont;
    // onPubRemoteChanged
    dom_events->onPubRemoteChanged = (ORTEOnPubRemote) onPubRemoteChanged;
    dom_events->onPubRemoteChangedParam = (void *) domain_events_cont;
    // onPubDelete
    dom_events->onPubDelete = (ORTEOnPubDelete) onPubDelete;
    dom_events->onPubDeleteParam = (void *) domain_events_cont;
    // onSubRemoteNew
    dom_events->onSubRemoteNew = (ORTEOnSubRemote) onSubRemoteNew;
    dom_events->onSubRemoteNewParam = (void *) domain_events_cont;
    // onSubRemoteChanged
    dom_events->onSubRemoteChanged = (ORTEOnSubRemote) onSubRemoteChanged;
    dom_events->onSubRemoteChangedParam = (void *) domain_events_cont;
    // onSubDelete
    dom_events->onSubDelete = (ORTEOnSubDelete) onSubDelete;
    dom_events->onSubDeleteParam = (void *) domain_events_cont;
    ////////////////////////////////////////////////
    cls = (*env)->GetObjectClass(env, obj);
    if(cls == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: cls = NULL \n");
      #endif
      return 0;
    }
    // fieldID - domainEventsContextHandle
    fid = (*env)->GetFieldID(env,
                             cls,
                             "domainEventsContextHandle",
                             "J");
    if(fid == 0)
    {
      #ifdef TEST_STAGE
        printf(":!c: fid = NULL \n");
      #endif
      return 0;
    }
    (*env)->SetLongField(env,
                        obj,
                        fid,
                        (jlong) domain_events_cont);
  }
  // call ORTE function
  d = (jlong) ORTEDomainAppCreate((int)jdomain,
                                 (ORTEDomainProp *) propHandle,
                                 (ORTEDomainAppEvents *) eventsHandle,
                                 (Boolean) jsusp);
  if(!d) {
    printf(":!c: creating app domain failed! [NULL handle]  \n");
    return 0;
  }
  #ifdef TEST_STAGE
    printf(":c: ORTEDomainAppCreate() ok.. + %#"PRIxPTR"\n", (intptr_t)d);
  #endif
  return (d);
}
