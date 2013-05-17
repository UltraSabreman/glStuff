#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class glStuffApp : public AppNative {
public:
	void setup();
	void prepareSettings(Settings *settings);
	void mouseDown(MouseEvent event);	
	void update();
	void draw();
};

void glStuffApp::prepareSettings(Settings *settings) {
	settings->setWindowSize(800, 600);
	settings->setFrameRate(60.0f);
}

void glStuffApp::setup() {
}

void glStuffApp::mouseDown(MouseEvent event) {
}

void glStuffApp::update() {
}

void glStuffApp::draw() {
	gl::clear(Color(0, 0, 0)); 

}

CINDER_APP_NATIVE(glStuffApp, RendererGl)
