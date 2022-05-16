#include "MSSFMLRendering.h"

MSSFMLRendering::MSSFMLRendering (MinesweeperBoard & boardSFML,
                                  MSSFMLView & viewSFML,
                                  MSSFMLController & controllerSFML)
                                  : board(boardSFML), view(viewSFML),
                                  controller(controllerSFML) {}


void MSSFMLRendering::Game() {

    sf::RenderWindow window (sf::VideoMode (view.GetScreenWidth(),
            view.GetScreenHeight()),"Minesweeper");

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            controller.HandlingEvents(event);
        }

        window.clear(sf::Color(0, 32, 220));

        window.draw(view);

        if (board.GetGameState() == RUNNING)
        {
            if (controller.GetCurrentMouseYPosition() - view.GetHUDYSize() > 0)
                window.draw(controller);
        }

        Update();

        window.display();
    }
}

void MSSFMLRendering::Update() {

    board.GetFlagNumber();
    view.BoardFieldsSettings();
    view.SetGameStatusInfo();
    view.RevealMinesIfLost();
}
