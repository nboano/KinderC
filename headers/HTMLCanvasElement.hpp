#pragma once
#include "../kinderc.hpp"

class HTMLCanvasElement : public HTMLElement {
    public:
    HTMLCanvasElement(HTMLElement e) : HTMLElement(e) {}

    /// @brief Initialises the canvas element before drawing.
    void Init();

    /// @brief Retrieves the current width of the canvas.
    Property<int> Width {
        [](void* elm) {
            return (int)((HTMLCanvasElement*)elm)->getProperty("width");
        }, this
    };

    /// @brief Retrieves the current height of the canvas.
    Property<int> Height {
        [](void* elm) {
            return (int)((HTMLCanvasElement*)elm)->getProperty("height");
        }, this
    };

    /// @brief Sets the current line color of the canvas.
    Property<const char*> LineColor {
        [](void* elm, const char* value) {
            ((HTMLCanvasElement*)elm)->setProperty("ctx.fillStyle", value);
        }, this
    };

    /// @brief Draws a rectangle in a given position.
    /// @param x The X coordinate.
    /// @param y The Y coordinate.
    /// @param sizeX The width of the rectangle.
    /// @param sizeY The height of the rectangle.
    /// @param color The CSS color of the rectangle (OPTIONAL).
    void DrawRectangle(double x, double y, double sizeX, double sizeY, const char* color = "#000");

    /// @brief Clears the canvas.
    /// @param color The canvas background color.
    void Clear(const char* color = "#FFF");
};

void HTMLCanvasElement::Init(){
    JavaScript::Eval("%s.querySelectorAll('%s')[%i].ctx=%s.querySelectorAll('%s')[%i].getContext('2d')", docname, query, cindex, docname, query, cindex);
}

void HTMLCanvasElement::DrawRectangle(double x, double y, double sizeX, double sizeY, const char* color) {
    LineColor = color;
    JavaScript::Eval("%s.querySelectorAll('%s')[%i].ctx.fillRect(%f,%f,%f,%f)", docname, query, cindex, x, y, sizeX, sizeY);
}

void HTMLCanvasElement::Clear(const char* color) {
    DrawRectangle(0, 0, (int)Width, (int)Height, color);
}