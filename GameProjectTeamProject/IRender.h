#pragma once

class IRender
{
public:
	inline virtual void Render() abstract;
	virtual int GetRenderPriotity() abstract;
};