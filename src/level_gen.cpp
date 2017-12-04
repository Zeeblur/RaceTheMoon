//
// Created by beej on 24/11/17.
//

#include "level_gen.h"

// this is a function object to delete a pointer matching our criteria.
struct entity_deleter
{
	void operator()(entity*& e) // important to take pointer by reference!
	{
		delete e;
		e = NULL;
	}
};

bool level_gen::initialise()
{
	// intialise with 4 new blocks
	srand(time(NULL));

	for (int i = 400; i <= 1600; i += 400)
	{
		int rng = rand() % level_gen_functions.size();
		level_gen_functions[rng](-i);
	}

	
	return true;
}

bool level_gen::load_content() { return true; }

void level_gen::update(float delta_time)
{
	// remove block that has passed
	auto pos = entity_manager::get()->get_entity("Bat")->get_trans().z;

	if (pos < currentBlock)
	{
		std::cout << "passed block: " << currentBlock << std::endl;

		// remove all components from entities
		for (auto &e : puzzleBlocks[currentBlock])
		{
			entity_manager::get()->delete_entity(e._Get()->get_name());
		}

		// remove entities
		currentBlock -= blocksize;

		// add new block
		int rng = rand() % level_gen_functions.size();
		level_gen_functions[rng](currentBlock - 1200);
	}

}

void level_gen::render() {}
void level_gen::unload_content() {}
void level_gen::shutdown() {}

