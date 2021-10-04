#ifndef __ANLTYPES_H__
#define __ANLTYPES_H__

#include <cstdlib>

//Maximum size of packet payload on comms channel
#define MAX_CTRL_DATA 256

namespace SSPDAQ{

  //Readable names for interface types
enum Comm_t{kUSB, kEthernet, kEmulated};

//==============================================================================
// Enumerated Constants
// These are defined by the SSP hardware spec
//==============================================================================

//Command to send to SSP
enum commandConstants {
	cmdNone			= 0,
	// Basic Commands
	cmdRead			= 1,
	cmdReadMask		= 2,
	cmdWrite		= 3,
	cmdWriteMask	= 4,
	// Array Commands
	cmdArrayRead	= 5,
	cmdArrayWrite	= 6,
	// Fifo Commands
	cmdFifoRead		= 7,
	cmdFifoWrite	= 8,
	numCommands
};

//Holder for status returned from SSP
enum statusConstants {
	statusNoError		= 0,
	statusSendError		= 1,
	statusReceiveError	= 2,
	statusTimeoutError	= 3,
	statusAddressError	= 4,
	statusAlignError	= 5,
	statusCommandError	= 6,
	statusSizeError		= 7,
	statusWriteError	= 8		// Returned if read-only address is written
};

//==============================================================================
// Types
//==============================================================================

  //Header to write out at top of millislice (i.e. this is the artdaq "metadata"
  //for a fragment
 struct MillisliceHeader {
   unsigned long startTime;
   unsigned long endTime;
   unsigned long triggerTime;
   unsigned int	length;				// Packet Length in unsigned ints (including header)
   unsigned int nTriggers;
   unsigned int triggerType;
   
   static const size_t sizeInUInts = 9;
   
 };

  //Structure defined by hardware, i.e. hardware output can be written straight into this struct
struct EventHeader {	// NOTE: Group fields are listed from MSB to LSB
	unsigned int	header;				// 0xAAAAAAAA
	unsigned short	length;				// Packet Length in unsigned ints (including header)
	unsigned short	group1;				// Trigger Type, Status Flags, Header Type
	unsigned short	triggerID;			// Trigger ID
	unsigned short	group2;				// Module ID, Channel ID
	unsigned short	timestamp[4];		// External Timestamp
								// Words 0-1 = Clocks since last sync pulse
								// Words 2-3 = Sync pulse count
	unsigned short	peakSumLow;			// Lower 16 bits of Peak Sum
	unsigned short	group3;				// Offset of Peak, Higher 8 bits of Peak Sum
	unsigned short	preriseLow;			// Lower 16 bits of Prerise
	unsigned short	group4;				// Lower 8 bits of integratedSum, Higher 8 bits of Prerise
	unsigned short	intSumHigh;			// Upper 16 bits of integratedSum
	unsigned short	baseline;			// Baseline
	unsigned short	cfdPoint[4];		// CFD Timestamp Interpolation Points
	unsigned short	intTimestamp[4];	// Internal Timestamp
								// Word 0 = Reserved for interpolation
								// Words 1-3 = 48 bit Timestamp
};
//static_assert(sizeof(struct EventHeader) == 12, "Check your assumptions on SSP EventHeader size");

  //byte-level structure of command header to send to SSP
struct CtrlHeader {
        unsigned int length;
	unsigned int address;
	unsigned int command;
	unsigned int size;
	unsigned int status;
};

  //Struct containing header followed by payload.
  //Since control packets are small, just allocate enough space to accommodate
  //longest possible message
struct CtrlPacket {
	CtrlHeader	header;
	unsigned int	data[MAX_CTRL_DATA];
};

}//namespace SSPDAQ
#endif
