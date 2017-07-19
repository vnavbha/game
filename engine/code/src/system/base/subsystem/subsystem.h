#pragma once

struct SGameTime;

class ZSubSystem
{
public:
	ZSubSystem();
	virtual ~ZSubSystem();

	virtual bool Init();
	virtual void Uninit();
	virtual void Update(const SGameTime& gameTime);
};
