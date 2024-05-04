#include "pch.h"
#include "cEnemyAttributes.h"

cEnemyAttributes::cEnemyAttributes(std::string modelName, glm::vec3 position, glm::vec3 forward, float speed, float rotationSpeed)
{
	this->initialEnemyPosition = position;
	this->enemyModelName = modelName;
	this->currentEnemyPosition = position;
	this->enemyForward = forward;
	this->enemySpeed = speed;
	this->enemyRotationSpeed = rotationSpeed;
}

// Function to make the enemy move towards the player
void cEnemyAttributes::Seek(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - currentEnemyPosition);

	glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	// Condition to check if the enemy model is not very close to the player
	if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) >= CLOSEST_DISTANCE)
	{
		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving model towards player direction
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.85f, 0.f, 0.f); // Red
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move away from the player
void cEnemyAttributes::Flee(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	// Condition to check if the player is close enough for the enemy to flee
	if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(currentEnemyPosition - playerAttributes.playerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.f, 0.85f); // Blue
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move towards the player's future position
void cEnemyAttributes::Pursue(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 futurePlayerPosition = playerAttributes.playerPosition + playerAttributes.playerVelocity * TIME_HORIZON;

	glm::vec3 pursueDirection = glm::normalize(futurePlayerPosition - currentEnemyPosition); // Direction for movement

	glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - currentEnemyPosition); // Direction for orientation

	glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	if (glm::length(currentEnemyPosition - futurePlayerPosition) > 10.0f)
	{
		currentEnemyPosition += enemySpeed * pursueDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving model towards player direction
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.f); // Green
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move away from the player's future position
void cEnemyAttributes::Evade(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 futurePlayerPosition = playerAttributes.playerPosition + playerAttributes.playerVelocity * TIME_HORIZON;

	if (glm::length(currentEnemyPosition - futurePlayerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(currentEnemyPosition - futurePlayerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.85f, 0.85f, 0.f); // Yellow
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy maintain distance from the player
void cEnemyAttributes::Approach(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	float offset = 10.f;

	if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) > MAINTAIN_DISTANCE + offset)
	{
		glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - currentEnemyPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		// Condition to check if the enemy model is not very close to the player
		if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) > MAINTAIN_DISTANCE + offset)
		{
			currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

			// Moving model towards player direction
			gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

			gameEngine.UseManualColors(enemyModelName, true);
			gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.85f); // Light Blue
		}
		else
			gameEngine.UseManualColors(enemyModelName, false);
	}

	else if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(currentEnemyPosition - playerAttributes.playerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.85f); // Light Blue
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to initialize the wander behaviour
void cEnemyAttributes::InitializeWanderBehaviour(unsigned decisionTime, float radius1, float radius2, glm::vec3 wanderColor)
{
	if (this->mWanderBehavior == NULL)
		this->mWanderBehavior = new sWanderBehaviorAttributes(decisionTime, radius1, radius2, wanderColor);
	else
	{
		std::cout << std::endl;
		std::cout << "WANDER BEHAVIOUR ALREADY INITIALIZED" << std::endl;
	}
}

// Function to make the enemy wander in the game world region
void cEnemyAttributes::Wander(cControlGameEngine& gameEngine)
{
	this->mWanderBehavior->wanderCountdown -= gameEngine.deltaTime;

	if (this->mWanderBehavior->wanderCountdown <= 0.f)
	{
		this->mWanderBehavior->wanderCountdown = this->mWanderBehavior->wanderDecisionTime;
		
		glm::vec3 direction = this->enemyForward;
		glm::vec3 wanderPoint(this->currentEnemyPosition + direction * this->mWanderBehavior->wanderRadius1);

		// Finding a random angle to move to/turn to
		float randomAngle = glm::linearRand(0.f, glm::two_pi<float>());

		float xPos = this->mWanderBehavior->wanderRadius1 * glm::cos(randomAngle);
		float zPos = this->mWanderBehavior->wanderRadius2 * glm::sin(randomAngle);

		wanderPoint.x += xPos;
		wanderPoint.z += zPos;

		this->mWanderBehavior->wanderDirection = glm::normalize(wanderPoint - this->currentEnemyPosition);

		//--------------------Creating a sphere to indicate the wander point in game world-------------------------------
		
		this->IndicateWanderPoint(gameEngine, wanderPoint);
	}

	// Fetching the target rotation direction
	glm::quat targetRotationQuat = glm::rotation(enemyForward, this->mWanderBehavior->wanderDirection);

	// Fetching the target original rotated direction
	glm::quat rotationQuat = gameEngine.GetModelRotationQuat(this->enemyModelName);
	
	// Fetching the interpolated quat(a rotation direction inbetween the current and target direction)
	glm::quat interpolatedQuat = glm::slerp(glm::normalize(rotationQuat), glm::normalize(targetRotationQuat), this->enemyRotationSpeed * static_cast<float>(gameEngine.deltaTime));

	rotationQuat = interpolatedQuat;

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	this->currentEnemyPosition += enemySpeed * this->mWanderBehavior->wanderDirection * static_cast<float>(gameEngine.deltaTime);

	float BOUNDARY_CHECK = 950.f;

	// Checking if the enemy is leaving the boundary of the game region
	if (this->currentEnemyPosition.x > BOUNDARY_CHECK || this->currentEnemyPosition.x < -BOUNDARY_CHECK || this->currentEnemyPosition.z > BOUNDARY_CHECK || this->currentEnemyPosition.z < -BOUNDARY_CHECK)
		this->currentEnemyPosition = this->initialEnemyPosition;

	// Moving model towards player direction
	gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

	// Changing colors to distinguish the models
	if (!this->bColorChanged)
	{
		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, this->mWanderBehavior->wanderVariationColor.x, this->mWanderBehavior->wanderVariationColor.y, this->mWanderBehavior->wanderVariationColor.z);
		
		this->bColorChanged = true;
	}
}

// Function to create spheres to indicate the wander point in the game world
void cEnemyAttributes::IndicateWanderPoint(cControlGameEngine& gameEngine, glm::vec3 wanderPoint)
{
	std::string sphereModelName = "Sphere_" + this->enemyModelName;

	this->DeleteOldPoint(gameEngine, sphereModelName);

	gameEngine.LoadModelsInto3DSpace("Sphere_1_unit_Radius_uv.ply", sphereModelName, wanderPoint.x, 10.f, wanderPoint.z);
	gameEngine.ScaleModel(sphereModelName, 4.5f);
	gameEngine.TurnMeshLightsOn(sphereModelName);
	gameEngine.TurnWireframeModeOn(sphereModelName);
	gameEngine.UseManualColors(sphereModelName, true);
	gameEngine.ChangeColor(sphereModelName, this->mWanderBehavior->wanderVariationColor.x - 0.1, this->mWanderBehavior->wanderVariationColor.y - 0.1, this->mWanderBehavior->wanderVariationColor.z - 0.1);
}

// Function to delete the old sphere model in the previous wander point
void cEnemyAttributes::DeleteOldPoint(cControlGameEngine& gameEngine, std::string sphereModelName)
{
	gameEngine.DeleteMesh(sphereModelName);
}

