/*
 *  $Id: streamengine.h,v 1.2 2003/07/01 13:58:27 ajung Exp $
 *
 * SCTP implementation according to RFC 2960.
 * Copyright (C) 2000 by Siemens AG, Munich, Germany.
 *
 * Realized in co-operation between Siemens AG
 * and University of Essen, Institute of Computer Networking Technology.
 *
 * Acknowledgement
 * This work was partially funded by the Bundesministerium für Bildung und
 * Forschung (BMBF) of the Federal Republic of Germany (Förderkennzeichen 01AK045).
 * The authors alone are responsible for the contents.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * There are two mailinglists available at http://www.sctp.de which should be
 * used for any discussion related to this implementation.
 *
 * Contact: discussion@sctp.de
 *          tuexen@fh-muenster.de
 *          ajung@exp-math.uni-essen.de
 *
 * Purpose: This module processes datastreams, sending and
 *          receiving datachunks.
 *          In SEND direction the flow goes from ULP via 
 *          MessageDisatribution to WinFlowCtrl.
 *          In RECEIVE direction the data chunks are received from 
 *          RX_Control and delivered to ULP via MessageDistribution.
 *          Thats necessary to convert the associationID on ULP side
 *          to the association address on Stream_Engine side. 
 */
#ifndef STREAMENGINE_H
#define STREAMENGINE_H


#include  "globals.h"           /* boolean, etc */
#include  "messages.h"



/**
* return values for se_ulpreceive
*/
#define  RECEIVE_DATA           0 /* received data ok in streamengine */
#define  STREAM_ID_OVERFLOW     1 /* wrong stream Id from ulp */
#define  NO_DATA_AVAILABLE      2 /* no datagram in streamengine receive list */



/******************** Function Definitions *****************************************/


/* This function is called to instanciate one Stream Engine for an association.
   It is called by Message Distribution.
   called from MessageDisribution 
   returns: the pointer to the Stream Engine 
*/
void* se_new_stream_engine (unsigned int numberReceiveStreams,        /* max of streams to receive */
                            unsigned int numberSendStreams,           /* max of streams to send */
                            gboolean assocSupportsPRSCTP);

/* 
 * se_delete_stream_engine: Deletes a stream engine instance
 * 
 * Params: Pointer/handle which was returned by se_new()
 * Return value: error value
 */
void se_delete_stream_engine(void *instancePtr);



/* returns the number of in- and out-streams */
int se_readNumberOfStreams(unsigned short *inStreams, unsigned short *outStreams);



/**
 * This function is called to send a chunk.
 *  called from MessageDistribution
 * @return 0 for success, -1 for error (e.g. data sent in shutdown state etc.)
*/
int se_ulpsend(unsigned short streamId,
               unsigned char *buffer,
               unsigned int byteCount, unsigned int protocolId,
               short destAddressIndex, void* context, unsigned int lifetime,
               gboolean unorderedDelivery,  /* optional (=FALSE if none) */
               gboolean dontBundle);         /* optional (=null if none)  */



/* after all chunks in a SCTP pdu have been given to the
   Stream Engine module, we start reassembly and notifications */
int se_doNotifications(void);


/* This function is called from ULP to receive a chunk.
*/
short se_ulpreceive(unsigned char *buffer, unsigned int *byteCount, 
                    unsigned short streamId, unsigned short* streamSN,
                    unsigned int * tsn, unsigned int flags);




/*
 * This function is called from RX_Control to receive a chunk.
 */
int se_recvDataChunk(SCTP_data_chunk * dataChunk, unsigned int byteCount);


/**
 * function to return the number of chunks that can be retrieved
 * by the ULP - this function may need to be refined !!!!!!
 */
guint32 se_numOfQueuedChunks(void);

/**
 * function to return the number of streams that we may
 * send on
 */
guint16 se_numOfSendStreams(void);

/**
 * function to return the number of streams that we are allowed to
 * receive data on
 */
guint16 se_numOfRecvStreams(void);

int se_deliver_unreliably(unsigned int up_to_tsn, SCTP_forward_tsn_chunk* fw_tsn_chk);

int se_getQueuedBytes(void);


#endif                          /* STREAMENGINE_H */
