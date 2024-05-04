<<--------------------------------------------------------------------------------Artificial_Intelligence_Project_02------------------------------------------------------------------------------------------>>

# Developers :
	- This project was done by Max Sherwin(1128059)

# About Project :
	- The project reads the scene contents( i.e the model properties, light properties, etc) from the json file located in "Artificial_Intelligence_Project_02->GameWorldConstruct->SceneDescription.json".

	- In the scene I have placed 3 Beholders and 1 free flying camera(controlled by the user). Controls are given below.
 
	- The 3 Beholders each will indicate the same behaviour, Wander, but different wander styles. I used the alorithm from class.
	
	- Each Wander style is distinct and are distinguished using different colors. 
	
	- If the Beholders wander off and reach almost the end of the terrain, they'll be instantly teleported to the initial position from where they all started.
	
	- The Wander parameteres for each Beholder can be changed in the function 'InitializingEnemyAIs()' located in the 'EnemyAIBrain.cpp' file under the project 'GameWorldConstruct'. 

	- The speed of the characters can also be changed in the same function mentioned above.
	
	- As mentioned in class, for bonus marks, I created a logic to create spheres to indicate where the next wander point is for each Beholder. The spheres are in the same color as the Beholder to show the difference between them.
	
	- Note : The Spiderman model in the middle of the scene has nothing to do with the project, it is just to pinpoint the middle of the game scene.

## How to build and run : 
	- The solution "Artificial_Intelligence_Project_02.sln" has to be built(either in debug or release platform mode) and then once succeeded(probably will!), make the "GameWorldConstruct" project as the startup project and now it'll be able to run for some visual treat.
	- When building the solution, the "MaxGameEngine" project should be run first since it is a static project without which the project with contents(GameWorldConstruct) cannot be run.
	
### Controls :
	- W,A,S,D,Q,E for camera movement(Front, Left, Back, Right, Up and Down respectively)
	- Mouse movement for camera rotation
	- Spacebar to pause and resume mouse mouvement(by default it is set to pause, so click on Spacebar when the scene starts to rotate camera with mouse)
	- 1, 2, 3, 4, 5 buttons are default camera showcase angles.
