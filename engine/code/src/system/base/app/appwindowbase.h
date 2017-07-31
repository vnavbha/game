#pragma once

struct SGameTime;

//-----------------------------------------------------------------------------

class ZAppWindowBase
{
public:
	ZAppWindowBase();
	virtual ~ZAppWindowBase();

	virtual bool Init();
	virtual void Uninit();
	virtual bool Update(const SGameTime& gameTime);

private:
};
