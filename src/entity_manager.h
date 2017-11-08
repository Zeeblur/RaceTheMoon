#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "subsystem.h"
#include "entity.h"
#include "engine_state.h"

// entity manager just holds our entities in a lookup table.
// This is a simple system - you might want more.
class entity_manager : public subsystem
{
private:

    std::unordered_map<std::string, std::shared_ptr<entity>> _entities[5];

    entity_manager() = default;

public:

    int currentState;

    inline static std::shared_ptr<entity_manager>& get()
    {
        static std::shared_ptr<entity_manager> instance(new entity_manager());
        return instance;
    }

	std::shared_ptr<entity> get_entity(std::string name)
	{
		// Returns the entity of the given name
		for (auto &entLists : _entities)
			for (auto &e : entLists)
				if (e.first == name)
					return e.second;
	}

    std::shared_ptr<entity> create_entity(const std::string &name, int state, transform_data trans = transform_data())
    {
        auto e = std::make_shared<entity>(name, trans);
		e->state = state;
        _entities[state][name] = e;
        return e;
    }

    bool initialise() override final
    {
        std::cout << "Entity manager initialising" << std::endl;
        for (auto &entLists : _entities)
        {
            for (auto &e : entLists)
                if (!e.second->initialise())
                    return false;
        }
        return true;
    }

    bool load_content() override final
    {
        std::cout << "Entity manager loading content" << std::endl;
        for (auto &entLists : _entities)
        {
            for (auto &e : entLists)
                if (!e.second->load_content())
                    return false;
        }
        return true;
    }

    void update(float delta_time) override final
    {
        //std::cout << "Entity manager updating" << std::endl;
        for (auto &e : _entities[currentState])
            e.second->update(delta_time);
    }

    void render() override final
    {
        //std::cout << "Entity manager rendering" << std::endl;
        for (auto &e : _entities[currentState])
            e.second->render();
    }

    void unload_content() override final
    {
        std::cout << "Entity manager unloading content" << std::endl;
        for (auto &entLists : _entities)
        {
            for (auto &e : entLists)
                e.second->unload_content();
        }
    }

    void shutdown() override final
    {
        std::cout << "Entity manager shutting down" << std::endl;
        for (auto &entLists : _entities)
        {
            for (auto &e : entLists)
                e.second->shutdown();
        }
        // Clear the entity map

        for (auto &entMap : _entities)
        {
            entMap.clear();
        }

    }
};