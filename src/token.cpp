#include "../include/token.h"


char& Token::operator[](size_t i) {
	return m_info[i];
}


const char& Token::operator[](size_t i) const {
	return m_info[i];
}


uint8_t Token::readChar(char ch) {

	uint8_t prior = checkChar(ch);

	if (m_info.size()) {
		if (prior == Priorities::THREE) { // Dot or comma
			m_info += '.';
			if (!isDot) {
				isDot = true;
			}
			else {
				return 0; // Invalid second . or , in a float num
			}
		}
		else if (prior == Priorities::ONE || prior == Priorities::TWO ||
				 prior == Priorities::SPACE || prior == Priorities::FIVE) {
			isFinal = true;
			if (prior != Priorities::SPACE) isSaved = true;
		}
	}
	else {
		if (prior == Priorities::THREE) {
			m_info = ch;
			return 0; // Invalid . or , without a digit before it
		}

	}

	if (prior == Priorities::ONE || prior == Priorities::TWO || prior == Priorities::FOUR ||
		prior == Priorities::FIVE) isFinal = true;

	if (prior != Priorities::THREE && prior != Priorities::SPACE && !(prior == Priorities::FIVE && isSaved))
		m_info += ch;

	if (m_info.size() == 1) {
		m_prior = static_cast<Priorities>(prior);
	}
	return prior;
}


uint8_t Token::checkChar(char ch) const {
	if (ch == Symbols::SPC) return Priorities::SPACE;
	if (isdigit(ch)) return Priorities::LAST;

	auto it = sym_prior.find(static_cast<Symbols>(ch));
	if (it != sym_prior.end()) return it->second;

	return 0;
}


void Token::clearToken() {
	m_info = "";
	m_prior = Priorities::LAST;
	isSaved = false;
	isFinal = false;
	isDot = false;
}