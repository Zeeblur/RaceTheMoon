//
// Created by beej on 24/11/17.
//

#pragma once
#include <memory>
#include "state_machine.h"
#include <functional>

class level_gen : public subsystem
{
private:
    level_gen() = default;

	transform_data leftWall, rightWall;

	std::map<int, std::vector<std::weak_ptr<entity>>> puzzleBlocks;

	int blocksize = 400;
	int currentBlock = -400;

public:

    inline static std::shared_ptr<level_gen> get()
    {
        static std::shared_ptr<level_gen> instance = std::shared_ptr<level_gen>(new level_gen());
        return instance;
    }



    void static addWaterfallPuzzle(int blockIdx);
    void static addCrusher(int blockIdx);
	void static addSnakeBalls(int blockIdx);

    const std::vector<std::function<void(int blockIdx)>> level_gen_functions =
	{
		addWaterfallPuzzle,
		addCrusher,
		addSnakeBalls
	};

	bool initialise() override final;

	bool load_content() override final;

	void update(float delta_time) override final;

	void render() override final;

    void reset();

	void unload_content() override final;

	void shutdown() override final;
    
};