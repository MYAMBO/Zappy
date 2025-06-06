/*
** EPITECH PROJECT, 2025
** My_Shogi
** File description:
** Button
*/

#include "Button.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


gui::ui::Button::Button(function actived)
    : _fontSize(20),  _isHovered(false), _isPressed(false), _text("Button"), _actived(actived), 
    _textColor(BLACK), _bounds({0, 0, 100, 50}), _normalColor(LIGHTGRAY), _hoveredColor(GRAY), _pressedColor(DARKGRAY)
{
}

gui::ui::Button::Button(function actived, Rectangle bounds, const std::string& text)
    : _fontSize(20), _isHovered(false), _isPressed(false), _text(text), _actived(actived),
      _textColor(BLACK), _bounds(bounds), _normalColor(LIGHTGRAY), _hoveredColor(GRAY), _pressedColor(DARKGRAY)
{
}

gui::ui::Button::~Button()
{
}


/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/


void gui::ui::Button::isClicked()
{
    if (_actived && _isPressed)
        _actived();
}

void gui::ui::Button::update()
{
    Vector2 mousePos = GetMousePosition();
    _isHovered = CheckCollisionPointRec(mousePos, _bounds);
    
    if (_isHovered) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _isPressed = true;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && _isPressed) {
            isClicked();
            _isPressed = false;
        }
    } else {
        _isPressed = false;
    }
    
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        _isPressed = false;
    }
}

void gui::ui::Button::draw()
{
    Color currentColor = _normalColor;
    
    if (_isPressed) {
        currentColor = _pressedColor;
    } else if (_isHovered) {
        currentColor = _hoveredColor;
    }
    DrawRectangleRec(_bounds, currentColor);
    DrawRectangleLinesEx(_bounds, 2, BLACK);
    if (!_text.empty()) {
        int textWidth = MeasureText(_text.c_str(), _fontSize);
        Vector2 textPos = {
            _bounds.x + (_bounds.width - textWidth) / 2,
            _bounds.y + (_bounds.height - _fontSize) / 2
        };
        DrawText(_text.c_str(), (int)textPos.x, (int)textPos.y, _fontSize, _textColor);
    }
}


/************************************************************
**                   >>>>   SETTERS   <<<<                 **
************************************************************/


void gui::ui::Button::setBounds(Rectangle bounds)
{
    _bounds = bounds;
}

void gui::ui::Button::setText(const std::string& text)
{
    _text = text;
}

void gui::ui::Button::setColors(Color normal, Color hovered, Color pressed)
{
    _normalColor = normal;
    _hoveredColor = hovered;
    _pressedColor = pressed;
}

void gui::ui::Button::setTextColor(Color color)
{
    _textColor = color;
}

void gui::ui::Button::setFontSize(int size)
{
    _fontSize = size;
}


/************************************************************
**                   >>>>   GETTERS   <<<<                 **
************************************************************/


Rectangle gui::ui::Button::getBounds() const
{
    return _bounds;
}

bool gui::ui::Button::getIsHovered() const
{
    return _isHovered;
}

bool gui::ui::Button::getIsPressed() const
{
    return _isPressed;
}