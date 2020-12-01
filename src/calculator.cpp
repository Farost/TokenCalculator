#include "../include/calculator.h"


// In case if you're lazy (I used this while coding), but don't forget to catch errors
std::istream& operator>>(std::istream& is, Calculator& calc) {
	if (!calc.calcExpression(is)) throw std::runtime_error("Invalid expression in operator>>");
	return is;
}

// Had to create a one huge function to speed the calculations up
// (reading the stream && processing the numbers at the same moment, 
// not reading the stream in a string -> processing the string again)
bool Calculator::calcExpression(std::istream& is) {
	reinitCalc();
	size_t bracket_counter = 0;
	bool eos = false;
	bool saved = false;
	Token t;
	char ch;
	size_t chars_counter = 0;

	// We add ( at the beginning and ) at the end of every expression
	// to make unary operations valid and save the regular rules
	// of controlling the order of ops and nums without any need of 
	// additional check at the begginning and the end of the stream

	std::istringstream bracketstream("()");
	bracketstream >> ch;
	checkChar(bracketstream, t, ch, eos);
	pushToken(t, saved);

	while (!eos || saved) {
		if (saved || is >> std::noskipws >> ch) {
			++chars_counter;
			if (!checkBrackets(ch, bracket_counter, saved)) return false; 

			if (!checkChar(is, t, ch, eos)) return false;

			if (!pushToken(t, saved)) return false;
		}
		else eos = true;
	}

	if (chars_counter) {
		bracketstream >> ch;
		if (!checkChar(bracketstream, t, ch, eos)) return false;
		if (!pushToken(t, saved)) return false;

		if (saved) { // Don't forget about the last ')' if it's saved
			if (!checkChar(bracketstream, t, ch, eos)) return false;
			if (!pushToken(t, saved)) return false;

		}
	}
	else {
		RETURN_ERROR("The expression is empty")
	}

	if (bracket_counter) {
		RETURN_ERROR("Incorrect bracket balance!")
	}
	
	if (m_ops.size() || m_nums.size() > 1)
		RETURN_ERROR("Can't calculate the result")

	m_res = round(m_nums.top() * 100) / 100; // Calculations are already done, the result is here
	m_nums.pop();
	return true;
}


bool Calculator::isTokenNumber(const Token& t, float& t_float) const {
	if (t.size() && std::isdigit(t[0])) {
		t_float = std::stof(t.getInfo());
		return true;
	}
	else {
		t_float = 0.0f;
		return false;
	}
}


bool Calculator::checkBrackets(char ch, size_t& counter, bool& saved) const {

	if (ch == '(' && !saved) {
		++counter;
	}
	if (ch == ')' && !saved) {

		if (!counter) {
			RETURN_ERROR("Incorrect bracket balance!")
		}
		--counter;
	}
	saved = false;
	
	return true;
}


bool Calculator::checkChar(std::istream& is, Token& t, char ch, bool& eos) {
	uint8_t prior = t.readChar(ch);

	if (!prior) {
		while (!eos && prior != Priorities::SPACE) {     // To print "incorrect abs", not "incorrect a"
			if (!(is >> std::noskipws >> ch)) {			 // for the string "1 + 5 + abs * 8"
				eos = true;
			}
			prior = t.readChar(ch);
		}
		RETURN_ERROR("Incorrect token " << t.getInfo())
	}

	return true;
}


