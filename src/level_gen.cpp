//
// Created by beej on 24/11/17.
//

#include "level_gen.h"


void level_gen::addWaterfallPuzzle(glm::vec3 p)
{
    // Attempt at waterfall boxes puzzle
    //Left wall piece

    // Waterfall piece 1
    transform_data waterfall1Trans;
    waterfall1Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall1Trans.x = p.x+-230.0f;
    waterfall1Trans.y = p.y+60.0f;
    waterfall1Trans.z = p.z+0.0f;
    auto w1 = entity_manager::get()->create_entity("Waterfall1", state_type::GAME, waterfall1Trans);
    w1->add_component("physics", physics_system::get()->build_component(w1));
    w1->add_component("ai", ai_system::get()->build_component(w1, DOWNTHENUP, 20.0f, 60.0f));
    w1->add_component("render", renderer::get()->build_component(w1, glm::vec4(1.0f), "", "cube", "Gouraud", phong));
    w1->add_component("collider", physics_system::get()->build_collider_component(w1));

    // Waterfall piece 2
    transform_data waterfall2Trans;
    waterfall2Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall2Trans.x = p.x+-170.0f;
    waterfall2Trans.y = p.y+50.0f;
    waterfall2Trans.z = p.z+0.0f;
    auto w2 = entity_manager::get()->create_entity("Waterfall2", state_type::GAME, waterfall2Trans);
    w2->add_component("physics", physics_system::get()->build_component(w2));
    w2->add_component("ai", ai_system::get()->build_component(w2, UPTHENDOWN, 20.0f, 60.0f));
    w2->add_component("render", renderer::get()->build_component(w2, glm::vec4(1.0f), "", "cube", "Gouraud", phong));
    w2->add_component("collider", physics_system::get()->build_collider_component(w2));

    // Waterfall piece 3
    transform_data waterfall3Trans;
    waterfall3Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall3Trans.x = p.x+-110.0f;
    waterfall3Trans.y = p.y+40.0f;
    waterfall3Trans.z = p.z+0.0f;
    auto w3 = entity_manager::get()->create_entity("Waterfall3", state_type::GAME, waterfall3Trans);
    w3->add_component("physics", physics_system::get()->build_component(w3));
    w3->add_component("ai", ai_system::get()->build_component(w3, UPTHENDOWN, 20.0f, 60.0f));
    w3->add_component("render", renderer::get()->build_component(w3, glm::vec4(1.0f), "", "cube", "Gouraud", phong));
    w3->add_component("collider", physics_system::get()->build_collider_component(w3));

    // Waterfall piece 4
    transform_data waterfall4Trans;
    waterfall4Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall4Trans.x = p.x+-50.0f;
    waterfall4Trans.y = p.y+30.0f;
    waterfall4Trans.z = p.z+0.0f;
    auto w4 = entity_manager::get()->create_entity("Waterfall4", state_type::GAME, waterfall4Trans);
    w4->add_component("physics", physics_system::get()->build_component(w4));
    w4->add_component("ai", ai_system::get()->build_component(w4, UPTHENDOWN, 20.0f, 60.0f));
    w4->add_component("render", renderer::get()->build_component(w4, glm::vec4(1.0f), "", "cube", "Gouraud", phong));
    w4->add_component("collider", physics_system::get()->build_collider_component(w4));

    
    // Waterfall piece 5
    transform_data waterfall5Trans;
    waterfall5Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall5Trans.x = p.x + 10.0f;
    waterfall5Trans.y = p.y + 20.0f;
    waterfall5Trans.z = p.z + 0.0f;
    auto w5 = entity_manager::get()->create_entity("Waterfall1", state_type::GAME, waterfall5Trans);
    w5->add_component("physics", physics_system::get()->build_component(w5));
    w5->add_component("ai", ai_system::get()->build_component(w5, DOWNTHENUP, 20.0f, 60.0f));
    w5->add_component("render", renderer::get()->build_component(w5, glm::vec4(1.0f), "", "cube", "Gouraud", phong));
    w5->add_component("collider", physics_system::get()->build_collider_component(w5));

    // Waterfall piece 6
    transform_data waterfall6Trans;
    waterfall6Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall6Trans.x = p.x + 10.0f;
    waterfall6Trans.y = p.y + 20.0f;
    waterfall6Trans.z = p.z + 0.0f;
    auto w6 = entity_manager::get()->create_entity("Waterfall1", state_type::GAME, waterfall6Trans);
    w6->add_component("physics", physics_system::get()->build_component(w6));
    w6->add_component("ai", ai_system::get()->build_component(w6, DOWNTHENUP, 20.0f, 60.0f));
    w6->add_component("render", renderer::get()->build_component(w6, glm::vec4(1.0f), "", "cube", "Gouraud", phong));
    w6->add_component("collider", physics_system::get()->build_collider_component(w6));
}