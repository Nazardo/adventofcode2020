#include <iostream>
#include <regex>
#include <stack>
#include <unordered_map>
#include <unordered_set>

long recursive_visit(std::unordered_map<std::string, std::unordered_map<std::string, int>> graph, std::string name) {
	auto it = graph.find(name);
	if (it == graph.end()) {
		return 1;
	}
	long result = 0;
	for (auto child_it = it->second.begin(); child_it != it->second.end(); ++child_it) {
		result += child_it->second * recursive_visit(graph, child_it->first);
	}
	return 1 + result;
}

int main() {
	std::regex regex_bagtype("^(\\w+ \\w+) bags contain");
	std::regex regex_childbag("(\\d+) (\\w+ \\w+) bags?");
	std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;
	std::unordered_map<std::string, std::unordered_map<std::string, int>> reverse_graph;
	std::string line;
	while (std::getline(std::cin, line)) {
		std::smatch matches;
		std::regex_search(line, matches, regex_bagtype);
		std::string container_name = matches[1];
		auto child_list_begin = std::sregex_iterator(line.begin(), line.end(), regex_childbag);
		auto child_list_end = std::sregex_iterator();
		for (auto it = child_list_begin; it != child_list_end; ++it) {
			std::smatch child_matches = *it;
			std::string child_name = child_matches[2];
			int child_count = std::atoi(child_matches[1].str().c_str());
			auto reverse_node_it = reverse_graph.try_emplace(child_name, std::unordered_map<std::string, int>()).first;
			reverse_node_it->second.insert_or_assign(container_name, child_count);
			auto node_it = graph.try_emplace(container_name, std::unordered_map<std::string, int>()).first;
			node_it->second.insert_or_assign(child_name, child_count);
		}
	}
	{
		// Search for all containers with "shiny gold" items inside
		std::stack<std::string> stack;
		std::unordered_set<std::string> visited;
		stack.push("shiny gold");
		while (!stack.empty()) {
			auto child = reverse_graph.find(stack.top());
			visited.insert(stack.top());
			stack.pop();
			if (child != reverse_graph.end()) {
				for (auto it = child->second.begin(); it != child->second.end(); ++it) {
					stack.push(it->first);
				}
			}
		}
		std::cout << "1st solution: " << visited.size() - 1 << std::endl;
	}
	{
		// Visit all nodes reachable from "shiny gold" node
		long result = recursive_visit(graph, "shiny gold");
		std::cout << "2nd solution: " << result - 1 << std::endl;
	}
	return 0;
}
