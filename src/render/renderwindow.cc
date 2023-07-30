#include "renderwindow.h"

RenderWindow::RenderWindow(Board* board): ChessRender{board} {
    // Set up colors
    window.addColor(Color::Black, "00", "00", "00");
    window.addColor(Color::White, "ff", "ff", "ff");
    window.addColor(Color::ChessDotComBlack, "76", "96", "56");
    window.addColor(Color::ChessDotComWhite, "ee", "ee", "d2");
    window.addColor(Color::ChessDotComBg, "36", "46", "52");

    // Set up images
    addPieceSet("assets/chess_dot_com");
    addPieceSet("assets/irl");
}

void RenderWindow::addPieceSet(std::string folder_path) {
    const std::string teams[] = {
        "B", "W"
    };

    const std::string pieceNames[] = {
        "Bishop",
        "King",
        "Knight",
        "Pawn",
        "Queen",
        "Rook"
    };

    const std::string fileSuffix = ".png";

    for (std::string team : teams) {
        for (std::string pieceName : pieceNames) {
            std::string filePath = folder_path + "/" + team + pieceName + fileSuffix;
            window.addImage(filePath);
        }
    }
}

void RenderWindow::render() {
    // Draw bg
    window.fillRectangle(0, 0, WINDOW_W, WINDOW_W, currentTheme.bgColor);

    // Draw board
    for (int i = 0; i < 8; i++) {
        // Draw rank
        std::string rank = std::to_string(8 - i);
        window.drawString(BOARD_MARGIN/2, BOARD_TOP_LEFT.y() + SQUARE_W/2 + SQUARE_W*i, rank, currentTheme.textColor);

        for (int j = 0; j < 8; j++) {
            Coordinate c{j, 7-i};
            Piece piece = board->getSquare(c);
            
            unsigned long squareColor = isWhite(c) ? currentTheme.whiteSquareColor : currentTheme.blackSquareColor;
            Coordinate squareTopLeft = BOARD_TOP_LEFT + c*SQUARE_W;
            window.fillRectangle(squareTopLeft.x(), squareTopLeft.y(), SQUARE_W, SQUARE_W, squareColor);
        }
    }
    
    // Draw file
    for (int j = 0; j < 8; j++) {
        std::string file{(char)('a' + j)};
        window.drawString(BOARD_MARGIN + SQUARE_W/2 + SQUARE_W*j, BOARD_TOP_LEFT.y() + BOARD_W + BOARD_MARGIN/2, file, currentTheme.textColor);
    }

    window.putImage("assets/irl/WQueen.png", 300, 300, 256, 256);
}
