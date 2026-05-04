#include "Application.hpp"

int main(const int argc, char* argv[])
{
	Permafrost::Application app{argc, argv, {800, 500}};

	app.Render();
	
	return QApplication::exec();
}
