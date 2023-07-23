#include "Menu.h"
Menu::Menu() {

	_isVisible = true;
	_isPlayButtonSelected = true;
	_isExitButtonSelected = false;
	_isRetryButtonSelected = false;
	_isNextLevelButtonSelected = false;
	_isHomeButtonSelected = false;

	_gameOver = false;
	_levelComplete = false;

	_txtFont.loadFromFile("../src/assets/fonts/Raceline Demo.otf");

	// Texto título del juego

	_txtGameTitle.setFont(_txtFont);
	_txtGameTitle.setCharacterSize(50);
	_txtGameTitle.setFillColor(sf::Color::Red);
	_txtGameTitle.setString("Ragdoll Cannon Clone");
	_txtGameTitle.setPosition(220, 250);

	// Textos botones

	_txtPlayButton.setFont(_txtFont);
	_txtPlayButton.setCharacterSize(40);
	_txtPlayButton.setFillColor(sf::Color::Yellow);
	_txtPlayButton.setOutlineColor(sf::Color::Red);
	_txtPlayButton.setOutlineThickness(1.0f);
	_txtPlayButton.setString("Jugar");
	_txtPlayButton.setPosition(410, 350);

	_txtExitButton.setFont(_txtFont);
	_txtExitButton.setCharacterSize(40);
	_txtExitButton.setFillColor(sf::Color::White);
	_txtExitButton.setOutlineColor(sf::Color::Red);
	_txtExitButton.setString("Salir");
	_txtExitButton.setPosition(415, 420);

	_txtNextLevelButton.setFont(_txtFont);
	_txtNextLevelButton.setCharacterSize(40);
	_txtNextLevelButton.setFillColor(sf::Color::Yellow);
	_txtNextLevelButton.setOutlineColor(sf::Color::Red);
	_txtNextLevelButton.setOutlineThickness(1.0f);
	_txtNextLevelButton.setString("Siguiente nivel");
	_txtNextLevelButton.setPosition(340, 350);

	_txtRetryButton.setFont(_txtFont);
	_txtRetryButton.setCharacterSize(40);
	_txtRetryButton.setFillColor(sf::Color::Yellow);
	_txtRetryButton.setOutlineColor(sf::Color::Red);
	_txtRetryButton.setOutlineThickness(1.0f);
	_txtRetryButton.setString("Reintentar");
	_txtRetryButton.setPosition(380, 350);

	_txtHomeButton.setFont(_txtFont);
	_txtHomeButton.setCharacterSize(40);
	_txtHomeButton.setFillColor(sf::Color::White);
	_txtHomeButton.setOutlineColor(sf::Color::Red);
	_txtHomeButton.setString("Menu principal");
	_txtHomeButton.setPosition(340, 420);

	// Textos de los mensajes

	_txtLevelComplete.setFont(_txtFont);
	_txtLevelComplete.setCharacterSize(50);
	_txtLevelComplete.setFillColor(sf::Color::Green);
	_txtLevelComplete.setString("Nivel superado");
	_txtLevelComplete.setPosition(290, 600);

	_txtGameOver.setFont(_txtFont);
	_txtGameOver.setCharacterSize(50);
	_txtGameOver.setFillColor(sf::Color::Green);
	_txtGameOver.setString("Fin del juego");
	_txtGameOver.setPosition(330, 600);

};

void Menu::DrawMenu(sf::RenderWindow& RW) {
	RW.draw(_txtGameTitle);
	if (!_gameOver && !_levelComplete) {
		RW.draw(_txtPlayButton);
		RW.draw(_txtExitButton);
	}
	else {
		RW.draw(_txtHomeButton);
	}
	
	if (_gameOver) {
		RW.draw(_txtGameOver);
		RW.draw(_txtRetryButton);
	}
	if (_levelComplete) {
		RW.draw(_txtLevelComplete);
		RW.draw(_txtNextLevelButton);
	}
	
};

