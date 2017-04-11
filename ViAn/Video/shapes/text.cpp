#include "text.h"

/**
 * @brief Text::Text
 * @param col Colour of the new object
 * @param pos Starting point for the new object
 * @param strng String to be displayed
 * @param fnt_scl Font scale of the string
 */
Text::Text(QColor col, QPoint pos, QString strng, double fnt_scl) : Shape(col, pos) {
    string = strng;
    font_scale = fnt_scl;
}

/**
 * @brief Text::draw
 * Draws the object on top of the specified frame.
 * @param frame Frame to draw on.
 * @return Returns the frame with drawing.
 */
cv::Mat Text::draw(cv::Mat &frame) {
    cv::putText(frame, string.toStdString(), draw_end, cv::FONT_HERSHEY_SIMPLEX, font_scale,
                colour, LINE_THICKNESS);
    return frame;
}

/**
 * @brief Text::handle_new_pos
 * Function to handle the new position of the mouse.
 * Does not need to store the new position.
 * @param pos
 */
void Text::handle_new_pos(QPoint pos) {
}
