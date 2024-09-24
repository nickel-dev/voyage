// This struct doesn't contain pointers for serialization reasons.
// To save the game, you can just copy the entire struct into a binary file. 
global struct State {
    Entity entities[MAX_ENTITY_COUNT];
} state;

Entity*
new_entity() {
    for (u64 i = 0; i < MAX_ENTITY_COUNT; ++i) {
        Entity* e = &state.entities[i];
        if (!e->active) {
            e->active = true;
            return e;
        }
    }
    assert(false, "You ran out of entities, please increase the MAX_ENTITY_COUNT: %i", MAX_ENTITY_COUNT);
    return NULL;
}