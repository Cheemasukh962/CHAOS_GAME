#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Error loading font!" << endl;
        return -1;
    }

    // Set up instructions
    Text instructions;
    instructions.setFont(font);
    instructions.setString("Click 3 points for the triangle, then 1 more to start! or Hit S for Square");
    instructions.setCharacterSize(24);
    instructions.setFillColor(Color::White);
    instructions.setPosition(20, 20);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    Vector2f click;

    int sides = 3; // Default to triangle (3 sides)

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    click = Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if (vertices.size() < sides)
                    {
                        vertices.push_back(click);
                        cout << "Vertex added at: (" << click.x << ", " << click.y << ")" << endl;

                        if (vertices.size() == sides)
                        {
                            instructions.setString("Click inside to start the fractal!");
                        }
                    }
                    else if (points.empty())
                    {
                        points.push_back(click);
                        instructions.setString("Generating the fractal...");
                    }
                }
            }

            // Handle shape switching
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::T) // Switch to triangle
                {
                    sides = 3;
                    vertices.clear();
                    points.clear();
                    instructions.setString("Click 3 points for the triangle, then 1 more to start!");
                }
                else if (event.key.code == Keyboard::S) // Switch to square
                {
                    sides = 4;
                    vertices.clear();
                    points.clear();
                    instructions.setString("Click 4 points for the square, then 1 more to start!");
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (!points.empty())
        {
            // Generate fractal points
            int randomIndex = rand() % vertices.size();
            Vector2f randomVertex = vertices[randomIndex];
            Vector2f lastPoint = points.back();
            Vector2f midpoint((randomVertex.x + lastPoint.x) / 2, (randomVertex.y + lastPoint.y) / 2);
            points.push_back(midpoint);
        }

        // Draw everything
        window.clear();

        for (int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10, 10));
            rect.setPosition(vertices[i].x , vertices[i].y);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(2, 2));
            rect.setPosition(points[i]);
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        window.draw(instructions);
        window.display();
    }

    return 0;
}
