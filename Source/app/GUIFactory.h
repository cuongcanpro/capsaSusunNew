#ifndef GUIFactory_h__
#define GUIFactory_h__

#include <string>

class BaseLayer;
class GUIFactory {
public:
	static BaseLayer* createGUI(std::string className);
};
#endif // GUIFactory_h__
