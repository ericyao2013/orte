/*
 *  $Id: RTPSUtils.c,v 0.0.0.1          2003/09/13 
 *
 *  DEBUG:  section 50          Utils
 *  AUTHOR: Petr Smolik                 petr.smolik@wo.cz
 *
 *  ORTE - OCERA Real-Time Ethernet     http://www.ocera.org/
 *  --------------------------------------------------------------------
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 */ 

#include "orte.h"

/**********************************************************************************/
int gavl_cmp_ntp_time(const NtpTime *a,const NtpTime *b) {
  return NtpTimeCmp(*a,*b);
}

/**********************************************************************************/
int gavl_cmp_sn(const SequenceNumber *a, const SequenceNumber *b) {
  return SeqNumberCmp(*a,*b);
}

/**********************************************************************************/
int 
gavl_cmp_guid(const GUID_RTPS *a, const GUID_RTPS *b) {
  //HID
  if (a->hid>b->hid) return 1;
  if (a->hid<b->hid) return -1;
  //AID
  if (a->aid>b->aid) return 1;
  if (a->aid<b->aid) return -1;
  //OID
  if (a->oid>b->oid) return 1;
  if (a->oid<b->oid) return -1;
  return 0;
}

/**********************************************************************************/
int 
gavl_cmp_str(const char *const *a,const char *const *b) {
  return strcmp(*a,*b);
}
/**********************************************************************************/
int 
getMaxMessageLength(ORTEDomain *d) {
  return d->domainProp.wireProp.metaBytesPerPacket-d->mbSend.cdrStream.length-
         RTPS_HEADER_LENGTH-20;
}

