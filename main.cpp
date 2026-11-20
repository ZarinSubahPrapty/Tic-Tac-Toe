
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <optional>
#include <algorithm>
#include <cstdint>

namespace {
constexpr unsigned int WINDOW_WIDTH = 900;
constexpr unsigned int WINDOW_HEIGHT = 760;
constexpr float CELL_SIZE = 142.f;
constexpr float CELL_GAP = 14.f;
constexpr float BOARD_X = 222.f;
constexpr float BOARD_Y = 190.f;

const sf::Color BACKGROUND(255, 241, 246);
const sf::Color CARD(255, 255, 255);
const sf::Color PINK(255, 105, 145);
const sf::Color PURPLE(143, 112, 232);
const sf::Color DARK(76, 57, 91);
const sf::Color MUTED(145, 127, 151);
const sf::Color MINT(190, 239, 218);
const sf::Color YELLOW(255, 222, 130);
const sf::Color SHADOW(238, 215, 228);

using Board = std::array<char, 9>;

void drawRoundedRect(sf::RenderTarget& target, sf::Vector2f position,
                     sf::Vector2f size, float radius, sf::Color color) {
    sf::RectangleShape middle({size.x - 2.f * radius, size.y});
    middle.setPosition({position.x + radius, position.y});
    middle.setFillColor(color);
    target.draw(middle);

    sf::RectangleShape center({size.x, size.y - 2.f * radius});
    center.setPosition({position.x, position.y + radius});
    center.setFillColor(color);
    target.draw(center);

    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            sf::CircleShape corner(radius);
            corner.setPosition({
                position.x + (x == 0 ? 0.f : size.x - 2.f * radius),
                position.y + (y == 0 ? 0.f : size.y - 2.f * radius)
            });
            corner.setFillColor(color);
            target.draw(corner);
        }
    }
}

void drawText(sf::RenderTarget& target, const sf::Font& font,
              const std::string& value, unsigned int size,
              sf::Color color, sf::Vector2f position,
              bool centered = false) {
    sf::Text text(font, value, size);
    text.setFillColor(color);

    if (centered) {
        const auto bounds = text.getLocalBounds();
        text.setOrigin({
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        });
    }

    text.setPosition(position);
    target.draw(text);
}

bool loadFont(sf::Font& font) {
    const std::array<std::string, 4> paths = {
        "assets/arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/segoeui.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    };

    for (const auto& path : paths) {
        if (font.openFromFile(path))
            return true;
    }

    return false;
}

int winner(const Board& board) {
    constexpr int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto& line : lines) {
        const char a = board[line[0]];

        if (a != ' ' && a == board[line[1]] && a == board[line[2]])
            return a == 'X' ? 1 : 2;
    }

    return 0;
}

bool boardFull(const Board& board) {
    return std::none_of(board.begin(), board.end(),
                        [](char cell) { return cell == ' '; });
}

void resetGame(Board& board, char& currentPlayer, int& gameWinner,
               bool& draw, int& xScore, int& oScore, int& draws) {
    board.fill(' ');
    currentPlayer = 'X';
    gameWinner = 0;
    draw = false;
}

void drawMark(sf::RenderTarget& target, char mark, sf::Vector2f center) {
    if (mark == 'X') {
        sf::RectangleShape slash({12.f, 88.f});
        slash.setOrigin({6.f, 44.f});
        slash.setPosition(center);
        slash.setRotation(sf::degrees(45.f));
        slash.setFillColor(PINK);
        target.draw(slash);

        sf::RectangleShape backslash({12.f, 88.f});
        backslash.setOrigin({6.f, 44.f});
        backslash.setPosition(center);
        backslash.setRotation(sf::degrees(-45.f));
        backslash.setFillColor(PINK);
        target.draw(backslash);
    } else if (mark == 'O') {
        sf::CircleShape ring(36.f);
        ring.setOrigin({36.f, 36.f});
        ring.setPosition(center);
        ring.setFillColor(sf::Color::Transparent);
        ring.setOutlineThickness(11.f);
        ring.setOutlineColor(PURPLE);
        target.draw(ring);
    }
}

void drawButton(sf::RenderTarget& target, const sf::Font& font,
                sf::Vector2f position, sf::Vector2f size,
                const std::string& label, sf::Color color, bool hovered) {
    drawRoundedRect(target, {position.x, position.y + 5.f}, size, 18.f, SHADOW);

    drawRoundedRect(target, position, size, 18.f,
        hovered ? sf::Color(
            static_cast<std::uint8_t>(std::min(255, color.r + 12)),
            static_cast<std::uint8_t>(std::min(255, color.g + 12)),
            static_cast<std::uint8_t>(std::min(255, color.b + 12)))
            : color);

    drawText(target, font, label, 20, DARK,
        {position.x + size.x / 2.f, position.y + size.y / 2.f}, true);
}

