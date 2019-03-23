#pragma once

#include <functional>
#include <SFML/System.hpp>

#include "whatever.hpp"

namespace blah
{

template <typename T>
T squareMagnitude(const sf::Vector2<T> &v)
{
	return (
		pow<T>(v.x, 2) +
		pow<T>(v.y, 2));
}

template <typename T>
T magnitude(const sf::Vector2<T> &v)
{
    return sqrt(squareMagnitude(v));
}

template <typename T>
sf::Vector2<T> normalized(sf::Vector2<T> v)
{
    T mag = magnitude<T>(v);
    return sf::Vector2<T>(
        static_cast<T>(v.x / mag),
        static_cast<T>(v.y / mag));
}

template <typename T>
sf::Vector2<T> randomVector2()
{
	return sf::Vector2<T>(randomNumber<T>(static_cast<T>(0), static_cast<T>(SCREEN_WIDTH)),
		randomNumber<T>(static_cast<T>(0), static_cast<T>(SCREEN_HEIGHT)));
}

template <typename T>
sf::Vector2<T> randomVector2(T start, T end)
{
    auto blah{std::bind(randomNumber<T>, start, end)};
    return sf::Vector2<T>(blah(), blah());
}

} // namespace blah

template <typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector3<T> &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}