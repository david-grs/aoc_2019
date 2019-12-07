#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cstring>

class IntCode
{
public:
	explicit IntCode(const std::vector<int>& pg) :
	  mPg{pg}
	{}

	static IntCode FromStdin()
	{
		std::vector<int> pg;
		for (int opcode; std::cin >> opcode;)
		{
			pg.push_back(opcode);
			if (std::cin.peek() == ',') std::cin.ignore();
			if (std::cin.peek() == '\n') break;
		}
		return IntCode{pg};
	}

	void Reset(const IntCode& p)
	{
		if (p.mPg.size() != mPg.size()) throw 42;
		std::memcpy(mPg.data(), p.mPg.data(), p.mPg.size());
		mIp = 0;
	}

	template <class OnRead, class OnWrite>
	void Execute(OnRead onRead, OnWrite onWrite)
	{
		while (ExecuteInstruction(onRead, onWrite));
	}

	enum struct Opcode { Add = 1, Mul = 2, Read = 3, Write = 4, JNZ = 5, JZ = 6, LT = 7, EQ = 8, End = 99 };
	enum struct Mode { Position = 0, Immediate = 1 };

	int Read(Mode mode, int mIp)
	{
		switch (mode)
		{
		case Mode::Position: return mPg.at(mPg[mIp]);
		case Mode::Immediate: return mPg[mIp];
		}
		throw std::runtime_error("unexpected mode");
	}

	template <class OnRead, class OnWrite>
	bool ExecuteInstruction(OnRead onRead, OnWrite onWrite)
	{
		const std::array<Mode, 3> m{Mode{(mPg[mIp] / 100) % 10}, Mode{(mPg[mIp] / 1000) % 10}, Mode{(mPg[mIp] / 10000) % 10}};
		const Opcode opcode{mPg[mIp] % 100};

		switch (opcode)
		{
		case Opcode::End:
			return false;

		case Opcode::Add:
		case Opcode::Mul:
		{
			const int op1 = Read(m[0], mIp + 1);
			const int op2 = Read(m[1], mIp + 2);
			if (m[2] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[mIp + 3]) = opcode == Opcode::Add ? op1 + op2 : op1 * op2;
			mIp += 4;
			break;
		}

		case Opcode::Read:
		{
			int value = onRead();
			if (m[0] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[mIp + 1]) = value;
			mIp += 2;
			break;
		}

		case Opcode::Write:
			onWrite(Read(m[0], mIp + 1));
			mIp += 2;
			break;

		case Opcode::JNZ:
			if (Read(m[0], mIp + 1) != 0)
				mIp = Read(m[1], mIp + 2);
			else
				mIp += 3;
			break;

		case Opcode::JZ:
			if (Read(m[0], mIp + 1) == 0)
				mIp = Read(m[1], mIp + 2);
			else
				mIp += 3;
			break;

		case Opcode::LT:
			if (m[2] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[mIp + 3]) = Read(m[0], mIp + 1) < Read(m[1], mIp + 2) ? 1 : 0;
			mIp += 4;
			break;

		case Opcode::EQ:
			if (m[2] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[mIp + 3]) = Read(m[0], mIp + 1) == Read(m[1], mIp + 2) ? 1 : 0;mIp += 4;
			break;
		}
		return true;
	}

private:
	std::vector<int> mPg;
	std::size_t mIp;
};
