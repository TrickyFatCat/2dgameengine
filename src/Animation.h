#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
	public:
		unsigned int index = 0;
		unsigned int numFrames = 0;
		unsigned int animationSpeed = 0;

		Animation();
		Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
	private:
};

#endif