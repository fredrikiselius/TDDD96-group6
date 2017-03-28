#include "text.h"

/**
 * @brief text::text
 * @param col Colour of the new object
 * @param pos Starting point for the new object
 */
text::text(QColor col, QPoint pos, QString strng) : shape(col, pos) {
    string = strng;
}

/**
 * @brief text::draw
 * Draws the object on top of the specified QImage.
 * @param img QImage to draw on
 */
void text::draw(QImage &img) {
    QPainter painter(&img);
    setup_paint_tool(painter);

    QFont font = painter.font() ;
    font.setPointSize(FONT_SIZE);
    painter.setFont(font);

    painter.drawText(draw_end.x(), draw_end.y(), string);
    painter.end();
}

/**
 * @brief text::handle_new_pos
 * Function to handle the new position of the mouse.
 * Does not need to store the new position.
 * @param pos
 */
void text::handle_new_pos(QPoint pos) {
}