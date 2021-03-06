#include "booster.hpp"

void booster::add_to_world(b2World * world)
{
    const settings& config = settings::get_instance();

    b2BodyDef bdef;
    bdef.type = b2_staticBody;
    bdef.position.Set(this->x, this->y);

    body = world->CreateBody(&bdef);

    b2CircleShape bshape;
    bshape.m_p.Set(0.0f, 0.0f);
    bshape.m_radius = config.BOOSTER_RADIUS;

    b2FixtureDef fdef;
    fdef.shape = &bshape;
    fdef.isSensor = true;
    body->CreateFixture(&fdef);
    col_data = std::shared_ptr<collision_user_data>(new collision_user_data(this));
    body->SetUserData(static_cast<void*>(col_data.get()));

    is_alive = true;
}

void booster::step_on(ball* m)
{
    if(! is_alive) {
        return;
    }
    std::cout << "booster stepped on" << std::endl;

    const settings& config = settings::get_instance();
    respawn_counter = config.BOOSTER_RESPAWN_TIME;

    switch(type) {
        case booster_type::all:  m->get_boosted(); break;
        case booster_type::red:  
        case booster_type::blue:
           if(same_color(type, m->type)) m->get_boosted();
           else return; // prevents is_alive from being switched
           break;
    }

    is_alive = false;
}

void to_json(nlohmann::json& j, const booster& p)
{
    j = nlohmann::json{{"x", p.x}, {"y", p.y}, {"type", to_string(p.type)}};
}

void from_json(const nlohmann::json& j, booster& p)
{
    p.x      = j.at("x").get<float>();
    p.y      = j.at("y").get<float>();
    p.type   = booster_type_from_string(j.at("type").get<std::string>());
}
