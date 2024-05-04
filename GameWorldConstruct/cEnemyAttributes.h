#pragma once
#include "pch.h"

#include "PlayerAttributes.h"
#include <cControlGameEngine.h>

struct sWanderBehaviorAttributes
{
	sWanderBehaviorAttributes(float decisionTime, float radius1, float radius2, glm::vec3 wanderColor)
		: wanderCountdown(0.f)
		, wanderDecisionTime(decisionTime)
		, wanderRadius1(radius1)
		, wanderRadius2(radius2) 
		, wanderVariationColor(wanderColor) {}

	glm::vec3 wanderDirection = glm::vec3(0.f);
	glm::vec3 wanderVariationColor;

	float wanderCountdown;
	float wanderDecisionTime;
	float wanderRadius1;
	float wanderRadius2;
};

class cEnemyAttributes
{
public:
	glm::vec3 initialEnemyPosition;
	glm::vec3 currentEnemyPosition;
	glm::vec3 enemyForward;

	std::string enemyModelName;
	
	float enemySpeed;
	float enemyRotationSpeed;

	cEnemyAttributes(std::string modelName, glm::vec3 position, glm::vec3 forward, float speed, float rotationSpeed);

	void Seek(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Flee(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Pursue(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Evade(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void Approach(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes);
	void InitializeWanderBehaviour(unsigned decisionTime, float radius1, float radius2, glm::vec3 wanderColor);
	void Wander(cControlGameEngine& gameEngine);

private:

	float CLOSEST_DISTANCE = 25.f; // The closest the enemy can get to the player is 25 units(SEEK)
	float MAINTAIN_DISTANCE = 75.f; // Length of distance the enemy has to maintain from the player before fleeing(FLEE and APPROACH)
	float TIME_HORIZON = 15.0f; // How much further the AI should look into the player's position(PURSUE and EVADE)

	bool bColorChanged = false;

	sWanderBehaviorAttributes* mWanderBehavior = NULL;

	void IndicateWanderPoint(cControlGameEngine& gameEngine, glm::vec3 wanderPoint);
	void DeleteOldPoint(cControlGameEngine& gameEngine, std::string sphereModelName);
};

