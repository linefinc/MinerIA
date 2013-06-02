#pragma once
#include <vector>
#include <memory>
#include <string>
#include "GameObject.h"

using namespace std;


class GameObjectManager
{
private:
	int NextID;


	private:
        GameObjectManager() 
		{
			NextID =0;
		};                   // Constructor? (the {} brackets) are needed here.
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
        GameObjectManager(GameObjectManager const&);              // Don't Implement
        void operator=(GameObjectManager const&); // Don't implement

	public:
        static GameObjectManager& getInstance()
        {
            static GameObjectManager    instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
            return instance;
        }

		shared_ptr<GameObject> findGameObjectByName(const string& Name);

		void AddGameObject(shared_ptr<GameObject> object);

		int GetNextID();
};


