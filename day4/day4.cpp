#include <iostream>
#include <regex>
#include <unordered_set>

class passport {
public:
	passport() :
		field_regex("^(byr|iyr|eyr|hgt|hcl|ecl|pid):.*$", std::regex_constants::ECMAScript),
		validity_regex("^byr:(19[2-9][0-9]|200[0-2])|iyr:20(1[0-9]|20)|eyr:20(2[0-9]|30)|hgt:(1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in)|hcl:#[0-9a-f]{6}|ecl:(amb|blu|brn|gry|grn|hzl|oth)|pid:[0-9]{9}$", std::regex_constants::ECMAScript),
		valid(true) {}

	void add_field(std::string field_definition) {
		std::smatch matches;
		if (std::regex_match(field_definition, matches, field_regex)) {
			auto field_key = matches[1];
			fields.insert(field_key);
			valid &= std::regex_match(field_definition, validity_regex);
		}
	}

	void reset() {
		fields.clear();
		valid = true;
	}

	bool is_complete() const { return fields.size() == 7; }
	bool is_valid() const { return valid; }
private:
	std::regex field_regex;
	std::regex validity_regex;
	std::unordered_set<std::string> fields;
	bool valid;
};


int main() {
	std::string line;
	passport current_passport;
	int count_complete = 0;
	int count_valid = 0;
	while (std::getline(std::cin, line)) {
		if (line.empty() || std::cin.eof()) {
			if (current_passport.is_complete()) {
				count_complete++;
				if (current_passport.is_valid()) {
					count_valid++;
				}
			}
			current_passport.reset();
		} else {
			std::stringstream linestream(line);
			std::string field_definition;
			while (linestream >> field_definition) {
				current_passport.add_field(field_definition);
			}
		}
	}
	if (current_passport.is_complete()) {
		count_complete++;
		if (current_passport.is_valid()) {
			count_valid++;
		}
	}
	std::cout << "1st solution: " << count_complete << std::endl;
	std::cout << "2nd solution: " << count_valid << std::endl;
	return 0;
}
