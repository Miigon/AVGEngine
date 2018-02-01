#pragma once

class Uncopyable
{
public:
	Uncopyable() = default;
	virtual ~Uncopyable() = default;
	Uncopyable(const Uncopyable&) = delete;
	Uncopyable(const Uncopyable&&) = delete;
	Uncopyable operator =(const Uncopyable&) = delete;
	Uncopyable operator =(const Uncopyable&&) = delete;
};