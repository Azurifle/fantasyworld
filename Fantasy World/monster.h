#ifndef MONSTER
#define MONSTER
#pragma once
class monster
{
public:
	explicit monster(player player_to_attack);
	virtual ~monster() = default;

	void update() const;

private:
	player player_to_attack_;
	string name_;
	int damage_;
};

#endif //MONSTER
