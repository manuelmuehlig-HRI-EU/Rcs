/*******************************************************************************

  Copyright (c) 2017, Honda Research Institute Europe GmbH.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement: This product includes
     software developed by the Honda Research Institute Europe GmbH.

  4. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef MESHNODE_H
#define MESHNODE_H

#include "NodeBase.h"

#include <osg/Geode>
#include <osg/ShapeDrawable>

namespace Rcs
{

/*!
 * \ingroup RcsGraphics
 * \brief    OpenSceneGraph node to display triangle meshes. The data is
 *           assumed as vertex and face lists in arrays vertex and faces.
 *           Value numVertices is the number of the (xyz) vertex vectors,
 *           value numFaces is the number of triangles. The array vertices
 *           must point to memory with equal to or more than 3*numVertices
 *           double values. The array faces must point to memory with equal
 *           to or more than 3*numVertices integer values. The function
 *           setMesh replaces the current mesh with the new one.
 */
class MeshNode : public NodeBase
{
public:

  MeshNode();
  MeshNode(const char* meshFile);
  MeshNode(const double* vertices, unsigned int numVertices,
           const unsigned int* faces, unsigned int numFaces);
  void setMesh(const double* vertices, unsigned int numVertices,
               const unsigned int* faces, unsigned int numFaces);
  void clear();

protected:

  osg::ref_ptr<osg::Geode> geode;
  void init();
};

}   // namespace Rcs

#endif // MESHNODE_H
