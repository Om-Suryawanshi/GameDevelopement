#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"

// Config Handleing
#include <fstream>
#include <iostream>
#include <iomanip> // for std::quoted

// User Defined Headers
#include "shapes.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define CONFIG "config.txt"


void renderShapes(sf::RenderWindow& window, const std::vector<shape>& shapes, const sf::Font& font)
{
    
    for (const auto& s : shapes) 
    {
        sf::Text label;
        label.setFont(font);
		label.setString(s.s_text);
		label.setCharacterSize(14);
		label.setFillColor(sf::Color::White);
        label.setPosition(s.s_position.x, s.s_position.y - 20);
		window.draw(label);

        if(s.s_type == "circle")
        {
            sf::CircleShape circle(s.size);
			circle.setPosition(s.s_position.x, s.s_position.y);
            circle.setFillColor(sf::Color(
                static_cast<int>(s.s_color.r * 255),
                static_cast<int>(s.s_color.g * 255),
                static_cast<int>(s.s_color.b * 255)
            ));
            window.draw(circle);
        }
        else if(s.s_type == "square")
        {
			sf::RectangleShape square(sf::Vector2f(s.size, s.size));
			square.setPosition(s.s_position.x, s.s_position.y);
            square.setFillColor(sf::Color(
                static_cast<int>(s.s_color.r * 255),
                static_cast<int>(s.s_color.g * 255),
                static_cast<int>(s.s_color.b * 255)
            ));
			window.draw(square);
        }
        else if (s.s_type == "triangle")
        {
            sf::ConvexShape triangle;
            triangle.setPointCount(3);
			float x = s.s_position.x;
            float y = s.s_position.y;
            float size = static_cast<float>(s.size);
			triangle.setPoint(0, sf::Vector2f(x + size / 2.0f, y)); // 2.0 centers the top dot of the triangle
			triangle.setPoint(1, sf::Vector2f(x, y + size));
			triangle.setPoint(2, sf::Vector2f(x + size, y + size));
            triangle.setFillColor(sf::Color(
                static_cast<int>(s.s_color.r * 255),
                static_cast<int>(s.s_color.g * 255),
                static_cast<int>(s.s_color.b * 255)
			));
            window.draw(triangle);
        }
        else if (s.s_type == "ellipse")
        {
            sf::CircleShape ellipse(s.size);
            ellipse.setScale(1.5f, 1.0f);  // Wider than tall
            ellipse.setPosition(s.s_position.x, s.s_position.y);
            ellipse.setFillColor(sf::Color(
                static_cast<int>(s.s_color.r * 255),
                static_cast<int>(s.s_color.g * 255),
                static_cast<int>(s.s_color.b * 255)
            ));
            window.draw(ellipse);
        }
    }
}

void writeConfig(const std::string& filename, const std::vector<shape>& shapes)
{
	std::ofstream file(filename);
	if (!file.is_open()) return;
    for (const auto& s : shapes)
    {
        file << s.s_type << " "
             << s.s_color.r << " "
             << s.s_color.g << " "
             << s.s_color.b << " "
             << std::quoted(s.s_text) << " "
             << s.s_position.x << " "
             << s.s_position.y << " "
             << s.size << " "
			 << s.s_velocity.x << " "
			 << s.s_velocity.y << "\n";
	}
}

void readConfig(const std::string& filename, std::vector<shape>& shapes)
{
	std::ifstream file(filename);
    std::string temp;

    if(!file.is_open())
    {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
	}
	std::string type, text;
    float r, g, b, x, y, velx, vely;
    int size;

    while (file >> type >> r >> g >> b >> std::quoted(text) >> x >> y >> size >> velx >> vely)
    {
		color col(r, g, b);
        position pos(x, y);
        velocity vel(velx, vely);
		shape s(type, col, text, pos, size, vel);
		shapes.push_back(s);
    }
}

void updatePositions(std::vector<shape>& shapes)
{
    for (auto& s : shapes)
    {
		s.s_position.x += s.s_velocity.x;
        s.s_position.y += s.s_velocity.y;

        if (s.s_type == "circle")
        {
            if (s.s_position.x < 0 || s.s_position.x + s.size > WINDOW_HEIGHT - s.size)
                s.s_velocity.x *= -1;
        }
        else if (s.s_type == "ellipse")
        {
			if (s.s_position.x < 0 || s.s_position.x + s.size > WINDOW_HEIGHT - s.size * 2.0f) // The size is scaled for ellipse
				s.s_velocity.x *= -1;
        }
        else
        {
            // Bounce off the walls
            if (s.s_position.x < 0 || s.s_position.x + s.size > WINDOW_WIDTH)
                s.s_velocity.x *= -1;
        }

        // Bounce vertically
        if (s.s_type == "circle" || s.s_type == "ellipse") // the x is same ellipse not scaled 
        {
            if(s.s_position.y < 0 || s.s_position.y + s.size > WINDOW_HEIGHT - s.size)
				s.s_velocity.y *= -1;
        }
        else //rectangle
        {
            if (s.s_position.y < 0 || s.s_position.y + s.size > WINDOW_HEIGHT)
                s.s_velocity.y *= -1;
        }        
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Bounceing Shapes");
    ImGui::SFML::Init(window);

	window.setFramerateLimit(240);
	window.setVerticalSyncEnabled(true);

    std::vector<shape> shapes;
    int selectedShapeIndex = 0;

	readConfig(CONFIG, shapes);

    sf::Font font;

    int const minShapeSize = 10;
    int const maxShapeSize = 50;
    float const minVelocity = -10;
    float const maxVelocity = 10;

    if (!font.loadFromFile("MOELA.ttf"))
    {
        std::cerr << "Could not load Font! " << std::endl;
		return -1;
    }
    
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Config");
        ImGui::Text("Shapes Config!");
        if (ImGui::BeginCombo("Select Shape", shapes[selectedShapeIndex].s_text.c_str()))
        {
            for (int i = 0; i < shapes.size(); ++i) 
            {
                bool isSelected = (i == selectedShapeIndex);
                if (ImGui::Selectable(shapes[i].s_text.c_str(), isSelected))
                {
                    selectedShapeIndex = i;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        shape& selectedShape = shapes[selectedShapeIndex];
        ImGui::ColorEdit3("Color", &selectedShape.s_color.r);
        ImGui::SliderInt("Size", &selectedShape.size, minShapeSize, maxShapeSize);
        ImGui::SliderFloat2("Velocity", &selectedShape.s_velocity.x, minVelocity, maxVelocity);
        ImGui::SliderFloat2("Position", &selectedShape.s_position.x, 0.0f, 750.0f);
        char buff[128];
        strncpy_s(buff, sizeof(buff), selectedShape.s_text.c_str(), sizeof(buff));
        if (ImGui::InputText("Label", buff, sizeof(buff))) 
        {
            selectedShape.s_text = buff;
        }

		//No need to save the shape it gets saved in the updatePositions function

        ImGui::End();

        window.clear(sf::Color::Black);
		renderShapes(window, shapes, font);
		updatePositions(shapes);
        ImGui::SFML::Render(window);
        window.display();
    }


	// Write the final updated position or config to file instead to writing it every frame
    writeConfig(CONFIG, shapes);
    ImGui::SFML::Shutdown();
    return 0;
}