/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ECS
*/

#ifndef ECS_ECS_HPP
# define ECS_ECS_HPP

#include <ostream>

class ECS
{
// ATTRIBUTES
  private:
  public:

// METHODS
  public:// CONSTRUCTORS
	ECS();
	~ECS() = default;
	ECS(const ECS &copy) = default;
	ECS(ECS &&) noexcept = default;

  public: //OPERATORS
	ECS &operator=(const ECS &other) = default;
	ECS &operator=(ECS &&) = default;

  public:
  private:
};

std::ostream &operator<<(std::ostream &out, const ECS &);

#endif /* !ECS_ECS_HPP */
