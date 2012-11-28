namespace engine
{
	/**
	 * The Entity class is a representation of an object in a game or program.
	 * This class is responsible for drawing and updating itself on the screen.
	 */
	class Entity
	{
	public:
		Entity();
		~Entity();
		void Draw();
		void Update();
	};
}