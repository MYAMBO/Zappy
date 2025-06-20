/*
** EPITECH PROJECT, 2025
** My_Shogi
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <string>
    #include <raylib.h>
    #include <functional>

using function = std::function<void()>;

namespace gui {
    namespace ui {
        class Button {
            public:
                Button(function actived);
                Button(function actived, Rectangle bounds, const std::string& text = "");
                ~Button();
        
                /**
                 * @brief Draw the button on the screen.
                 * This function draws the button with its current state (normal, hovered, pressed).
                 */
                void draw();

                /**
                 * @brief Update the button state based on mouse input.
                 * This function checks if the mouse is hovering over the button and updates its pressed state.
                 */
                void update();
                
                /**
                 * @brief Setter for the font size.
                 * This function allows you to set the font size of the text displayed on the button.
                 * @param size The font size to set.
                 */
                void setFontSize(int size);
                
                /**
                 * @brief Setter for the text color.
                 * This function allows you to set the color of the text displayed on the button.
                 * @param color The color of the text.
                 */
                void setTextColor(Color color);

                /**
                 * @brief Setter for the bounds.
                 * This functions allow you to set the bounds.
                 * @param bounds The rectangle defining the button's position and size.
                 */
                void setBounds(Rectangle bounds);
                
                /**
                 * @brief Setter for the text.
                 * This function allows you to set the text displayed on the button.
                 * @param text The text to display on the button.
                 */
                void setText(const std::string& text);

                /**
                 * @brief Setter for the colors.
                 * This function allows you to set the colors for different button states.
                 * @param normal The color when the button is in its normal state.
                 * @param hovered The color when the button is hovered over.
                 * @param pressed The color when the button is pressed.
                 */
                void setColors(Color normal, Color hovered, Color pressed);
                
                /**
                 * @brief Getter for the hover of the button.
                 * This function returns whether the button is currently hovered.
                 * @return true if the button is hovered, false otherwise.
                */
                bool getIsHovered() const;

                /**
                 * @brief Getter for the pressed state.
                 * This function returns whether the button is currently pressed.
                 * @return true if the button is pressed, false otherwise.
                 */
                bool getIsPressed() const;

                /**
                 * @brief Getter for the bounds.
                 * This function returns the rectangle defining the button's position and size.
                 * @return The bounds of the button.
                 */
                Rectangle getBounds() const;
        
            private:
                /** 
                 * @brief Check if the button is clicked and execute the action if it is.
                 * This function checks if the button is pressed and calls the action function if it is.
                */
                void isClicked();

                int _fontSize;
                bool _isHovered;
                bool _isPressed;
                std::string _text;
                function _actived;
        
                Color _textColor;
                Rectangle _bounds;
                Color _normalColor;
                Color _hoveredColor;
                Color _pressedColor;
        };
    }
}

#endif