#include "cinder\app\AppNative.h"
#include "cinder\gl\gl.h"
#include "cinder\gl\GlslProg.h"
#include "cinder\gl\Vbo.h"
#include "cinder\MayaCamUI.h"

#define VERTx 20
#define VERTy 20

using namespace ci;
using namespace ci::app;
using namespace std;

class glStuffApp : public AppNative {
public:
	void setup();
	void prepareSettings(Settings *);
	void mouseDown(MouseEvent);	
	void mouseDrag(MouseEvent);
	void resize();
	void update();
	void draw();

	gl::GlslProg shader;
	gl::VboMeshRef mVbo;
	MayaCamUI myCamera;

	GLuint model,proj,view;
};

void glStuffApp::resize() {
	// adjust aspect ratio
	CameraPersp cam = myCamera.getCamera();
	cam.setAspectRatio(getWindowAspectRatio());
	myCamera.setCurrentCam(cam);
}

void glStuffApp::mouseDrag(MouseEvent event) {
	myCamera.mouseDrag( event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown() );
}

void glStuffApp::prepareSettings(Settings *settings) {
	//settings->setWindowSize(800, 600);
	//settings->setFrameRate(60.0f);
}

void glStuffApp::setup() {

	CameraPersp cam;
	cam.setPerspective(75.0f, getWindowAspectRatio(), 5.0f, 2000.0f);
	cam.setEyePoint(Vec3f(0,0,500));
	cam.setCenterOfInterestPoint(Vec3f::zero());
	myCamera.setCurrentCam(cam);

	try {
		shader = gl::GlslProg(loadAsset("vert_shader.glsl"), loadAsset("frag_shader.glsl"));
	} catch(gl::GlslProgCompileExc shaderError) {
		console() << "Shader Compile error:" << endl;
		console() << shaderError.what() << endl;
	}

		// setup the parameters of the Vbo
	int totalVertices = VERTx*VERTy;
	int totalQuads = VERTx*VERTy;

	gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setDynamicPositions();
	layout.setStaticColorsRGB();
	mVbo = gl::VboMesh::create( totalVertices, totalQuads * 4, layout, GL_QUADS );
	
	// buffer our static data - the texcoords and the indices
	vector<uint32_t> indices;
	vector<Color> texCoords;
	int lol = 0;
	for( int x = 0; x < VERTx; ++x ) {
		for( int y = 0; y < VERTy; ++y, lol++ ) {
			// create a quad for each vertex, except for along the bottom and right edges
			if( ( x + 1 < VERTx ) && ( y + 1 < VERTy ) ) {
				indices.push_back( (x+0) * VERTy + (y+0));
				indices.push_back( (x+1) * VERTy + (y+0));
				indices.push_back( (x+1) * VERTy + (y+1));
				indices.push_back( (x+0) * VERTy + (y+1));
			}

			Color test = hsvToRGB(Vec3f((float)lol/totalVertices,1.0,1.0));
			texCoords.push_back(test);
		}
	}
	mVbo->bufferIndices(indices);
	mVbo->bufferColorsRGB(texCoords);
//	mVbo->
	//console() << shader.getAttribLocation("Color") << endl;
}

void glStuffApp::mouseDown(MouseEvent event) {
}

void glStuffApp::update() {

	gl::VboMesh::VertexIter iter = mVbo->mapVertexBuffer();
	for( int x = 0; x < VERTx; ++x ) {
		for( int y = 0; y < VERTy; ++y ) {
			iter.setPosition(Vec3d(x,y,sin(x + y + getElapsedSeconds()) * 1));
			++iter;
		}
	}
}

void glStuffApp::draw() {
	gl::clear(Color(0.0, 0, 0), true); 

	//gl::setMatrices(myCamera.getCamera());
	gl::enableDepthRead();
	gl::enableWireframe();

	shader.bind();
	shader.uniform("modelview", myCamera.getCamera().getModelViewMatrix());
	shader.uniform("projection", myCamera.getCamera().getProjectionMatrix());

	gl::draw(mVbo);

	shader.unbind();

	gl::disableWireframe();
	gl::disableDepthRead();
	//gl::popMatrices();
}

CINDER_APP_NATIVE(glStuffApp, RendererGl)
