#include "Game.h"
#include "Box2DHelper.h"
#include "Ragdoll.h"

Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	_pTexExplosion = new Texture();
	// CARGA DE TEXTURA DE LA EXPLOSION
	if (!_pTexExplosion->loadFromFile("../src/assets/images/explosion.png")) {
		cout << "No se pudo cargar la imagen: " << "../src/assets/images/explosion.png" << endl;
	}
	_explosion = new AnimatedObject(_pTexExplosion, 7, 0, 0, false, 160, 145, 7, 1);

	// CARGA DE TEXTURA DE BARRA DE ENERGIA
	_pSprEnergia = new Sprite();
	_pTexEnergia = new Texture();

	if (!_pTexEnergia->loadFromFile("../src/assets/images/barraEnergia.png")) {
		cout << "No se pudo cargar la imagen: " << "../src/assets/images/barraEnergia.png" << endl;
	}
	_pTexEnergia->setSmooth(true);
	_pSprEnergia->setTexture(*_pTexEnergia);
	_pSprEnergia->setScale(0.071f, 0.105f);
	_pSprEnergia->setPosition(21.7, 1.2);

	// CARGA DE TEXTURAS VARIAS
	texturaFondo.loadFromFile("../src/assets/images/background.png");
	texturaFondo.setSmooth(true);
	texturaBase.loadFromFile("../src/assets/images/base.png");
	texturaBase.setSmooth(true);
	texturaCanion.loadFromFile("../src/assets/images/canion.png");
	texturaCanion.setSmooth(true);
	texturaMouse.loadFromFile("../src/assets/images/mira1.png");
	texturaMouse.setSmooth(true);
	texturaBarrel.loadFromFile("../src/assets/images/barrel.png");
	texturaBarrel.setSmooth(true);
	texturaPaused.loadFromFile("../src/assets/images/paused.png");
	texturaPaused.setSmooth(true);
	texturaLevelOne.loadFromFile("../src/assets/images/levelOne.png");
	texturaLevelOne.setSmooth(true);
	texturaLevelTwo.loadFromFile("../src/assets/images/levelTwo.png");
	texturaLevelTwo.setSmooth(true);
	texturaLevelComplete.loadFromFile("../src/assets/images/levelComplete.png");
	texturaLevelComplete.setSmooth(true);
	texturaGameOver.loadFromFile("../src/assets/images/gameOver.png");
	texturaGameOver.setSmooth(true);

	// CARGA FUENTE PARA TEXTOS
	_txtFont.loadFromFile("../src/assets/fonts/Raceline Demo.otf");

	// TEXTO ANGULO DE DISPARO Y RAGDOLLS RESTANTES
	_txtAngle.setFont(_txtFont);
	_txtAngle.setCharacterSize(20);
	_txtAngle.setScale(0.1f, 0.1f);
	_txtAngle.setFillColor(sf::Color::White);
	_txtAngle.setString("00");
	_txtAngle.setPosition(66.8f, 1.6f);

	_txtRagdollsCount.setFont(_txtFont);
	_txtRagdollsCount.setCharacterSize(20);
	_txtRagdollsCount.setScale(0.1f, 0.1f);
	_txtRagdollsCount.setFillColor(sf::Color::White);
	_txtRagdollsCount.setString(std::to_string(_ragdollsCount));
	_txtRagdollsCount.setPosition(94.7f, 1.6f);

	sprFondo.setTexture(texturaFondo);
	sprBase.setTexture(texturaBase);
	sprCanion.setTexture(texturaCanion);
	sprMouse.setTexture(texturaMouse);
	sprBarrel.setTexture(texturaBarrel);
	sprPaused.setTexture(texturaPaused);
	sprLevelOne.setTexture(texturaLevelOne);
	sprLevelTwo.setTexture(texturaLevelTwo);
	sprLevelComplete.setTexture(texturaLevelComplete);
	sprGameOver.setTexture(texturaGameOver);
	sprFondo.setScale(0.108f, 0.13f);
	sprBase.setScale(0.02f, 0.02f);
	sprCanion.setScale(0.025f, 0.025f);
	sprMouse.setScale(0.025f, 0.025f);
	sprBarrel.setScale(0.017f, 0.019f);
	sprPaused.setScale(0.1f, 0.1f);
	sprLevelOne.setScale(0.1f, 0.1f);
	sprLevelTwo.setScale(0.1f, 0.1f);
	sprLevelComplete.setScale(0.1f, 0.1f);
	sprGameOver.setScale(0.1f, 0.1f);
	sprBase.setOrigin(texturaBase.getSize().x / 2, texturaBase.getSize().y / 2);
	sprCanion.setOrigin(texturaCanion.getSize().x / 4, texturaCanion.getSize().y / 2);
	sprMouse.setOrigin(texturaMouse.getSize().x / 2, texturaMouse.getSize().y / 2);
	sprBarrel.setOrigin(texturaBarrel.getSize().x / 2, texturaBarrel.getSize().y / 2);
	sprPaused.setOrigin(texturaPaused.getSize().x / 2, texturaPaused.getSize().y / 2);
	sprLevelOne.setOrigin(texturaPaused.getSize().x / 2, texturaPaused.getSize().y / 2);
	sprLevelTwo.setOrigin(texturaPaused.getSize().x / 2, texturaPaused.getSize().y / 2);
	sprLevelComplete.setOrigin(texturaPaused.getSize().x / 2, texturaPaused.getSize().y / 2);
	sprGameOver.setOrigin(texturaPaused.getSize().x / 2, texturaPaused.getSize().y / 2);
	sprBase.setPosition(5, 95);
	sprCanion.setPosition(4, 93);
	sprMouse.setPosition(0, 0);
	sprBarrel.setPosition(88.5, 93.0);
	sprPaused.setPosition(50, 50);
	sprLevelOne.setPosition(50, 50);
	sprLevelTwo.setPosition(50, 50);
	sprLevelComplete.setPosition(50, 50);
	sprGameOver.setPosition(50, 50);

	// RECURSOS DE AUDIO
	_menuEnterSound = new Sound();
	_explosionSound = new Sound();
	_gameOverSound = new Sound();
	_levelCompleteSound = new Sound();
	_exitSound = new Sound();
	_navMenuSound = new Sound();

	// CARGA DE MUSICA DE FONDO
	if (!_backgroundMusic.openFromFile("../src/assets/sounds/background.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/background.ogg" << endl;
	}
	_backgroundMusic.setLoop(true);
	_backgroundMusic.setVolume(30.0f);

	if (!_backgroundMenuMusic.openFromFile("../src/assets/sounds/menuBackground.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/menuBackground.ogg" << endl;
	}
	_backgroundMenuMusic.setLoop(true);
	_backgroundMenuMusic.setVolume(60.f);

	// CARGA EFECTOS DE SONIDO

	if (!_menuEnterBuffer.loadFromFile("../src/assets/sounds/enterMenu.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/menuEnter.ogg" << endl;
	}
	_menuEnterSound->setBuffer(_menuEnterBuffer);

	if (!_explosionBuffer.loadFromFile("../src/assets/sounds/explosion.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/explosion.ogg" << endl;
	}
	_explosionSound->setBuffer(_explosionBuffer);
	_explosionSound->setVolume(30.f);

	if (!_gameOverBuffer.loadFromFile("../src/assets/sounds/gameOver.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/gameOver.ogg" << endl;
	}
	_gameOverSound->setBuffer(_gameOverBuffer);

	if (!_exitBuffer.loadFromFile("../src/assets/sounds/exit.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/exit.ogg" << endl;
	}
	_exitSound->setBuffer(_exitBuffer);

	if (!_levelCompleteBuffer.loadFromFile("../src/assets/sounds/levelComplete.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/levelComplete.ogg" << endl;
	}
	_levelCompleteSound->setBuffer(_levelCompleteBuffer);

	if (!_navMenuBuffer.loadFromFile("../src/assets/sounds/navMenu.ogg")) {
		cout << "No se pudo cargar el archivo: " << "../src/assets/sounds/navMenu.ogg" << endl;
	}
	_navMenuSound->setBuffer(_navMenuBuffer);
	_navMenuSound->setVolume(40.f);


	delay = 3.0f;
	msgDelay = 3.0f;
	timer = 0.f;
	msgTimer = 0.f;
	frecuencyHz = 0.0f;
	dampingRatio = 0.0f;
	fps = 0.0f;
	angle = 0.0f; 
	angleRad = 0.0f; 
	dt = 0.0f;
	mouseDistance = 0.0f;

	paused = false;
	playing = false;
	verCuerpos = true;
	_ragdollsCount = 20;
	levelCount = 1;
	msgId = 0;

	levelComplete = false;
	msgEnded = true;
	msgOnScreen = false;
	gameOver = false;
	delayStart = false;
	delayEnded = true;

	wnd->setMouseCursorVisible(false);
	wnd->setVisible(true);
	mousePos = Vector2f(0, 0);
	verCuerpos = false;
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	frecuencyHz = 10.0f;
	dampingRatio = 0.5f;
	_menu = new Menu();
	_backgroundMenuMusic.play();
}

void Game::Loop()
{
	Clock clock;
	clock.restart();
	while(wnd->isOpen())
	{
		dt = clock.restart().asSeconds();
		wnd->clear(clearColor);
		DoEvents();
		if (playing && !paused) {
			if (!msgOnScreen) {
				CheckCollisions();
				UpdatePhysics();
			}
			Update(dt);
		}
		DrawGame();
		wnd->display();
	}
}

void Game::Update(float dt) {

	// Chequear estado del nivel actual ( 1 = el nivel fue superado / 2 = nivel no superado)
	if (!levelComplete || !gameOver) {
		if (actualLevel->Update(dt, verCuerpos) == 1) {
			levelComplete = true;
			delayStart = true;
			gameOver = false;
		}
		else if (actualLevel->Update(dt, verCuerpos) == 2) {
			gameOver = true;
			delayStart = true;
		}
	}
	// Si el nivel termina (gane o pierda) se dispara un timer de 3 segundos pre-mensaje en pantalla
	if (_ragdollsCount == 0 && !levelComplete && !gameOver) {
		gameOver = true;
		delayStart = true;
		delay = 3.0f;
	}
	
	// Si el timer pre-mensaje fue disparado se controla que este llegue al límite establecido.
	if (delayStart) {
		timer += dt;
		delayEnded = false;
		if (timer >= delay) {
			delayEnded = true;
			delayStart = false;
			_backgroundMusic.stop();
			if (levelComplete) {
				ShowMessage(2);
				if (_levelCompleteSound->getStatus() != Sound::Playing) {
					_levelCompleteSound->play();
				}
			}
			else if (gameOver) {
				ShowMessage(3);
				if (_gameOverSound->getStatus() != Sound::Playing) {
					_gameOverSound->play();
				}
			}
		}
	}
	// Si el mensaje se dispara inicia el timer de mensajes que dura 3 segundos.
	if (msgOnScreen) {
		msgEnded = false;
		msgTimer += dt;
		if (msgTimer >= msgDelay) {
			msgOnScreen = false;
			msgEnded = true;
			msgTimer = 0.f;
		}
	}
	// Si la animación de la explosión se está reproduciendo se la actualiza
	if (_explosion->GetStatus())
		_explosion->Update(dt);

	// Corrección de escala de la posición actual del cursor para calcular la distancia a la base del cañón.
	float newScaleX = mouseDistance * 0.005 / 7.6f;
	if (newScaleX > 0.072f)
		newScaleX = 0.072f;
	if (newScaleX < 0.005f)
		newScaleX = 0.005f;
	// Actualizar barra de energía del disparo
	_pSprEnergia->setScale(newScaleX, _pSprEnergia->getScale().y);

	// Acotar distancia del mouse entre 30 y 80 para no excederse o quedar corto de energía en el disparo.
	if (mouseDistance < 30) {
		mouseDistance = 30;
	}
	else if (mouseDistance > 80) {
		mouseDistance = 80;
	}
	// Si el timer pre-mensaje y el timer de mensajes finalizaron controlar si levelComplete o gameOver para procesar según corresponda.
	if (delayEnded && msgEnded) {
		if (levelComplete) {
			playing = false;
			actualLevel = nullptr;
			levelCount++;
			ResetZoom();
			_menu->Show("levelComplete");
			_backgroundMenuMusic.play();
		}
		else if (gameOver) {
			std::cout << "Fin del juego" << std::endl;
			_backgroundMenuMusic.play();
			GameOver();
		}
	}
}

void Game::LoadLevel() {
	// Setear todo para el incio de un nivel.
	timer = 0.f;
	msgTimer = 0.f;
	levelComplete = false;
	gameOver = false;
	delayEnded = true;
	msgEnded = true;
	playing = true;
	_ragdollsCount = 20;
	_txtRagdollsCount.setString(std::to_string(_ragdollsCount));
	_backgroundMenuMusic.stop();
	_backgroundMusic.play();
	SetZoom();
	InitPhysics();
}

void Game::UpdatePhysics()
{
	// Si hay un nivel en juego procesar la física. Sino, solo procesar la lista de ragdolls (esta opción se usa solo para testeo).
	if (actualLevel != nullptr)
		actualLevel->UpdatePhysics();
	else {
		for (Ragdoll* ragdoll : _ragdollList) {
			ragdoll->Update();
		}
	}
	cannonPos = sprCanion.getPosition(); // Calcular posición del cañón.
	angleRad = atan2(mousePos.y - cannonPos.y, mousePos.x - cannonPos.x); // Calcular ángulo en radianes.
	mouseDistance = sqrt(pow(mousePos.x - cannonPos.x, 2) + pow(mousePos.y - cannonPos.y, 2)); // Calcular distancia desde la base al cursor del mouse.
	angle = angleRad * -180 / 3.1415f;
	// Corrección ángulo del cañón si éste es mayor a 90 o menor a 0 para limitarlo.
	if (angle >= 0 && angle <= 90) {
		angle *= -1;
		sprCanion.setRotation(angle);
		std::string angleTxt = std::to_string(angle);
		angleTxt = angleTxt.substr(1, 2);
		_txtAngle.setString(angleTxt);
	}
	
}

void Game::DoEvents()
{
	int option;
	Vector2f posMouse;
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		case sf::Event::MouseMoved:
			sprMouse.setPosition(evt.mouseMove.x * 0.1077, evt.mouseMove.y * 0.1261);
			mousePos = Vector2f(evt.mouseMove.x * 0.1077, evt.mouseMove.y * 0.1261);
			break;
		case Event::KeyPressed:
			switch (evt.key.code)
			{
			case Keyboard::Up:
				std::cout << "Tecla arriba presionada" << std::endl;
				if (!playing) {
					_navMenuSound->play();
				}
				break;
			case Keyboard::Down:
				std::cout << "Tecla abajo presionada" << std::endl;
				if (!playing) {
					_navMenuSound->play();
				}
				break;
			case Keyboard::Enter:
				std::cout << "Tecla Enter presionada" << std::endl;
				if (!playing) {
					_menuEnterSound->play();
				}
				if (!playing) {
					option = _menu->Update(evt.key.code);
					if (option == 0) {
						// salir del juego
						wnd->close();
					}
					else if (option == 4) {
						// ir al menú principal
						levelCount = 1;
						_menu->Show("standard");
					}
					else {
						// Jugar - Reintentar - Siguiente nivel
						if (levelCount < 3)
							LoadLevel();
					}
				}
				break;
			case Keyboard::P:
				if (playing) {
					if (paused) {
						std::cout << "Paused = false" << std::endl;
						paused = false;
						_backgroundMusic.play();
					}
					else {
						std::cout << "Paused = true" << std::endl;
						paused = true;
						_backgroundMusic.pause();
					}
				}
				break;
			case Keyboard::V:
				if (playing) {
					std::cout << "Tecla V presionada, verCuerpos vale: " << verCuerpos << std::endl;
					verCuerpos = !verCuerpos;
				}
				break;
			case Keyboard::Escape:
				// Finaliza cualquier nivel en jugeo y sale al menú principal.
				if (playing){
					playing = false;
					levelComplete = false;
					levelCount = 1;
					ResetZoom();
					_menu->Show("standard");
					_exitSound->play();
					_backgroundMenuMusic.play();
					_backgroundMusic.stop();
				}
				break;
			default:
				break;
			}
			// Actualizar el menú con la tecla presionada.
			_menu->Update(evt.key.code);
			break;
		case Event::MouseButtonPressed:
			// Procesar clic del mouse presionado 
			if (_ragdollsCount > 0 && playing && !msgOnScreen) {
				// Calcular las coordenadas del extremo del cañón.
				float x_end = (cannonPos.x * std::cosf(angleRad * -1)) + 4 * angleRad;
				float y_end = (cannonPos.y - 0.5 * std::sinf(angleRad * -1)) + angleRad * 6;
				// Reproducir la animación de la explosión.
				_explosion->RunXY(x_end, y_end);
				_explosionSound->play();
				// Lanzar el ragdoll correspondiente en el extremo del cañón.
				actualLevel->LaunchRagdoll(Vector2f(x_end + 10, y_end - 2), mouseDistance, angle);
				// Restar contador de ragdolls restantes y actualizar en pantalla.
				_ragdollsCount--;
				_txtRagdollsCount.setString(std::to_string(_ragdollsCount));
			}
			break;
		}
	}

}

void Game::GameOver()
{
	// Setar todo para el fin de juego
	playing = false;
	actualLevel = nullptr;
	_explosion->Stop();
	ResetZoom();
	_menu->Show("gameOver");
}

void Game::ResetZoom() {
	//Setear cámara para ver el menú
	View camara;
	// Posicion del view
	camara.setSize(928.0f, 793.0f);
	camara.setCenter(464.0f, 396.0f);
	wnd->setView(camara);
}

void Game::CheckCollisions()
{
	//Chequar colisiones para el nivel actual
	actualLevel->CheckCollisions();
}

void Game::SetZoom()
{
	// Setear cámara para ver la simulación
	View camara;
	// Posicion del view
	camara.setSize(100.0f, 100.0f);
	camara.setCenter(50.0f, 50.0f);
	wnd->setView(camara); //asignamos la camara
}


void Game::InitPhysics()
{
	// Crear nivel correspondiente y almacenarlo en "actualLevel"
	switch (levelCount)
	{
	case 1:
		actualLevel = new LevelOne(wnd, frameTime, true);
		ShowMessage(0);
		break;
	case 2:
		actualLevel = new LevelTwo(wnd, frameTime, true);
		ShowMessage(1);
		break;
	default:
		break;
	}

}

void Game::ShowMessage(int messageId)
{
	// Setear el ID de mensaje para que se muestre el correspondiente
	// messageId => 0: Carga level1 // 1: Carga level2 // 2: Nivel superado // 3: Fin del juego 
	msgId = messageId;
	msgOnScreen = true;
}

void Game::DrawGame()
{
	//Dibujar los sprites
	if (playing) {
		if (!verCuerpos) {
			wnd->draw(sprFondo);
		}
		actualLevel->Draw(*wnd);
		wnd->draw(sprCanion);
		wnd->draw(sprBase);
		wnd->draw(*_pSprEnergia);
		wnd->draw(_txtAngle);
		wnd->draw(_txtRagdollsCount);
		_explosion->Draw(wnd);
		wnd->draw(sprMouse);
		// Recorrer la lista de Ragdolls y dibujar
		for (Ragdoll* ragdoll : _ragdollList) {
			ragdoll->Draw(*wnd);
		}
		if (paused && !msgOnScreen) {
			wnd->draw(sprPaused);
		}
		// Dibujar mensajes en pantalla
		if (msgOnScreen) {
			switch (msgId)
			{
			case 0:
				wnd->draw(sprLevelOne);
				break;
			case 1:
				wnd->draw(sprLevelTwo);
				break;
			case 2:
				wnd->draw(sprLevelComplete);
				break;
			case 3:
				wnd->draw(sprGameOver);
				break;
			default:
				break;
			}
		}
	}
	else {
		_menu->DrawMenu(*wnd);
	}	
}

Game::~Game(void)
{
	delete _menu;
	delete actualLevel;
	delete _pTexExplosion;
	delete _pSprEnergia;
	delete _pTexEnergia;
	delete _explosion;
}