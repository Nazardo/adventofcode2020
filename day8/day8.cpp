#include <iostream>
#include <unordered_set>
#include <vector>

class instruction {
public:
	enum type_of_instruction {
		add,
		jump,
		nop,
	};
	instruction(type_of_instruction type, int argument) :
		type(type),
		argument(argument) {}
	type_of_instruction get_type() const { return type; }
	int get_argument() const { return argument; }
	void swap() {
		if (type == jump) { type = nop; }
		else if (type == nop) { type = jump; }
	}
private:
	type_of_instruction type;
	int argument;
};

void read_stream(
	std::istream& stream,
	std::vector<instruction>& instructions) {
	std::string command;
	int argument;
	instruction::type_of_instruction type;
	while (stream >> command) {
		stream >> argument;
		if (command[0] == 'j') {
			type = instruction::jump;
		} else if (command[0] == 'a') {
			type = instruction::add;
		} else {
			type = instruction::nop;
		}
		instructions.emplace_back(type, argument);
	}
}

bool run_program(
	const std::vector<instruction>& instructions,
	int& accumulator) {
	size_t program_counter = 0;
	std::unordered_set<size_t> set;
	while (set.find(program_counter) == set.end()
	    && program_counter < instructions.size()) {
		set.insert(program_counter);
		auto& i = instructions[program_counter];
		if (i.get_type() == instruction::add) {
			accumulator += i.get_argument();
		}
		if (i.get_type() == instruction::jump) {
			program_counter += i.get_argument();
		} else {
			program_counter += 1;
		}
	}
	return program_counter >= instructions.size();
}

int main() {
	int accumulator = 0;
	std::vector<instruction> instructions;
	read_stream(std::cin, instructions);
	run_program(instructions, accumulator);
	std::cout << "1st solution: " << accumulator << std::endl;
	bool finished_correctly = false;
	auto it = instructions.begin();
	while (!finished_correctly) {
		while (it->get_type() == instruction::add) {
			it++;
		}
		it->swap();
		accumulator = 0;
		finished_correctly = run_program(instructions, accumulator);
		it->swap();
		it++;
	}
	std::cout << "2nd solution: " << accumulator << std::endl;
	return 0;
}
