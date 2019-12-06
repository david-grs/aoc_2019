#include <iostream>
#include <vector>
#include <cstring>
#include <array>
#include <cmath>

struct day5
{
	enum struct Opcode { Add = 1, Mul = 2, Read = 3, Write = 4, JNZ = 5, JZ = 6, LT = 7, EQ = 8, End = 99 };
	enum struct Mode { Position = 0, Immediate = 1 };

	void solve()
	{
		for (int opcode; std::cin >> opcode;)
		{
			mPg.push_back(opcode);
			if (std::cin.peek() == ',') std::cin.ignore();
			if (std::cin.peek() == '\n') break;
		}

		for (int ip = 0; Execute(ip); );
	}

	int Read(Mode mode, int ip)
	{
		switch (mode)
		{
		case Mode::Position: return mPg.at(mPg[ip]);
		case Mode::Immediate: return mPg[ip];
		}
		throw std::runtime_error("unexpected mode");
	}

	bool Execute(int& ip)
	{
		const std::array<Mode, 3> m{Mode{(mPg[ip] / 100) % 10}, Mode{(mPg[ip] / 1000) % 10}, Mode{(mPg[ip] / 10000) % 10}};
		const Opcode opcode{mPg[ip] % 100};

		switch (opcode)
		{
		case Opcode::End:
			return false;

		case Opcode::Add:
		case Opcode::Mul:
		{
			const int op1 = Read(m[0], ip + 1);
			const int op2 = Read(m[1], ip + 2);
			if (m[2] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[ip + 3]) = opcode == Opcode::Add ? op1 + op2 : op1 * op2;
			ip += 4;
			break;
		}

		case Opcode::Read:
			int value;
			std::cout << "read "; std::cout.flush();
			std::cin >> value;
			if (m[0] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[ip + 1]) = value;
			ip += 2;
			break;

		case Opcode::Write:
			std::cout << Read(m[0], ip + 1) << " ";
			ip += 2;
			break;

		case Opcode::JNZ:
			if (Read(m[0], ip + 1) != 0)
				ip = Read(m[1], ip + 2);
			else
				ip += 3;
			break;

		case Opcode::JZ:
			if (Read(m[0], ip + 1) == 0)
				ip = Read(m[1], ip + 2);
			else
				ip += 3;
			break;

		case Opcode::LT:
			if (m[2] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[ip + 3]) = Read(m[0], ip + 1) < Read(m[1], ip + 2) ? 1 : 0;
			ip += 4;
			break;

		case Opcode::EQ:
			if (m[2] != Mode::Position) throw std::runtime_error("unexpected mode");
			mPg.at(mPg[ip + 3]) = Read(m[0], ip + 1) == Read(m[1], ip + 2) ? 1 : 0;ip += 4;
			break;
		}
		return true;
	}

private:
	std::vector<int> mPg;

};

int main()
{
	day5 d;
	d.solve();
	return 0;
}

