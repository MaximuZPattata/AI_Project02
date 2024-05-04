#include "pch.h"
#include "cEnemyAttributes.h"


extern std::vector<cEnemyAttributes> enemyDetailsList;

void InitializingEnemyAIs()
{
	//---------------------------Creating Enemy AI------------------------------------------

	// Paramters = EnemyModelName, Initial Position, Forward Direction, Move Speed, Rotation Speed
	cEnemyAttributes enemy01("Beholder01", glm::vec3(20.f, 10.f, 0.f), glm::vec3(-1.f, 0.f, 0.f), 10.0f, 1.f); 
	cEnemyAttributes enemy02("Beholder02", glm::vec3(50.0, 10.0, 20.0), glm::vec3(-1.f, 0.f, 0.f), 5.0f, 2.f);
	cEnemyAttributes enemy03("Beholder03", glm::vec3(40.0, 10.0, -20.0), glm::vec3(-1.f, 0.f, 0.f), 7.5f, 3.f);

	//-----------------------Initialize Wander Behavior-------------------------------------

	// Giving each wander variation a color
	glm::vec3 GreenColor = glm::vec3(0.1, 0.85, 0.1);
	glm::vec3 WhiteColor = glm::vec3(0.9, 0.9, 0.9);
	glm::vec3 BlueColor = glm::vec3(0.1, 0.1, 0.85);

	enemy01.InitializeWanderBehaviour(2.5f, 5.f, 2.f, GreenColor);	// Change parameters for distinct wandering style
	enemy02.InitializeWanderBehaviour(5.0f, 3.f, 5.f, WhiteColor);	// Change parameters for distinct wandering style
	enemy03.InitializeWanderBehaviour(1.0f, 7.f, 7.f, BlueColor);	// Change parameters for distinct wandering style

	enemyDetailsList.push_back(enemy01);
	enemyDetailsList.push_back(enemy02);
	enemyDetailsList.push_back(enemy03);
}