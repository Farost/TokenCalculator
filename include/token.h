#pragma once


#include <cstdint>
#include <cctype>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <string>

// Token = float num or operator: + - * / or ()


// Valid symbols for the calculator
enum Symbols : char {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	COM = ',',
	DOT = '.',
	OBR = '(',
	CBR = ')',
	SPC = ' ',
};

// Priorities of the symbols (groups)
enum Priorities : uint8_t {
	ONE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SPACE,
	LAST,
};

// There could be used vector or array (converting chars to size_ts) for better speed,
// but I've decided to leave some space for easy upgrades (adding new operands, etc.)
const std::unordered_map<Symbols, Priorities> sym_prior = { {ADD, ONE}, {SUB, ONE}, {MUL, TWO}, {DIV, TWO}, 
															{COM, THREE}, {DOT, THREE}, {OBR, FOUR}, 
															{CBR, FIVE}}; // no need of SPC here

class Token {
public:
	
	inline std::string getInfo() const { return m_info; }      // Get token's info
	inline Priorities getPrior() const { return m_prior; }	   // Get token's current priority
	inline size_t size() const { return m_info.size(); }	   // Get token's info's size (to get an easy access)

	char& operator[](size_t i);              // Deal with token's info (to get an easy access)
	const char& operator[](size_t i) const;

	uint8_t readChar(char ch);				 // Read next char for token

	void clearToken();						 // Return token to initial values

	bool isFinal = false;  // Does this token ready to be pushed (no more chars needed)
	bool isSaved = false;  // Should we save the input char for another token (used
						   // when we realise that this token is final only when we get an operand
					       // without spaces, for instance, '2.5 +' (here we should save '+'))
private:
	bool isDot = false;    // Is there already a dot in this token
	std::string m_info = "";
	Priorities m_prior = Priorities::LAST;

	uint8_t checkChar(char ch) const; // Check if the char is valid
};
