#include "stdafx.h"
#include "FunctionLeaveQuick.h"


namespace Commands
{
	FunctionLeaveQuick::FunctionLeaveQuick(FunctionID data, ThreadID threadid, __int64 timestamp) 
		: function((__int64)data), thread((__int64)threadid), code(0x19), hasEncoded(false), timestamp(timestamp)
	{
	}

	FunctionLeaveQuick::~FunctionLeaveQuick()
	{
	}

	std::wstring FunctionLeaveQuick::Name()
	{
		return L"Function Enter (Quick)";
	}

	std::wstring FunctionLeaveQuick::Description()
	{
		return L"Sends over an enter method, from the ELT calls.";
	}

	std::shared_ptr<std::vector<char>> FunctionLeaveQuick::Encode()
	{


		if (!hasEncoded)
		{
			size_t size = sizeof(__int32)	// len
				+ sizeof(short)				// code
				+ sizeof(__int64)			// timstamp
				+ sizeof(__int64)			// functionid
				+ sizeof(__int64)			// threadid
				+ sizeof(short);			// term

			auto vector = new char[size];
			short term = 0;
			auto v2 = (char*)memcpy(vector, &size, sizeof(__int32));
			v2 += sizeof(__int32);
			memcpy(v2, &code, sizeof(short));
			v2 += sizeof(short);
			memcpy(v2, &timestamp, sizeof(__int64));
			v2 += sizeof(__int64);
			memcpy(v2, &function, sizeof(__int64));
			v2 += sizeof(__int64);
			memcpy(v2, &thread, sizeof(__int64));
			v2 += sizeof(__int64);
			memcpy(v2, &term, sizeof(short));

			hasEncoded = true;
			auto v = std::vector<char>(vector, vector + size);
			m_internalvector = std::make_shared<std::vector<char>>(v);
		}

		return m_internalvector;

	}

	std::shared_ptr<ICommand> FunctionLeaveQuick::Decode(std::shared_ptr<std::vector<char>> &data)
	{
		return std::make_shared<FunctionLeaveQuick>(FunctionLeaveQuick(0,0,0));
	}

}