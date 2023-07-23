#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
/**
* @brief Clase que representa el menú del juego. Se controla mediante sus métodos desde la clase game.
*/
class Menu
{
private:
	sf::Text _txtGameTitle;
	sf::Text _txtPlayButton;
	sf::Text _txtExitButton;
	sf::Text _txtNextLevelButton;
	sf::Text _txtRetryButton;
	sf::Text _txtHomeButton;
	sf::Text _txtReturnButton;
	sf::Text _txtLevelComplete;
	sf::Text _txtGameOver;
	sf::Font _txtFont;

	bool _isVisible;
	bool _levelComplete;
	bool _gameOver;
	bool _isPlayButtonSelected;
	bool _isExitButtonSelected;
	bool _isNextLevelButtonSelected;
	bool _isRetryButtonSelected;
	bool _isHomeButtonSelected;

public:
	Menu();
	void DrawMenu(sf::RenderWindow& RW);
	int Update(sf::Keyboard::Key key);
	void Show(std::string motive); // Motive puede ser => standard / levelComplete / gameOver
	void RefreshButtons();
	void Hide();
	~Menu();

};

