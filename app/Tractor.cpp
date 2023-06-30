#include "Tractor.h"
#include "ImplementModule.h"
#include "HAL_RS232.h"

Tractor::Tractor(ID Id) : _quit(false), _thread(&Tractor::ThreadFunc, this)
{
	_id = Id;
	HAL_RS232Init();
}

Tractor::~Tractor()
{
	_quit = true;
	_thread.join();
}

void Tractor::TurnOn()
{
	SendControlCmd(true);
}

void Tractor::TurnOff()
{
	SendControlCmd(false);
}

void Tractor::ThreadFunc()
{
	while (!_quit)
	{
		uint8_t byte;
		if (HAL_RS232WaitForByte(1, &byte))
			RxHandleByte(byte);
	}
}

void Tractor::SendControlCmd(bool isOn)
{
	ControlMsg m;
	m.header.preamble = MSG_PROTO_SYNC;
	m.header.msgType = MTYPE_CONTROL;
	m.header.payloadLen = sizeof(ControlMsg) - sizeof(Header);
	m.header.crc = CalculateCRC(((Msg*)&m)->payload, m.header.payloadLen);
	m.isOn = isOn;

	HAL_RS232SendBuff((uint8_t*)&m, sizeof(m));
}

void Tractor::RxHandleByte(uint8_t Byte)
{
	_rxBuff[_rxBuffIdx++] = Byte;
	Msg *msg = (Msg*)_rxBuff;

	switch (_rxState)
	{
	case COLLECT_HEADER:
		if (_rxBuffIdx == 1 && (msg->header.preamble != MSG_PROTO_SYNC))
			RxReset();
		else if (_rxBuffIdx >= sizeof(Header))
		{
			if (msg->header.payloadLen)
			{
				if (msg->header.payloadLen <= (MAX_MSG_MTU_SIZE - sizeof(Header)))
					_rxState = COLLECT_PAYLOAD;
				else
					RxReset();
			}
			else
				RxReset();
		}

		break;

	case COLLECT_PAYLOAD:
	{
		unsigned short payloadLen = _rxBuffIdx - sizeof(Header);

		if (payloadLen >= msg->header.payloadLen)
		{
			if (CalculateCRC(msg->payload, msg->header.payloadLen) == msg->header.crc)
				RxHandleMsg(msg->header.msgType, msg->payload, msg->header.payloadLen);

			RxReset();
		}
	}
	break;

	default:
		RxReset();
		break;
	}
}

void Tractor::RxHandleMsg(uint8_t MsgType, const uint8_t* Msg, uint16_t Len)
{
	switch (MsgType)
	{
		case MTYPE_TELEMETRY:
		{
			if (Len == sizeof(MsgPayloadTelemetry))
			{
				const MsgPayloadTelemetry* t = (MsgPayloadTelemetry*)Msg;
				ImplementModule::Instance()->OnTelemetry(GetId(), t->isOn, t->fuelLevel);
			}
			break;
		}

		default:
			break;
	}
}

void Tractor::RxReset()
{
	_rxState = COLLECT_HEADER;
	_rxBuffIdx = 0;
}

uint16_t Tractor::CalculateCRC(const uint8_t* Buff, uint16_t Len)
{
	uint16_t crc = 0;
	// calculate CRC
	return crc;
}
