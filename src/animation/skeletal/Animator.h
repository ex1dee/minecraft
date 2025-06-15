#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../../utils/Timer.h"
#include "AnimatorState.h"
#include "Animation.h"

class Animator {
	std::shared_ptr<Animation> animation;
	AnimatorState state;
	float animationTime;
	float animationSpeed;
	bool animationStopped;
	bool switchable;
	Timer timer;

	void handleAnimationEnd();
	void updateAnimationTime();
	void calcBoneTransform(const AnimationNode* node, const glm::mat4& parentTransform);
public:
	std::vector<glm::mat4> boneMatrices;

	Animator() = default;
	Animator(const std::shared_ptr<Animation>& animation);
	Animator(const std::string& path, AssimpLoader& assimpLoader);

	AnimatorState getState() const { return state; }
	bool isPlaying() const { return !isStopped(); }
	bool isStopped() const { return animationStopped || state == AnimatorState::IDLE; }
	void setAnimationSpeed(float animationSpeed) { this->animationSpeed = animationSpeed; }

	void update();
	void stopAnimation();
	void continueAnimation();
	void finishAnimation(bool smooth);
	void playAnimation(bool loop, float speed = DEFAULT_ANIMATION_SPEED, bool switchable = false);
	void replayAnimation(bool loop, float speed = DEFAULT_ANIMATION_SPEED, bool switchable = false);
};

#endif