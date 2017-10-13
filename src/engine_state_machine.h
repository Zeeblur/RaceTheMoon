#include <unordered_map>
#include "component.h"
#include "engine.h"
#include "subsystem.h"
#include "engine_state.h"


class engine_state_machine : public subsystem
{

public:
    static std::shared_ptr<engine_state_machine> get();


    void add_state(const std::string &name, std::shared_ptr<engine_state> state, state_type type);

    void change_state(const std::string &name);

    std::string get_current_state();

    state_type get_current_state_type();

    bool initialise() override final;

    bool load_content() override final;

    void update(float delta_time) override final;

    void render() override final;

    void unload_content() override final;

    void shutdown() override final;

private:
    // Used to keep track based on name
    std::unordered_map<std::string, std::shared_ptr<engine_state>> _states;

    std::string _current_state_name = "";

    state_type _current_state_type;

    std::shared_ptr<engine_state> _current_state = nullptr;

    engine_state_machine();

};