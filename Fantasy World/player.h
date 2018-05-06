#pragma once
class player
{
public:
	player(const char* name, int hp);
	virtual ~player();

	const char* get_name() const;
	void attacked(int damage);

private:
	const char* name_ = nullptr;
	int hp_ = 0;
	bool is_dead_ = false;
};

