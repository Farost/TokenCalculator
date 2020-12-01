#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>

#include "token.h"

#define RETURN_ERROR(msg) { std::cout << msg << '\n'; return false; }


class Calculator {
public:
	// Singleton
	Calculator(const Calculator&) = delete;
	Calculator& operator=(const Calculator&) = delete;

	static Calculator& get() {
		static Calculator calc;
		return calc;
	}

	bool calcExpression(std::istream& is);     // Main function for expressions' calculation

	inline float getResult() const { return m_res; } // Return the calculation's result

	void printStacks(); // In case of errors or for dumb debug
private:
	// Singleton
	Calculator() : m_res(0.0f), m_last_prior(Priorities::SPACE) {}
	~Calculator() = default;

	bool isTokenNumber(const Token& t, float& t_float) const;           // Check if token contains a number
	
	bool checkBrackets(char ch, size_t& counter, bool& saved) const;    // Check if brackets number is valid
	bool checkChar(std::istream& is, Token& t, char ch, bool& eos);     // Check if a new char is valid
	bool checkOrder(Priorities prior, bool& is_unary) const;            // Check the order of last tokens
	bool checkOpStackPrior(Priorities prior);                           // Check operations' priorities 
																		// to know if calculations are needed
	bool calcUpper();													// Calculate using the upper operation
	bool pushToken(Token& t, bool& saved);                              // Push token after all checks

	void reinitCalc();

	// Stacks for tokens
	std::stack<float> m_nums;
	std::stack<char> m_ops;

	Priorities m_last_prior; // Last added operation's priority to compare with a new one
	float m_res;             // Final result
};
