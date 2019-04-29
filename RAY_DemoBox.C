/*
 * Copyright (c) 2019
 *	Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 * This is a sample procedural DSO
 */

#include <UT/UT_DSOVersion.h>
#include <GU/GU_Detail.h>
#include "RAY_DemoBox.h"
#include <RAY/RAY_ProceduralFactory.h>

using namespace HDK_Sample;

static RAY_ProceduralArg	theArgs[] = {
    // Default minimum bound is {-1,-1,-1}
    RAY_ProceduralArg("minbound",	"real",	"-1 -1 -1"),
    // Default maximum bound is {1,1,1}
    RAY_ProceduralArg("maxbound",	"real",	"1 1 1"),
    RAY_ProceduralArg()
};

class ProcDef : public RAY_ProceduralFactory::ProcDefinition
{
public:
    ProcDef()
	: RAY_ProceduralFactory::ProcDefinition("demobox")
    {
    }
    virtual RAY_Procedural	*create() const { return new RAY_DemoBox(); }
    virtual RAY_ProceduralArg	*arguments() const { return theArgs; }
};

void
registerProcedural(RAY_ProceduralFactory *factory)
{
    factory->insert(new ProcDef);
}

RAY_DemoBox::RAY_DemoBox()
{
    myBox.initBounds(0, 0, 0);
}

RAY_DemoBox::~RAY_DemoBox()
{
}

const char *
RAY_DemoBox::className() const
{
    return "RAY_DemoBox";
}

int
RAY_DemoBox::initialize(const UT_BoundingBox *)
{
    fpreal	val[3];

    // Import the minbound parameter.  This will pick up parameters passed on
    // the procedural line in the IFD, or the default value from the
    // RAY_ProceduralArg.
    val[0] = val[1] = val[2] = -1;
    import("minbound", val, 3);
    myBox.initBounds(val[0], val[1], val[2]);

    val[0] = val[1] = val[2] = 1;
    import("maxbound", val, 3);
    myBox.enlargeBounds(val[0], val[1], val[2]);

    // The bounding box has been initialized.  The geometry generated must like
    // within the bounds.
    return 1;
}

void
RAY_DemoBox::getBoundingBox(UT_BoundingBox &box)
{
    // Return the bounding box of the geometry
    box = myBox;
}

void
RAY_DemoBox::render()
{
    /// Allocate geometry.
    /// NOTE:  Do not simply construct a GU_Detail.
    /// @see RAY_Procedural::createGeometry().
    RAY_ProceduralGeo	geo = createGeometry();

    /// Call the GU_Detail::cube() method to create a cube
    geo->cube(myBox.vals[0][0], myBox.vals[0][1],
	      myBox.vals[1][0], myBox.vals[1][1],
	      myBox.vals[2][0], myBox.vals[2][1]);

    // Create a geometry object in mantra
    RAY_ProceduralChildPtr	obj = createChild();
    obj->addGeometry(geo);
    // Change the surface shader setting
    obj->changeSetting("surface", "constant Cd ( 1 0 0 )", "object");
}
