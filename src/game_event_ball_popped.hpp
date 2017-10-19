#ifndef ML_GAME_EVENT_BALL_POPPED_HPP
#define ML_GAME_EVENT_BALL_POPPED_HPP

struct game_event_ball_popped
{
    game_event_ball_respawn(
        const std::size_t id,
        const b2Vec2 pos
    );
};

#endif