int Menu::Update(sf::Keyboard::Key key) {
	switch (key)
	{
	case sf::Keyboard::Up:
		if (!_gameOver && !_levelComplete && !_isPlayButtonSelected) {
			_isPlayButtonSelected = true;
			_isExitButtonSelected = false;
		}
		if (_gameOver && !_isRetryButtonSelected) {
			_isRetryButtonSelected = true;
			_isHomeButtonSelected = false;
		}
		if (_levelComplete && !_isNextLevelButtonSelected) {
			_isNextLevelButtonSelected = true;
			_isHomeButtonSelected = false;
		}
		break;
	case sf::Keyboard::Down:
		if (!_gameOver && !_levelComplete && !_isExitButtonSelected) {
			_isPlayButtonSelected = false;
			_isExitButtonSelected = true;
		}
		if (_gameOver && _isRetryButtonSelected) {
			_isRetryButtonSelected = false;
			_isHomeButtonSelected = true;
		}
		if (_levelComplete && _isNextLevelButtonSelected) {
			_isNextLevelButtonSelected = false;
			_isHomeButtonSelected = true;
		}
		break;
	case sf::Keyboard::Enter:

		if (_isPlayButtonSelected) {
			!_isPlayButtonSelected;
			return 1; //Botón Jugar presionado
		}
		else if (_isExitButtonSelected) {
			!_isExitButtonSelected;
			return 0; //Botón Salir presionado
		}
		else if (_isNextLevelButtonSelected) {
			!_isNextLevelButtonSelected;
			return 2; //Botón Siguiente Nivel presionado
		}
		else if (_isRetryButtonSelected) {
			!_isRetryButtonSelected;
			return 3;  //Botón Reintentar presionado
		}
		else if (_isHomeButtonSelected) {
			!_isHomeButtonSelected;
			return 4; //Botón Menú Principal presionado
		}
		break;
	default:
		break;
	}
	RefreshButtons();
};

void Menu::Show(std::string motive) { // Motive puede ser: standard / levelComplete / gameOver
	_isVisible = true;
	_isPlayButtonSelected = false;
	_isExitButtonSelected = false;
	_isHomeButtonSelected = false;
	_isNextLevelButtonSelected = false;
	_isRetryButtonSelected = false;

	if (motive == "standard") {
		_levelComplete = false;
		_gameOver = false;
		_isPlayButtonSelected = true;
	}
	else if (motive == "levelComplete") {
		_levelComplete = true;
		_gameOver = false;
		_isNextLevelButtonSelected = true;
	}
	else if (motive == "gameOver") {
		_levelComplete = false;
		_gameOver = true;
		_isRetryButtonSelected = true;
	}

	RefreshButtons();
};

void Menu::RefreshButtons() {
	// Cambio de colores en botones
	if (!_gameOver && !_levelComplete) {
		if (_isPlayButtonSelected) {
			_txtPlayButton.setFillColor(sf::Color::Yellow);
			_txtExitButton.setFillColor(sf::Color::White);
			_txtPlayButton.setOutlineThickness(1.0f);
			_txtExitButton.setOutlineThickness(0);
		}
		else {
			_txtPlayButton.setFillColor(sf::Color::White);
			_txtExitButton.setFillColor(sf::Color::Yellow);
			_txtPlayButton.setOutlineThickness(0);
			_txtExitButton.setOutlineThickness(1.0f);
		}
	}

	if (_isNextLevelButtonSelected && _levelComplete) {
		_txtNextLevelButton.setFillColor(sf::Color::Yellow);
		_txtHomeButton.setFillColor(sf::Color::White);
		_txtNextLevelButton.setOutlineThickness(1.0f);
		_txtHomeButton.setOutlineThickness(0);
	}
	else if (_levelComplete) {
		_txtNextLevelButton.setFillColor(sf::Color::White);
		_txtHomeButton.setFillColor(sf::Color::Yellow);
		_txtNextLevelButton.setOutlineThickness(0.f);
		_txtHomeButton.setOutlineThickness(1.0f);
	}

	if (_isRetryButtonSelected && _gameOver) {
		_txtRetryButton.setFillColor(sf::Color::Yellow);
		_txtHomeButton.setFillColor(sf::Color::White);
		_txtRetryButton.setOutlineThickness(1.0f);
		_txtHomeButton.setOutlineThickness(0.f);
	}
	else if (_gameOver) {
		_txtRetryButton.setFillColor(sf::Color::White);
		_txtHomeButton.setFillColor(sf::Color::Yellow);
		_txtRetryButton.setOutlineThickness(0.f);
		_txtHomeButton.setOutlineThickness(1.0f);
	}
}

void Menu::Hide() {
	_isVisible = false;
};

Menu::~Menu() {};