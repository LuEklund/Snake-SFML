#include "GUI.h"

Gui::Gui(sf::View &gameView)
	: m_gameView(gameView)
{
}

Gui::~Gui()
{
}

//inits
bool Gui::initGui(sf::Font &font)
{
	m_textPlayer.setString("Score: 0");
	m_textPlayer.setFont(font);
	m_textPlayer.setCharacterSize(10);
	m_textPlayer.setFillColor(sf::Color::Cyan);
	m_textPlayer.setPosition(
		m_gameView.getCenter() - (m_gameView.getSize() / 2.f));
	return (true);
}


void Gui::setScore(const int score)
{
	std::stringstream ss;
	ss << "Score: " << score;
	m_textPlayer.setString(ss.str());
}

void Gui::update()
{
	m_textPlayer.setPosition(
		m_gameView.getCenter() - (m_gameView.getSize() / 2.f));
}

// inits
void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_textPlayer);
}
