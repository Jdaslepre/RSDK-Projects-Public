bool setLoop = false;
#include "RetroEngine.hpp"

extern "C" {
    EMSCRIPTEN_KEEPALIVE void RSDKInitialize()
    {
	    Engine.Init();

	    if (setLoop == false) {
            setLoop = true;
    	    emscripten_set_main_loop([] () { Engine.Run(); }, Engine.refreshRate, 1);
    	}        
    }
}


int main()
{
    return 0;
}