void level_gen::addWaterfallPuzzle(int blockIdx)
{
	auto levelGenInstance = level_gen::get();
	
    // Waterfall boxes puzzle
    //Left wall piece
    transform_data waterfallLeftWallTrans;
    waterfallLeftWallTrans.scale = glm::vec3(10.0f, 20.0f, 400.0f);
    waterfallLeftWallTrans.x = -260.0f;
    waterfallLeftWallTrans.y =  10.0f;
    waterfallLeftWallTrans.z = blockIdx + 200.0f;
    auto wL = entity_manager::get()->create_entity("WaterfallLeftWall" + std::to_string(blockIdx), state_type::GAME, waterfallLeftWallTrans);
    wL->add_component("physics", physics_system::get()->build_component(wL));
    wL->add_component("render", renderer::get()->build_component(wL, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    wL->add_component("collider", physics_system::get()->build_collider_component(wL));

	levelGenInstance->puzzleBlocks[blockIdx].push_back(wL);

    // Waterfall piece 1
    transform_data waterfall1Trans;
    waterfall1Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall1Trans.x = -230.0f;
    waterfall1Trans.y = 60.0f;
    waterfall1Trans.z = blockIdx+0.0f;
    auto w1 = entity_manager::get()->create_entity("Waterfall1" + std::to_string(blockIdx), state_type::GAME, waterfall1Trans);
    w1->add_component("physics", physics_system::get()->build_component(w1));
    w1->add_component("ai", ai_system::get()->build_component(w1, DOWNTHENUP,  20.0f,  60.0f));
    w1->add_component("render", renderer::get()->build_component(w1, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w1->add_component("collider", physics_system::get()->build_collider_component(w1));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w1));

    // Waterfall piece 2
    transform_data waterfall2Trans;
    waterfall2Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall2Trans.x = -170.0f;
    waterfall2Trans.y = 50.0f;
    waterfall2Trans.z = blockIdx+0.0f;
    auto w2 = entity_manager::get()->create_entity("Waterfall2" + std::to_string(blockIdx), state_type::GAME, waterfall2Trans);
    w2->add_component("physics", physics_system::get()->build_component(w2));
    w2->add_component("ai", ai_system::get()->build_component(w2, UPTHENDOWN,  20.0f,  60.0f));
    w2->add_component("render", renderer::get()->build_component(w2, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w2->add_component("collider", physics_system::get()->build_collider_component(w2));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w2));

    // Waterfall piece 3
    transform_data waterfall3Trans;
    waterfall3Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall3Trans.x = -110.0f;
    waterfall3Trans.y = 40.0f;
    waterfall3Trans.z = blockIdx+0.0f;
    auto w3 = entity_manager::get()->create_entity("Waterfall3" + std::to_string(blockIdx), state_type::GAME, waterfall3Trans);
    w3->add_component("physics", physics_system::get()->build_component(w3));
    w3->add_component("ai", ai_system::get()->build_component(w3, UPTHENDOWN,  20.0f,  60.0f));
    w3->add_component("render", renderer::get()->build_component(w3, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w3->add_component("collider", physics_system::get()->build_collider_component(w3));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w3));

    // Waterfall piece 4
    transform_data waterfall4Trans;
    waterfall4Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall4Trans.x = -50.0f;
    waterfall4Trans.y = 30.0f;
    waterfall4Trans.z = blockIdx+0.0f;
    auto w4 = entity_manager::get()->create_entity("Waterfall4" + std::to_string(blockIdx), state_type::GAME, waterfall4Trans);
    w4->add_component("physics", physics_system::get()->build_component(w4));
    w4->add_component("ai", ai_system::get()->build_component(w4, UPTHENDOWN,  20.0f,  60.0f));
    w4->add_component("render", renderer::get()->build_component(w4, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w4->add_component("collider", physics_system::get()->build_collider_component(w4));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w4));
    
    // Waterfall piece 5
    transform_data waterfall5Trans;
    waterfall5Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall5Trans.x =  10.0f;
    waterfall5Trans.y =  20.0f;
    waterfall5Trans.z = blockIdx + 0.0f;
    auto w5 = entity_manager::get()->create_entity("Waterfall5" + std::to_string(blockIdx), state_type::GAME, waterfall5Trans);
    w5->add_component("physics", physics_system::get()->build_component(w5));
    w5->add_component("ai", ai_system::get()->build_component(w5, UPTHENDOWN,  20.0f,  60.0f));
    w5->add_component("render", renderer::get()->build_component(w5, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w5->add_component("collider", physics_system::get()->build_collider_component(w5));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w5));

    // Waterfall piece 6
    transform_data waterfall6Trans;
    waterfall6Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall6Trans.x =  70.0f;
    waterfall6Trans.y =  30.0f;
    waterfall6Trans.z = blockIdx + 0.0f;
    auto w6 = entity_manager::get()->create_entity("Waterfall6" + std::to_string(blockIdx), state_type::GAME, waterfall6Trans);
    w6->add_component("physics", physics_system::get()->build_component(w6));
    w6->add_component("ai", ai_system::get()->build_component(w6, DOWNTHENUP,  20.0f,  60.0f));
    w6->add_component("render", renderer::get()->build_component(w6, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w6->add_component("collider", physics_system::get()->build_collider_component(w6));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w6));

    // Waterfall piece 7
    transform_data waterfall7Trans;
    waterfall7Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall7Trans.x =  130.0f;
    waterfall7Trans.y =  40.0f;
    waterfall7Trans.z = blockIdx + 0.0f;
    auto w7 = entity_manager::get()->create_entity("Waterfall7" + std::to_string(blockIdx), state_type::GAME, waterfall7Trans);
    w7->add_component("physics", physics_system::get()->build_component(w7));
    w7->add_component("ai", ai_system::get()->build_component(w7, DOWNTHENUP,  20.0f,  60.0f));
    w7->add_component("render", renderer::get()->build_component(w7, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w7->add_component("collider", physics_system::get()->build_collider_component(w7));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w7));

    // Waterfall piece 8
    transform_data waterfall8Trans;
    waterfall8Trans.scale = glm::vec3(40.0f, 40.0f, 40.0f);
    waterfall8Trans.x =  190.0f;
    waterfall8Trans.y =  50.0f;
    waterfall8Trans.z = blockIdx + 0.0f;
    auto w8 = entity_manager::get()->create_entity("Waterfall8" + std::to_string(blockIdx), state_type::GAME, waterfall8Trans);
    w8->add_component("physics", physics_system::get()->build_component(w8));
    w8->add_component("ai", ai_system::get()->build_component(w8, DOWNTHENUP,  20.0f,  60.0f));
    w8->add_component("render", renderer::get()->build_component(w8, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    w8->add_component("collider", physics_system::get()->build_collider_component(w8));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((w8));

    //Right wall piece
    transform_data waterfallRightWallTrans;
    waterfallRightWallTrans.scale = glm::vec3(10.0f, 20.0f, 400.0f);
    waterfallRightWallTrans.x =  250.0f;
    waterfallRightWallTrans.y =  10.0f;
    waterfallRightWallTrans.z = blockIdx + 200.0f;
    auto wR = entity_manager::get()->create_entity("WaterfallRightWall" + std::to_string(blockIdx), state_type::GAME, waterfallRightWallTrans);
    wR->add_component("physics", physics_system::get()->build_component(wR));
    wR->add_component("render", renderer::get()->build_component(wR, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    wR->add_component("collider", physics_system::get()->build_collider_component(wR));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((wR));
}

void level_gen::addCrusher(int blockIdx)
{
	auto levelGenInstance = level_gen::get();

    //Left wall piece
    transform_data crusherLeftWallTrans;
    crusherLeftWallTrans.scale = glm::vec3(10.0f, 20.0f, 400.0f);
    crusherLeftWallTrans.x =  -260.0f;
    crusherLeftWallTrans.y =  10.0f;
    crusherLeftWallTrans.z = blockIdx + 200.0f;
    auto cL = entity_manager::get()->create_entity("CrusherLeftWall" +std::to_string(blockIdx), state_type::GAME, crusherLeftWallTrans);
    cL->add_component("physics", physics_system::get()->build_component(cL));
    cL->add_component("render", renderer::get()->build_component(cL, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    cL->add_component("collider", physics_system::get()->build_collider_component(cL));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cL));

    // Adding crusher left 1
    transform_data crusherL1Ttrans;
    crusherL1Ttrans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
    crusherL1Ttrans.x =  -230.0f;
    crusherL1Ttrans.y =  5.0f;
    crusherL1Ttrans.z = blockIdx + 150.0f;
    auto cL1 = entity_manager::get()->create_entity("CrusherL1" + std::to_string(blockIdx), state_type::GAME, crusherL1Ttrans);
    cL1->add_component("physics", physics_system::get()->build_component(cL1));
    cL1->add_component("ai", ai_system::get()->build_component(cL1, RIGHTTHENLEFT,  -230.0f,  -210.0f));
    cL1->add_component("render", renderer::get()->build_component(cL1, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    cL1->add_component("collider", physics_system::get()->build_collider_component(cL1));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cL1));

    // Adding crusher right 1
    transform_data crusherR1Ttrans;
    crusherR1Ttrans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
    crusherR1Ttrans.x =  -170.0f;
    crusherR1Ttrans.y =  5.0f;
    crusherR1Ttrans.z = blockIdx + 150.0f;
    auto cR1 = entity_manager::get()->create_entity("CrusherR1" + std::to_string(blockIdx), state_type::GAME, crusherR1Ttrans);
    cR1->add_component("physics", physics_system::get()->build_component(cR1));
    cR1->add_component("ai", ai_system::get()->build_component(cR1, LEFTTHENRIGHT,  -190.0f,  -170.0f));
    cR1->add_component("render", renderer::get()->build_component(cR1, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    cR1->add_component("collider", physics_system::get()->build_collider_component(cR1));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cR1));

    // Adding crusher left 2
    transform_data crusherL2Ttrans;
    crusherL2Ttrans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
    crusherL2Ttrans.x =  130.0f;
    crusherL2Ttrans.y =  5.0f;
    crusherL2Ttrans.z = blockIdx + 0.0f;
    auto cL2 = entity_manager::get()->create_entity("CrusherL2" + std::to_string(blockIdx), state_type::GAME, crusherL2Ttrans);
    cL2->add_component("physics", physics_system::get()->build_component(cL2));
    cL2->add_component("ai", ai_system::get()->build_component(cL2, RIGHTTHENLEFT,  130.0f,  150.0f));
    cL2->add_component("render", renderer::get()->build_component(cL2, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    cL2->add_component("collider", physics_system::get()->build_collider_component(cL2));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cL2));

    // Adding crusher right 2
    transform_data crusherR2Ttrans;
    crusherR2Ttrans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
    crusherR2Ttrans.x =  190.0f;
    crusherR2Ttrans.y =  5.0f;
    crusherR2Ttrans.z = blockIdx + 0.0f;
    auto cR2 = entity_manager::get()->create_entity("CrusherR2" + std::to_string(blockIdx), state_type::GAME, crusherR2Ttrans);
    cR2->add_component("physics", physics_system::get()->build_component(cR2));
    cR2->add_component("ai", ai_system::get()->build_component(cR2, LEFTTHENRIGHT,  170.0f,  190.0f));
    cR2->add_component("render", renderer::get()->build_component(cR2, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    cR2->add_component("collider", physics_system::get()->build_collider_component(cR2));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cR2));

	// Adding crusher left 3
	transform_data crusherL3Trans;
	crusherL3Trans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
	crusherL3Trans.x =  0.0f;
	crusherL3Trans.y =  5.0f;
	crusherL3Trans.z = blockIdx + 150.0f;
	auto cL3 = entity_manager::get()->create_entity("CrusherL3" + std::to_string(blockIdx), state_type::GAME, crusherL3Trans);
	cL3->add_component("physics", physics_system::get()->build_component(cL3));
	cL3->add_component("ai", ai_system::get()->build_component(cL3, RIGHTTHENLEFT,  0.0f,  20.0f));
	cL3->add_component("render", renderer::get()->build_component(cL3, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
	cL3->add_component("collider", physics_system::get()->build_collider_component(cL3));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cL3));

	// Adding crusher right 3
	transform_data crushR3;
	crushR3.scale = glm::vec3(10.0f, 20.0f, 60.0f);
	crushR3.x =  60.0f;
	crushR3.y =  5.0f;
	crushR3.z = blockIdx + 150.0f;
	auto cR3 = entity_manager::get()->create_entity("CrusherR3" + std::to_string(blockIdx), state_type::GAME, crushR3);
	cR3->add_component("physics", physics_system::get()->build_component(cR3));
	cR3->add_component("ai", ai_system::get()->build_component(cR3, LEFTTHENRIGHT,  40.0f,  60.0f));
	cR3->add_component("render", renderer::get()->build_component(cR3, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
	cR3->add_component("collider", physics_system::get()->build_collider_component(cR3));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cR3));

	// Adding crusher left 4
	transform_data crusherL4Trans;
	crusherL4Trans.scale = glm::vec3(10.0f, 20.0f, 60.0f);
	crusherL4Trans.x =  -60.0f;
	crusherL4Trans.y =  5.0f;
	crusherL4Trans.z = blockIdx + 250.0f;
	auto cL4 = entity_manager::get()->create_entity("CrusherL4" + std::to_string(blockIdx), state_type::GAME, crusherL4Trans);
	cL4->add_component("physics", physics_system::get()->build_component(cL4));
	cL4->add_component("ai", ai_system::get()->build_component(cL4, RIGHTTHENLEFT,  -60.0f,  -40.0f));
	cL4->add_component("render", renderer::get()->build_component(cL4, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
	cL4->add_component("collider", physics_system::get()->build_collider_component(cL4));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cL4));

	// Adding crusher right 4
	transform_data crushR4;
	crushR4.scale = glm::vec3(10.0f, 20.0f, 60.0f);
	crushR4.x =  0.0f;
	crushR4.y =  5.0f;
	crushR4.z = blockIdx + 250.0f;
	auto cR4 = entity_manager::get()->create_entity("CrusherR4" + std::to_string(blockIdx), state_type::GAME, crushR4);
	cR4->add_component("physics", physics_system::get()->build_component(cR4));
	cR4->add_component("ai", ai_system::get()->build_component(cR4, LEFTTHENRIGHT,  -20.0f,  0.0f));
	cR4->add_component("render", renderer::get()->build_component(cR4, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
	cR4->add_component("collider", physics_system::get()->build_collider_component(cR4));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cR4));

    //Right wall piece
    transform_data crusherRightWallTrans;
    crusherRightWallTrans.scale = glm::vec3(10.0f, 20.0f, 400.0f);
    crusherRightWallTrans.x =  250.0f;
    crusherRightWallTrans.y =  10.0f;
    crusherRightWallTrans.z = blockIdx + 200.0f;
    auto cR = entity_manager::get()->create_entity("CrusherRightWall" + std::to_string(blockIdx), state_type::GAME, crusherRightWallTrans);
    cR->add_component("physics", physics_system::get()->build_component(cR));
    cR->add_component("render", renderer::get()->build_component(cR, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
    cR->add_component("collider", physics_system::get()->build_collider_component(cR));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((cR));
}

void level_gen::addSnakeBalls(int blockIdx)
{
	auto levelGenInstance = level_gen::get();

	//Left wall piece
	transform_data snakeLeftWall;
	snakeLeftWall.scale = glm::vec3(10.0f, 20.0f, 400.0f);
	snakeLeftWall.x =  -260.0f;
	snakeLeftWall.y =  10.0f;
	snakeLeftWall.z = blockIdx + 200.0f;
	auto sL = entity_manager::get()->create_entity("SnakeLeftWall" + std::to_string(blockIdx), state_type::GAME, snakeLeftWall);
	sL->add_component("physics", physics_system::get()->build_component(sL));
	sL->add_component("render", renderer::get()->build_component(sL, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
	sL->add_component("collider", physics_system::get()->build_collider_component(sL));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sL));

	// Ball 1
	transform_data snakeBall1;
	snakeBall1.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall1.x =  -230.0f;
	snakeBall1.y =  10.0f;
	snakeBall1.z = blockIdx + 200.0f;
	auto sB1 = entity_manager::get()->create_entity("SnakeBall1" + std::to_string(blockIdx), state_type::GAME, snakeBall1);
	sB1->add_component("physics", physics_system::get()->build_component(sB1));
	sB1->add_component("ai", ai_system::get()->build_component(sB1, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB1->add_component("render", renderer::get()->build_component(sB1, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB1->add_component("collider", physics_system::get()->build_collider_component(sB1));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB1));

	//Ball 2
	transform_data snakeBall2;
	snakeBall2.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall2.x =  -190.0f;
	snakeBall2.y =  10.0f;
	snakeBall2.z = blockIdx + 150.0f;
	auto sB2 = entity_manager::get()->create_entity("SnakeBall2" + std::to_string(blockIdx), state_type::GAME, snakeBall2);
	sB2->add_component("physics", physics_system::get()->build_component(sB2));
	sB2->add_component("ai", ai_system::get()->build_component(sB2, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB2->add_component("render", renderer::get()->build_component(sB2, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB2->add_component("collider", physics_system::get()->build_collider_component(sB2));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB2));

	//Ball 3
	transform_data snakeBall3;
	snakeBall3.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall3.x =  -150.0f;
	snakeBall3.y =  10.0f;
	snakeBall3.z = blockIdx + 100.0f;
	auto sB3 = entity_manager::get()->create_entity("SnakeBall3" + std::to_string(blockIdx), state_type::GAME, snakeBall3);
	sB3->add_component("physics", physics_system::get()->build_component(sB3));
	sB3->add_component("ai", ai_system::get()->build_component(sB3, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB3->add_component("render", renderer::get()->build_component(sB3, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB3->add_component("collider", physics_system::get()->build_collider_component(sB3));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB3));

	//Ball 4
	transform_data snakeBall4;
	snakeBall4.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall4.x =  -110.0f;
	snakeBall4.y =  10.0f;
	snakeBall4.z = blockIdx + 50.0f;
	auto sB4 = entity_manager::get()->create_entity("SnakeBall4" + std::to_string(blockIdx), state_type::GAME, snakeBall4);
	sB4->add_component("physics", physics_system::get()->build_component(sB4));
	sB4->add_component("ai", ai_system::get()->build_component(sB4, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB4->add_component("render", renderer::get()->build_component(sB4, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB4->add_component("collider", physics_system::get()->build_collider_component(sB4));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB4));

	//Ball 5
	transform_data snakeBall5;
	snakeBall5.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall5.x =  -70.0f;
	snakeBall5.y =  10.0f;
	snakeBall5.z = blockIdx + 0.0f;
	auto sB5 = entity_manager::get()->create_entity("SnakeBall5" + std::to_string(blockIdx), state_type::GAME, snakeBall5);
	sB5->add_component("physics", physics_system::get()->build_component(sB5));
	sB5->add_component("light", renderer::get()->build_light(sB5));
	sB5->add_component("ai", ai_system::get()->build_component(sB5, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB5->add_component("render", renderer::get()->build_component(sB5, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB5->add_component("collider", physics_system::get()->build_collider_component(sB5));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB5));

	//Ball 6
	transform_data snakeBall6;
	snakeBall6.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall6.x =  -30.0f;
	snakeBall6.y =  10.0f;
	snakeBall6.z = blockIdx + -50.0f;
	auto sB6 = entity_manager::get()->create_entity("SnakeBall6" + std::to_string(blockIdx), state_type::GAME, snakeBall6);
	sB6->add_component("physics", physics_system::get()->build_component(sB6));
	sB6->add_component("light", renderer::get()->build_light(sB6));
	sB6->add_component("ai", ai_system::get()->build_component(sB6, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB6->add_component("render", renderer::get()->build_component(sB6, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB6->add_component("collider", physics_system::get()->build_collider_component(sB6));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB6));

	//Ball 7
	transform_data snakeBall7;
	snakeBall7.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall7.x =  10.0f;
	snakeBall7.y =  10.0f;
	snakeBall7.z = blockIdx + -100.0f;
	auto sB7 = entity_manager::get()->create_entity("SnakeBall7" + std::to_string(blockIdx), state_type::GAME, snakeBall7);
	sB7->add_component("physics", physics_system::get()->build_component(sB7));
	sB7->add_component("light", renderer::get()->build_light(sB7));
	sB7->add_component("ai", ai_system::get()->build_component(sB7, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB7->add_component("render", renderer::get()->build_component(sB7, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB7->add_component("collider", physics_system::get()->build_collider_component(sB7));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB7));

	//Ball 8
	transform_data snakeBall8;
	snakeBall8.scale = glm::vec3(10.0f, 10.0f, 10.0f);
	snakeBall8.x =  40.0f;
	snakeBall8.y =  10.0f;
	snakeBall8.z = blockIdx + -150.0f;
	auto sB8 = entity_manager::get()->create_entity("SnakeBall8" + std::to_string(blockIdx), state_type::GAME, snakeBall8);
	sB8->add_component("physics", physics_system::get()->build_component(sB8));
	sB8->add_component("light", renderer::get()->build_light(sB8));
	sB8->add_component("ai", ai_system::get()->build_component(sB8, RIGHTTHENLEFT,  -220.0f,  220.0f));
	sB8->add_component("render", renderer::get()->build_component(sB8, glm::vec4(1.0f), "res/textures/concrete.jpg", "sphere", "Gouraud", phong));
	sB8->add_component("collider", physics_system::get()->build_collider_component(sB8));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sB8));

	//Right wall piece
	transform_data snakeRightWall;
	snakeRightWall.scale = glm::vec3(10.0f, 20.0f, 400.0f);
	snakeRightWall.x =  250.0f;
	snakeRightWall.y =  10.0f;
	snakeRightWall.z = blockIdx + 200.0f;
	auto sR = entity_manager::get()->create_entity("SnakeRightWall" + std::to_string(blockIdx), state_type::GAME, snakeRightWall);
	sR->add_component("physics", physics_system::get()->build_component(sR));
	sR->add_component("render", renderer::get()->build_component(sR, glm::vec4(1.0f), "res/textures/concrete.jpg", "cube", "Gouraud", phong));
	sR->add_component("collider", physics_system::get()->build_collider_component(sR));

	levelGenInstance->puzzleBlocks[blockIdx].push_back((sR));
}




