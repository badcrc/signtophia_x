// User Defined Structures
typedef struct tagMATRIX										// A Structure To Hold An OpenGL Matrix
{
	float Data[16];												// We Use [16] Due To OpenGL's Matrix Format
}
MATRIX;

typedef struct tagVECTOR										// A Structure To Hold A Single Vector
{
	float X, Y, Z;												// The Components Of The Vector
}
VECTOR;

typedef struct tagVERTEX										// A Structure To Hold A Single Vertex
{
	VECTOR Nor;													// Vertex Normal
	VECTOR Pos;													// Vertex Position
}
VERTEX;

typedef struct tagPOLYGON										// A Structure To Hold A Single Polygon
{
	VERTEX Verts[3];											// Array Of 3 VERTEX Structures
}
POLYGON;

// User Defined Variables
int		outlineDraw		= 1;								// Flag To Draw The Outline
int		outlineSmooth	= 0;							// Flag To Anti-Alias The Lines
float		outlineColor[3]	= { 0.0f, 0.0f, 0.0f };				// Color Of The Lines
float		outlineWidth	= 3.0f;								// Width Of The Lines

VECTOR		lightAngle;											// The Direction Of The Light
float		lightPos[4];										// The Direction Of The Light, Stored In Four Components Because glLight Needs Them (NEW)
int		lightRotate		= 0;							// Flag To See If We Rotate The Light

float		modelAngle		= 0.0f;								// Y-Axis Angle Of The Model
int       modelRotate		= 0;							// Flag To Rotate The Model

POLYGON		*polyData		= NULL;								// Polygon Data
int			polyNum			= 0;								// Number Of Polygons

int		shaderTexture[1];									// Storage For One Texture

int		arbVertexProgram= false;							// Flag To Check If ARB_vertex_program Is Supported ( NEW )
int        useVertexProgram= true;								// Flag To Use Vertex Programs (Unused if Vertex Programs Are Not Supported) ( NEW )
int      program[1];											// Storage For One Program ( NEW )
char     vertexProgramString[] =								// The Vertex Program ( NEW )
"!!ARBvp1.0\
#\n\
# This computes the dot product between the normal and the\n\
# light direction and outputs it to the S texture coord\n\
#\n\
ATTRIB iPos         = vertex.position;\
ATTRIB iColor		= vertex.color;\
ATTRIB iNormal      = vertex.normal;\
PARAM  mvinv[4]     = { state.matrix.modelview.invtrans };\
PARAM  mvp[4]       = { state.matrix.mvp };\
PARAM  lightDir     = state.light[0].position;\
TEMP   xfNormal, tempdot;\
OUTPUT oPos         = result.position;\
OUTPUT oColor       = result.color;\
OUTPUT oTex         = result.texcoord;\
\
# Transform the vertex to clip coordinates.\n\
# We transform succesively through the modelview matrix, then the projection matrix.\n\
DP4 oPos.x, mvp[0], iPos;\
DP4 oPos.y, mvp[1], iPos;\
DP4 oPos.z, mvp[2], iPos;\
DP4 oPos.w, mvp[3], iPos;\
\
# Transform the normal to eye coordinates.\n\
# We transform through the inverse transpose modelview matrix, not through the modelview matrix (see OpenGL specs).\n\
DP3 xfNormal.x, mvinv[0], iNormal;\
DP3 xfNormal.y, mvinv[1], iNormal;\
DP3 xfNormal.z, mvinv[2], iNormal;\
\
# Compute the dot product between normal and light position (light direction in fact, since the w component is 0).\n\
DP3 tempdot.x, xfNormal, lightDir;\
# Store the dot product result into S texcoord, and clamp it to zero.\n\
MAX oTex.x, tempdot.x, 0;\
\
# Write our color out directly\n\
MOV oColor, iColor;\
\
END";
