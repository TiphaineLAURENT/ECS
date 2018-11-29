/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** ComponentManager
*/

#ifndef ECS_COMPONENTMANAGER_HPP
# define ECS_COMPONENTMANAGER_HPP

# include <ostream>
#include <bits/unordered_map.h>
#include "IComponentContainer.hpp"

namespace ecs
{

  class ComponentManager
  {

	  class ComponentContainer : public IComponentContainer
	  {
	    public:
		  ComponentContainer() = default;
		  virtual ~ComponentContainer() = default;
		  ComponentContainer(const ComponentContainer &) = delete;

	    public:
		  ComponentContainer &operator=(ComponentContainer &) = delete

	    public:
		  virtual const char *getComponentContainerTypeName() const override
		  {
			  static const char *COMPONENT_TYPE_NAME{typeid(T).name()};

			  return COMPONENT_TYPE_NAME;
		  }

		  virtual void destroyComponent(IComponent *object) override
		  {
			  delete object;
		  }

	  };

	  class ComponentManager
	  {
// ATTRIBUTES
	    private:
	    public:

// METHODS
	    public:// CONSTRUCTORS
		  ComponentManager();
		  ~ComponentManager() = default;
		  ComponentManager(const ComponentManager &copy) = default;
		  ComponentManager(ComponentManager &&) noexcept = default;

	    public: //OPERATORS
		  ComponentManager &operator=(const ComponentManager &other) = default;
		  ComponentManager &operator=(ComponentManager &&) = default;

	    public:
	    private:
	  };

	  std::ostream &operator<<(std::ostream &out, const ComponentManager &);

	  using ComponentContainerRegistry =
	  std::unordered_map<ComponentTypeId, IComponentContainer*>;
	  ComponentContainerRegistry _componentContainerRegistry;

	  ComponentManager(const ComponentManager&) = delete;

	  ComponentManager& operator=(ComponentManager&) = delete;

	  template <class T>
	  inline ComponentContainer<T> *getComponentContainer()
	  {
		  ComponentTypeId CID =T::STATIC_COMPONENT_TYPE_ID;

		  auto it = _componentContainerRegistry.find(CID);
		  ComponentContainer<T> *cc = nullptr;

		  if (it == _componentContainerRegistry.end()) {
			  cc = new ComponentContainer<T>();
			  _componentContainerRegistry[CID] = cc;
		  } else {
			  cc = static_cast<ComponentContainer<T>*>(it->second);
		  }

		  assert(cc != nullptr && "Failed to create "
		                          "ComponentContainer<T>*");
		  return cc;
	  }

	  using ComponentLookupTable = std::vector<IComponent*>;
	  ComponentLookupTable  _componentLUT;

	  using EntityComponentMap = std::vector<std::vector<ComponentId>>;
	  EntityComponentMap _entityComponentMap;

	  ComponentId acquireComponentId(IComponent *component);
	  void releaseComponentId(ComponentId id);

	  void mapEntityComponent(EntityId entityId, ComponentId componentId,
	                          ComponentTypeId componentTypeId);
	  void unmapEntityComponent(EntityId entityId, ComponentId componentId,
	                            ComponentTypeId componentTypeId);

    public:
  	template <class T>
        using TComponentIterator typename ComponentContainer<T>::iterator;

  	ComponentManager() = default;
  	~ComponentManager() = default;

	  template <class T, class ...ARGS>
	  T *addComponent(const EntityId entityId, ARGS&&... args)
	  {
		  static constexpr std::hash<ComponentId>
			  ENTITY_COMPONENT_ID_HASER{std::hash<ComponentId>()};
		  const ComponentTypeId CTID = T::STATIC_COMPONENT_TYPE_ID;

//		  getComponentContainer<T>()->createObject();
		  IComponent *component = new T(std::forward<ARGS>(args));
		  component->setComponentId(acquireComponentId(component));
		  component->setOwner(entityId);
		  component->setHashValue(ENTITY_COMPONENT_ID_HASER(entityId)
		                          ^ (ENTITY_COMPONENT_ID_HASER
		                          (component->getComponentId())
			                          << 1));

		  mapEntityComponent(entityId, component->getComponentId(), CTID);

		  return static_cast<T*>(component);
	  }

	  template <class T>
	  void removeComponent(const EntityId entityId)
	  {
		  const ComponentTypeId CTID = T::STATIC_COMPONENT_TYPE_ID;
		  const ComponentId componentId = _entityComponentMap[entityId
			  .index][CTID];

		  IComponent *component = _componentLUT[componentId];
		  assert(component != nullptr && "FATAL: Trying to remove a "
		                                 "component which is not used by this "
		                                 "entity!");

		  delete component;
		  unmapEntityComponent(entityId, component, CTID);
	  }

	  void removeAllComponents(const EntityId entityId)
	  {
	  	static const size_t NUM_COMPONENTS = _entityComponentMap[0]
		        .size();

	  	for (ComponentTypeId componentTypeId  = 0; componentTypeId <
	                                                   NUM_COMPONENTS; ++componentTypeId) {
		        const ComponentId componentId =
			                          _entityComponentMap[entityId
				                          .index][componentTypeId];
		        if (componentId == INVALID_COMPONENT_ID)
			        continue;

		        IComponent component = _componentLUT[componentId];
		        if (component == nullptr) {
			        auto it = _componentContainerRegistry.find
			        	(componentTypeId);
			        if (it != _componentContainerRegistry.end()) {
				        it->second->destroyComponent(component);
			        } else {
				        assert(false && "Trying to release a "
				                        "component that wasn't created by "
				                        "ComponentManager!");
			        }

			        unmapEntityComponent(entityId, componentId,
			                             componentTypeId);
		        }
	  	}
	  }

	  template <class T>
	  T *getComponent(const EntityId entityId)
	  {
		  const ComponentManager CTID = T::STATIC_COMPONENT_TYPE_ID;
		  const ComponentId componentId =
			                    _entityComponentMap[entityId.index][CTID];

		  if (componentId == INVALID_COMPONENT_ID)
			  return nullptr;

		  return static_cast<T*>(_componentLUT[componentId]);
	  }

	  template <class T>
	  inline TComponentIterator<T> begin()
	  {
		  return getComponentContainer<T>()->begin();
	  }

	  template <class T>
	  inline TComponentIterator<T> end()
	  {
		  return getComponentContainer<T>()->end();
	  }

  };

}

#endif /* !ECS_COMPONENTMANAGER_HPP */
