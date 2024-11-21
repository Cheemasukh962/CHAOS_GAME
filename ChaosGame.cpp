// Project made by Tredis, and Sukhman!
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object for the window dimensions
    VideoMode vm(1920, 1080); // Resolution: 1920x1080
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    // Load the font for displaying text
    Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Error loading font!" << endl;
        return -1; // Exit if font fails to load
    }

    // Set up the "cover" instructions to guide the user
    Text cover;
    cover.setFont(font);
    cover.setString("Choose a Shape: \nClick Triangle or Pentagon"); // Initial instructions
    cover.setCharacterSize(72); // Font size 
    cover.setFillColor(Color::Red); // Text color
    cover.setStyle(Text::Bold); // Bold 
    cover.setPosition(200, 200);

    // Set up "Triangle" button
    Text triangleButton;
    triangleButton.setFont(font);
    triangleButton.setString("Triangle");
    triangleButton.setCharacterSize(48);
    triangleButton.setFillColor(Color::Green);
    triangleButton.setPosition(600, 400);

    // Set up "Pentagon" button
    Text pentagonButton;
    pentagonButton.setFont(font);
    pentagonButton.setString("Pentagon");
    pentagonButton.setCharacterSize(48);
    pentagonButton.setFillColor(Color::Blue);
    pentagonButton.setPosition(600, 500);

    // Vectors to store vertices and points
    vector<Vector2f> vertices; // Stores the shape's vertices
    vector<Vector2f> points;   // Stores points used to generate the fractal
    Vector2f click;            // Temporarily stores user clicks

    int sides = 0; // Tracks the number of sides for the chosen shape
    bool shapeSelected = false; // Flag to indicate if a shape has been selected

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !shapeSelected) {
                    // Check if the "Triangle" button is clicked
                    if (triangleButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        sides = 3; // Set the shape to triangle
                        shapeSelected = true;
                        vertices.clear(); // Clear previous vertices
                        points.clear();   // Clear previous fractal points
                        cover.setString("Click 3 points for the triangle, then 1 more to start!");
                    }
                    // Check if the "Pentagon" button is clicked
                    else if (pentagonButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        sides = 5; // Set the shape to pentagon
                        shapeSelected = true;
                        vertices.clear();
                        points.clear();
                        cover.setString("Click 5 points for the pentagon, then 1 more to start!");
                    }
                }
                else if (shapeSelected) {
                    // Allow the user to define vertices for the shape
                    click = Vector2f(event.mouseButton.x, event.mouseButton.y);

                    if (vertices.size() < sides) {
                        vertices.push_back(click); // Add the vertex to the list
                        cout << "Vertex added at: (" << click.x << ", " << click.y << ")" << endl;

                        if (vertices.size() == sides) {
                            cover.setString("Click inside to start the fractal!"); // Update instructions
                        }
                    }
                    else if (points.empty()) {
                        points.push_back(click); // Initial point to begin fractal generation
                        cover.setString("Generating the fractal...");
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close(); // Close the application if the user presses the Escape key
        }

        if (!points.empty()) {
            // Generate fractal points 
            int randomIndex = rand() % vertices.size(); // Randomly pick one of the vertices
            Vector2f randomVertex = vertices[randomIndex];
            Vector2f lastPoint = points.back(); // The last generated point

            // Set the k value based on the shape
            float k;
            if (sides == 5) {
                k = 0.618f; // Golden ratio's reciprocal for pentagon
            }
            else {
                k = 0.5f; // Midpoint for triangle
            }

            // Calculate the new fractal point
            Vector2f newPoint(
                (1 - k) * lastPoint.x + k * randomVertex.x,
                (1 - k) * lastPoint.y + k * randomVertex.y
            );
            points.push_back(newPoint); // Add the new point to the fractal
        }

        // Draw everything
        window.clear(); // Clear the screen before drawing


        window.draw(cover);          // Draw  (instructions)
        if (!points.size() && !shapeSelected) {
            window.draw(triangleButton); // Draw the triangle button
            window.draw(pentagonButton); // Draw the pentagon button
        }
        // Draw the vertices for the chosen shape
        for (int i = 0; i < vertices.size(); i++) {
            RectangleShape rect(Vector2f(10, 10)); // Small square to represent vertices
            rect.setPosition(vertices[i].x, vertices[i].y);
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }

        // Draw the fractal points
        for (int i = 0; i < points.size(); i++) {
            RectangleShape rect(Vector2f(2, 2)); // Small square to represent points
            rect.setPosition(points[i]);
            rect.setFillColor(Color::Red);
            window.draw(rect);
        }

        window.display(); // Display all the drawn elements
    }

    return 0;
}