bool Calculator::checkOrder(Priorities prior, bool& is_unary) const {

	switch (prior) {
	case Priorities::ONE: 
	case Priorities::TWO:
		switch (m_last_prior) {
		case Priorities::ONE:
		case Priorities::TWO:
			RETURN_ERROR("ERROR: operator after operator")
			break;

		case Priorities::FOUR:
			if (prior == Priorities::ONE)
				is_unary = true;
			else 
				RETURN_ERROR("ERROR: operator after (")
			break;
		}
		break;

	case Priorities::FOUR:
		switch (m_last_prior) {
		case Priorities::FIVE:
			RETURN_ERROR("ERROR: ( after )")
			break;

		case Priorities::LAST:
			RETURN_ERROR("ERROR: ( after number")
			break;
		}
		break;

	case Priorities::FIVE:
		switch (m_last_prior) {
		case Priorities::ONE:
		case Priorities::TWO:
			RETURN_ERROR("ERROR: ) after operator")
			break;

		case Priorities::FOUR:
			RETURN_ERROR("ERROR: ) right after ( without tokens inside")
			break;

		}
		break;

	case Priorities::LAST:
		switch (m_last_prior) {
		case Priorities::FIVE:
			RETURN_ERROR("ERROR: number after )")
			break;

		case Priorities::LAST:
			RETURN_ERROR("ERROR: number after another number")
			break;
		}	
		break;
	}

	return true;
}


bool Calculator::checkOpStackPrior(Priorities prior) {
	if (!m_ops.size()) return false;

	Priorities prev = sym_prior.at(static_cast<Symbols>(m_ops.top()));

	switch (prior) {
	case Priorities::ONE:
		switch (prev) {
		case Priorities::ONE:
		case Priorities::TWO:
			return true;
		}
		break;

	case Priorities::TWO:
		if (prev == prior) return true;
		break;

	case Priorities::FIVE:
		if (prev != Priorities::FOUR) return true;
		else m_ops.pop();
		break;
	}

	return false; // No processes are needed
}


bool Calculator::calcUpper() {

	if (m_nums.size() < 2) RETURN_ERROR("Tried to calculate while there are not enough nums")

	float second = m_nums.top();
	m_nums.pop();
	float first = m_nums.top();
	m_nums.pop();
	Symbols op = static_cast<Symbols>(m_ops.top());
	m_ops.pop();

	switch (op) {
	case Symbols::ADD:
		m_nums.push(first + second);
		break;
	case Symbols::SUB:
		m_nums.push(first - second);
		break;
	case Symbols::MUL:
		m_nums.push(first * second);
		break;
	case Symbols::DIV:
		m_nums.push(first / second);
		break;
	default:
		m_nums.push(first);
		m_nums.push(second);
		RETURN_ERROR("Found wrong operator while calculating")
	}
	
	return true;
}


bool Calculator::pushToken(Token& t, bool& saved) {
	Priorities prior = Priorities::LAST;
	bool is_unary = false;

	if (t.isFinal) {
		if (t.isSaved) saved = true;

		float t_float;
		if (isTokenNumber(t, t_float)) {
			if (!checkOrder(prior, is_unary)) return false;
			m_nums.push(t_float);		
		}
		else {
			Symbols sym;
			if (t.size()) sym = static_cast<Symbols>(t[0]);

			if (t.size() && sym_prior.count(sym)) {
				prior = sym_prior.at(sym);
				if (!checkOrder(prior, is_unary)) return false;

				while (checkOpStackPrior(prior)) {
					if (!calcUpper()) return false; // Something went wrong and we can't calculate
				}

				if (is_unary) {
					m_nums.push(0.0f); // Unary operation
					is_unary = false;
				}
				if (prior != Priorities::FIVE) m_ops.push(t[0]);
			}
			else {
				RETURN_ERROR("Found a bugged token!") // This is nearly unreal, but who knows
			}

		}

		m_last_prior = t.getPrior();
		t.clearToken();
	}

	return true;
}

void Calculator::reinitCalc() {
	m_res = 0.0f;
	m_last_prior = Priorities::SPACE;
	while (m_nums.size()) m_nums.pop();
	while (m_ops.size()) m_ops.pop();
}

void Calculator::printStacks() { 
	std::cout << "Calculator NUMS: " << std::endl;
	while (m_nums.size()) {
		std::cout << m_nums.top() << " / ";
		m_nums.pop();
	}
	std::cout << std::endl;

	std::cout << "Calculator OPS:" << std::endl;
	while (m_ops.size()) {
		std::cout << m_ops.top() << " ";
		m_ops.pop();
	}
	std::cout << std::endl;
}