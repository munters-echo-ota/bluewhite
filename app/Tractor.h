#pragma once

#include "Implement.h"
#include "Dispatcher.h"
#include <thread>

class Tractor : public Implement
{
public:
	Tractor(ID Id);
	virtual ~Tractor();

	virtual void TurnOn();
	virtual void TurnOff();

private:
	Tractor(const Tractor&) = delete;
	Tractor & operator=(const Tractor&) = delete;

	static const int MAX_MSG_MTU_SIZE = 128;
	static const int MSG_PROTO_SYNC = 0xA5;
	typedef enum { COLLECT_HEADER, COLLECT_PAYLOAD } RX_STATE;
	typedef enum { MTYPE_CONTROL = 1, MTYPE_TELEMETRY } MSG_TYPE;

#pragma pack(push,1)
	typedef struct Header_t
	{
		uint8_t			preamble;
		uint8_t			payloadLen;
		uint8_t			msgType;
		uint16_t		crc;
	} Header;

	typedef struct Msg_t
	{
		Header			header;
		uint8_t			payload[1];
	} Msg;

	typedef struct MsgPayloadTelemetry_t
	{
		uint8_t			isOn;
		uint8_t			fuelLevel;
	} MsgPayloadTelemetry;

	typedef struct ControlMsg_t
	{
		Header			header;
		uint8_t			isOn;
	} ControlMsg;
#pragma pack(pop)

	void ThreadFunc();
	void SendControlCmd(bool isOn);
	void RxHandleByte(uint8_t Byte);
	void RxHandleMsg(uint8_t MsgType, const uint8_t* Msg, uint16_t Len);
	void RxReset();
	uint16_t CalculateCRC(const uint8_t* Buff, uint16_t Len);

	bool volatile	_quit;
	std::thread		_thread;
	uint8_t			_rxBuff[MAX_MSG_MTU_SIZE];
	int				_rxBuffIdx;
	RX_STATE		_rxState;
};

