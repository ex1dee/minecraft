#include "Animator.h"

#include "../../math/Mathf.h"

constexpr float ANIMATION_FINISH_SMOOTH_FACTOR = 0.05f;

Animator::Animator(const std::string& path, AssimpLoader& assimpLoader)
	: Animator(std::make_shared<Animation>(path, assimpLoader)) {
	
}

Animator::Animator(const std::shared_ptr<Animation>& animation)
	: animation(animation), animationTime(0.0f), animationSpeed(DEFAULT_ANIMATION_SPEED),
	  state(AnimatorState::IDLE), animationStopped(false), switchable(false) {
	boneMatrices.resize(MAX_BONES, glm::mat4(1.0f));
	calcBoneTransform(&animation->getRoot(), glm::mat4(1.0f));
}

void Animator::replayAnimation(bool loop, float speed, bool switchable) {
	animationTime = 0.0f;

	playAnimation(loop, speed, switchable);
}

void Animator::playAnimation(bool loop, float speed, bool switchable) {
	if (isStopped()) {
		timer.reset();
	}

	this->switchable = switchable;
	animationStopped = false;
	animationSpeed = speed;

	if (animationTime == animation->getDuration())
		animationTime = 0.0f;

	if (loop) {
		state = AnimatorState::PLAYING_LOOP;
	} else {
		state = AnimatorState::PLAYING_SINGLE;
	}
}

void Animator::finishAnimation(bool smooth) {
	animationStopped = false;

	if (smooth) {
		state = AnimatorState::FINISHING_SMOOTH;
	} else {
		state = AnimatorState::FINISHING_SHARP;
	}
}

void Animator::stopAnimation() {
	animationStopped = true;
}

void Animator::continueAnimation() {
	animationStopped = false;
	timer.reset();
}

void Animator::update() {
	if (!isPlaying()) {
		return;
	}

	updateAnimationTime();

	if (animationTime >= animation->getDuration() || animationTime < 0 || state == AnimatorState::FINISHING_SHARP)
		handleAnimationEnd();
	
	calcBoneTransform(&animation->getRoot(), glm::mat4(1.0f));
}

void Animator::updateAnimationTime() {
	float deltaTime = timer.getDeltaTime() * animation->getTicksPerSecond() * animationSpeed;

	if (state == AnimatorState::FINISHING_SMOOTH) {
		float targetAnimationTime;

		if (switchable
			|| animationTime < animation->getDuration() * 0.5f
			|| Mathf::equals(animationTime, animation->getDuration(), FLOAT_COMPARE_EPSILON))
			targetAnimationTime = 0.0f;
		else
			targetAnimationTime = animation->getDuration();

		animationTime = Mathf::lerp(animationTime, targetAnimationTime, deltaTime * ANIMATION_FINISH_SMOOTH_FACTOR);
	} else {
		animationTime += deltaTime;
	}
}

void Animator::handleAnimationEnd() {
	if (state == AnimatorState::PLAYING_LOOP) {
		animationTime = std::fmod(animationTime, animation->getDuration());
	} else {
		state = AnimatorState::IDLE;
		animationSpeed = DEFAULT_ANIMATION_SPEED;

		if (switchable)
			animationTime = animation->getDuration();
		else
			animationTime = 0.0f;
	}
}

void Animator::calcBoneTransform(const AnimationNode* node, const glm::mat4& parentTransform) {
	glm::mat4 nodeTransform = node->transform;

	if (animation->containsBone(node->boneName)) {
		Bone* bone = animation->getBone(node->boneName);
		bone->update(animationTime);
		
		nodeTransform = bone->getLocalTransform();
	}
	
	glm::mat4 globalTransform = parentTransform * nodeTransform;
	auto& boneInfoMap = animation->getBoneInfoMap();

	if (boneInfoMap.contains(node->boneName))
		boneMatrices[boneInfoMap[node->boneName].id] = globalTransform * boneInfoMap[node->boneName].offset;

	for (int i = 0; i < node->children.size(); ++i)
		calcBoneTransform(&node->children[i], globalTransform);
}