// HOME SCREEN
void drawHomeScreen(sf::RenderWindow& window, const sf::Font& font,
                    bool startHovered) {

    // Decorative bubbles
    sf::CircleShape bubble1(35.f);
    bubble1.setPosition({55.f, 95.f});
    bubble1.setFillColor(sf::Color(255, 215, 228));
    window.draw(bubble1);

    sf::CircleShape bubble2(24.f);
    bubble2.setPosition({790.f, 125.f});
    bubble2.setFillColor(sf::Color(218, 208, 255));
    window.draw(bubble2);

    sf::CircleShape bubble3(18.f);
    bubble3.setPosition({100.f, 620.f});
    bubble3.setFillColor(YELLOW);
    window.draw(bubble3);

    sf::CircleShape bubble4(30.f);
    bubble4.setPosition({760.f, 610.f});
    bubble4.setFillColor(MINT);
    window.draw(bubble4);

    // Main welcome card
    drawRoundedRect(window, {118.f, 160.f}, {664.f, 450.f}, 35.f, SHADOW);
    drawRoundedRect(window, {118.f, 150.f}, {664.f, 450.f}, 35.f, CARD);

    drawText(window, font, "WELCOME TO", 25, PURPLE,
             {450.f, 235.f}, true);

    drawText(window, font, "CANDY", 64, PINK,
             {450.f, 305.f}, true);

    drawText(window, font, "TIC-TAC-TOE!", 43, DARK,
             {450.f, 365.f}, true);

    drawText(window, font, "Sweet moves, friendly competition,",
             19, MUTED, {450.f, 425.f}, true);

    drawText(window, font, "and a whole lot of fun!", 
             19, MUTED, {450.f, 455.f}, true);

    // Start button
    drawButton(window, font, {325.f, 505.f}, {250.f, 65.f},
               "START GAME", MINT, startHovered);

    drawText(window, font, "Made with love and a little sweetness",
             14, MUTED, {450.f, 650.f}, true);
}

// GAME SCREEN
void drawGameScreen(sf::RenderWindow& window, const sf::Font& font,
                    const Board& board, char currentPlayer,
                    int gameWinner, bool draw, int xScore, int oScore,
                    bool resetHovered, bool homeHovered,
                    sf::Vector2f mousePoint) {

    drawText(window, font, "CANDY TIC-TAC-TOE", 38, DARK,
             {450.f, 54.f}, true);

    drawText(window, font, "A little game, a lot of fun!", 18, MUTED,
             {450.f, 100.f}, true);

    // Score cards
    drawRoundedRect(window, {230.f, 128.f}, {190.f, 48.f}, 16.f,
                    sf::Color(255, 220, 230));

    drawRoundedRect(window, {480.f, 128.f}, {190.f, 48.f}, 16.f,
                    sf::Color(229, 222, 255));

    drawText(window, font, "X  " + std::to_string(xScore), 20, PINK,
             {325.f, 152.f}, true);

    drawText(window, font, "O  " + std::to_string(oScore), 20, PURPLE,
             {575.f, 152.f}, true);

    // Board
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {

            const sf::Vector2f position(
                BOARD_X + col * (CELL_SIZE + CELL_GAP),
                BOARD_Y + row * (CELL_SIZE + CELL_GAP)
            );

            const sf::FloatRect cellBounds(position, {CELL_SIZE, CELL_SIZE});

            const bool hovered = cellBounds.contains(mousePoint) &&
                                 gameWinner == 0 && !draw;

            drawRoundedRect(window,
                {position.x, position.y + 5.f},
                {CELL_SIZE, CELL_SIZE}, 22.f, SHADOW);

            drawRoundedRect(window, position,
                {CELL_SIZE, CELL_SIZE}, 22.f,
                hovered ? sf::Color(255, 255, 255) : CARD);

            drawMark(window, board[row * 3 + col],
                {position.x + CELL_SIZE / 2.f,
                 position.y + CELL_SIZE / 2.f});
        }
    }

    std::string status;

    if (gameWinner == 1)
        status = "X wins! You're amazing!";
    else if (gameWinner == 2)
        status = "O wins! You're amazing!";
    else if (draw)
        status = "It's a draw! Great game!";
    else
        status = std::string("It's your turn, ") + currentPlayer + "!";

    drawText(window, font, status, 22, DARK,
             {450.f, 650.f}, true);

    drawButton(window, font, {350.f, 680.f}, {200.f, 52.f},
               "Play again", MINT, resetHovered);

    drawButton(window, font, {30.f, 680.f}, {150.f, 52.f},
               "Home", sf::Color(255, 220, 230), homeHovered);

    drawText(window, font, "Press R to restart  |  ESC to quit",
             14, MUTED, {450.f, 744.f}, true);
}
}

