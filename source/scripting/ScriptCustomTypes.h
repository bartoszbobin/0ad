#include "scripting/ScriptableObject.h"

#ifndef _SCRIPTCUSTOMTYPES_H_
#define _SCRIPTCUSTOMTYPES_H_

// Custom object types

// Whilst Point2d is fully coded, it is never registered so is not available in script
// This is mostly as a demonstration of what you need to code to add a new type

// VECTOR2D
extern JSClass Point2dClass;
extern JSPropertySpec Point2dProperties[];
JSBool Point2d_Constructor(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);

// Colour
struct SColour : public CJSObject<SColour>
{
public:
	float r, g, b, a; /* 0...1 */
	SColour() { SColourInit( 0.0f, 0.0f, 0.0f, 0.0f ); }
	SColour( float r, float g, float b ) { SColourInit( r, g, b, 1.0f ); }
	SColour( float r, float g, float b, float a ) { SColourInit( r, g, b, a ); }
	SColour( const SColour& other ) { SColourInit( other.r, other.g, other.b, other.a ); }
	void SColourInit( float r, float g, float b, float a );
	
	SColour &operator = (const SColour &o);

	jsval ToString( JSContext* cx, uintN argc, jsval* argv );
	static void ScriptingInit();
	static JSBool Construct( JSContext* cx, JSObject* obj, uint argc, jsval* argv, jsval* rval );
};

#endif
