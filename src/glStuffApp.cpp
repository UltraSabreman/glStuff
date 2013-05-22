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
	gl::VboMesh mVbo;
	MayaCamUI myCamera;

		TriMesh mMesh;

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
	/*int totalVertices = VERTx*VERTy;
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
	mVbo->bufferColorsRGB(texCoords);*/
	// Create the points of our cube

	Vec3f v0(-100,-100,-100);
	Vec3f v1( 100,-100,-100);
	Vec3f v2( 100, 100,-100);
	Vec3f v3(-100, 100,-100);
	Vec3f v4(-100,-100, 100);
	Vec3f v5( 100,-100, 100);
	Vec3f v6( 100, 100, 100);
	Vec3f v7(-100, 100, 100);
 
	// Create the colors for each vertex
	Color c0( 0, 0, 0 );
	Color c1( 1, 0, 0 );
	Color c2( 1, 1, 0 );
	Color c3( 0, 1, 0 );
	Color c4( 0, 0, 1 );
	Color c5( 1, 0, 1 );
	Color c6( 1, 1, 1 );
	Color c7( 0, 1, 1 );
 
	Vec3f faces[6][4] = { /* Vertices for the 6 faces of a cube. */
	{v0, v1, v2, v3}, {v3, v2, v6, v7}, {v7, v6, v5, v4},
	{v4, v5, v1, v0}, {v5, v6, v2, v1}, {v7, v4, v0, v3} };
 
	Color colors[6][4] = { /* colors for each vertex of the cube. */
	{c0, c1, c2, c3}, {c3, c2, c6, c7}, {c7, c6, c5, c4},
	{c4, c5, c1, c0}, {c5, c6, c2, c1}, {c7, c4, c0, c3} };
 
	for (int i = 0; i < 6; i++)
	{
 
		mMesh.appendVertex(faces[i][0]);
		mMesh.appendColorRgb(colors[i][0]);
		mMesh.appendVertex(faces[i][1]);
		mMesh.appendColorRgb(colors[i][1]);
		mMesh.appendVertex(faces[i][2]);
		mMesh.appendColorRgb(colors[i][2]);
		mMesh.appendVertex(faces[i][3]);
		mMesh.appendColorRgb(colors[i][3]);
 
		int numberVertices = mMesh.getNumVertices();
 
		mMesh.appendTriangle( numberVertices - 4, numberVertices - 3, numberVertices - 2 );
		mMesh.appendTriangle( numberVertices - 4, numberVertices - 2, numberVertices - 1 );
 
	}

	mVbo = gl::VboMesh(mMesh);

}

void glStuffApp::mouseDown(MouseEvent event) {
}

void glStuffApp::update() {

	/*gl::VboMesh::VertexIter iter = mVbo->mapVertexBuffer();
	for( int x = 0; x < VERTx; ++x ) {
		for( int y = 0; y < VERTy; ++y ) {
			iter.setPosition(Vec3d(x,y + cos(getElapsedSeconds()) * 10,sin(getElapsedSeconds()) * 10));
			++iter;
		}
	}*/

	if( mMesh.getNumVertices() == 0 ) return;
 
	// store all the mesh information
 
	vector<Color> col = mMesh.getColorsRGB();
	vector<Vec3f> vec= mMesh.getVertices();
 
	int i, j;
	i = mMesh.getNumVertices();
	j = 0;
 
	mMesh.clear();
 
	// something to add a little movement
	float inc = sin( getElapsedSeconds() );
 
	while(j < i)
	{
		// alter the positions array to get a little dynamism
		vec.at(j).x -= inc;
		vec.at(j+1).x += inc;
		vec.at(j+2).x += inc*2.0f;
		vec.at(j+3).x -= inc*2.0f;
 
		// now replace it in the mesh
		mMesh.appendVertex( vec.at(j));
		mMesh.appendColorRgb( col.at(j) );
		mMesh.appendVertex( vec.at(j+1));
		mMesh.appendColorRgb( col.at(j+1) );
		mMesh.appendVertex( vec.at(j+2));
		mMesh.appendColorRgb( col.at(j+2) );
		mMesh.appendVertex( vec.at(j+3));
		mMesh.appendColorRgb( col.at(j+3) );
 
		int vIdx0 = mMesh.getNumVertices() - 4;
		int vIdx1 = mMesh.getNumVertices() - 3;
		int vIdx2 = mMesh.getNumVertices() - 2;
		int vIdx3 = mMesh.getNumVertices() - 1;
 
		mMesh.appendTriangle( vIdx0, vIdx1, vIdx2 );
		mMesh.appendTriangle( vIdx0, vIdx2, vIdx3 );
 
		// go to the next triangle pair
		j+=4;
	}
}

void glStuffApp::draw() {
	gl::clear(Color(0.0, 0, 0)); 

	gl::setMatrices(myCamera.getCamera());
	gl::enableDepthRead();
	gl::enableWireframe();
	//console() << mVbo->getLayout().mAttributes << endl;

	shader.bind();
	shader.uniform("modelview", myCamera.getCamera().getModelViewMatrix());
	shader.uniform("projection", myCamera.getCamera().getProjectionMatrix());
	//shader.uniform("inCol", Color(0.0,0.0,1.0));

	gl::draw(mVbo);

	shader.unbind();

	gl::disableWireframe();
	gl::disableDepthRead();
	gl::popMatrices();
}

CINDER_APP_NATIVE(glStuffApp, RendererGl)