int main() {
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Candy Tic-Tac-Toe"
    );

    window.setFramerateLimit(60);

    sf::Font font;

    if (!loadFont(font))
        return 1;

    Board board;
    board.fill(' ');

    char currentPlayer = 'X';
    int gameWinner = 0;
    bool draw = false;

    int xScore = 0;
    int oScore = 0;
    int draws = 0;

    // Screen controls
    bool showHome = true;

    const sf::FloatRect startBounds({325.f, 505.f}, {250.f, 65.f});
    const sf::FloatRect resetBounds({350.f, 680.f}, {200.f, 52.f});
    const sf::FloatRect homeBounds({30.f, 680.f}, {150.f, 52.f});

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            else if (const auto* key =
                     event->getIf<sf::Event::KeyPressed>()) {

                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();

                if (!showHome && key->code == sf::Keyboard::Key::R) {
                    resetGame(board, currentPlayer, gameWinner,
                              draw, xScore, oScore, draws);
                }
            }

            else if (const auto* mouse =
                     event->getIf<sf::Event::MouseButtonPressed>()) {

                if (mouse->button == sf::Mouse::Button::Left) {

                    const sf::Vector2f point(
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    );

                    // HOME SCREEN CLICK
                    if (showHome) {
                        if (startBounds.contains(point)) {
                            showHome = false;

                            resetGame(board, currentPlayer, gameWinner,
                                      draw, xScore, oScore, draws);
                        }
                    }

                    // GAME SCREEN CLICK
                    else {

                        if (homeBounds.contains(point)) {
                            showHome = true;
                        }

                        else if (resetBounds.contains(point)) {
                            resetGame(board, currentPlayer, gameWinner,
                                      draw, xScore, oScore, draws);
                        }

                        else if (gameWinner == 0 && !draw) {

                            const float boardWidth =
                                3.f * CELL_SIZE + 2.f * CELL_GAP;

                            const sf::FloatRect boardBounds(
                                {BOARD_X, BOARD_Y},
                                {boardWidth, boardWidth}
                            );

                            if (boardBounds.contains(point)) {

                                const int col = static_cast<int>(
                                    (point.x - BOARD_X) /
                                    (CELL_SIZE + CELL_GAP)
                                );

                                const int row = static_cast<int>(
                                    (point.y - BOARD_Y) /
                                    (CELL_SIZE + CELL_GAP)
                                );

                                if (row >= 0 && row < 3 &&
                                    col >= 0 && col < 3) {

                                    const float localX = point.x -
                                        (BOARD_X + col * (CELL_SIZE + CELL_GAP));

                                    const float localY = point.y -
                                        (BOARD_Y + row * (CELL_SIZE + CELL_GAP));

                                    if (localX <= CELL_SIZE &&
                                        localY <= CELL_SIZE) {

                                        const int index = row * 3 + col;

                                        if (board[index] == ' ') {

                                            board[index] = currentPlayer;

                                            gameWinner = winner(board);

                                            if (gameWinner == 1)
                                                ++xScore;
                                            else if (gameWinner == 2)
                                                ++oScore;
                                            else if (boardFull(board)) {
                                                draw = true;
                                                ++draws;
                                            }

                                            if (gameWinner == 0 && !draw) {
                                                currentPlayer =
                                                    currentPlayer == 'X' ? 'O' : 'X';
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        const auto mousePosition = sf::Mouse::getPosition(window);

        const sf::Vector2f mousePoint(
            static_cast<float>(mousePosition.x),
            static_cast<float>(mousePosition.y)
        );

        window.clear(BACKGROUND);

        if (showHome) {

            const bool startHovered = startBounds.contains(mousePoint);

            drawHomeScreen(window, font, startHovered);
        }

        else {

            const bool resetHovered = resetBounds.contains(mousePoint);
            const bool homeHovered = homeBounds.contains(mousePoint);

            drawGameScreen(window, font, board, currentPlayer,
                           gameWinner, draw, xScore, oScore,
                           resetHovered, homeHovered, mousePoint);
        }

        window.display();
    }

    return 0;
}
