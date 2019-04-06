//
// Created by tiphaine on 06/04/19.
//

#ifndef ECS_SYSTEMMANAGER_HPP
# define ECS_SYSTEMMANAGER_HPP

# include <ostream>



class SystemManager {
// ATTRIBUTES
private:
public:

// METHODS:
public: // CONSTRUCTORS
    SystemManager();
    ~SystemManager() = default;
    SystemManager(const SystemManager &copy) = default;
    SystemManager(SystemManager &&other) noexcept = default;
    
public: // OPERATORS
    SystemManager &operator=(const SystemManager &other) = default;
    SystemManager &operator=(SystemManager &&other) = default;
};

std::ostream &operator<<(std::ostream &out, const SystemManager &);



#endif //ECS_SYSTEMMANAGER_HPP
