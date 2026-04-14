#pragma once

class IViewModelInterface
{
public:
	virtual ~IViewModelInterface() = default;
	virtual void BindViewModel() = 0;
};
